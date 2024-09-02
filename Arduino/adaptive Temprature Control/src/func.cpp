#include "func.h"

// used variables
LiquidCrystal_I2C lcd(0x27, 16, 2); // lcd 16*2 variable
float TL = 20;                      // initial TL condition
float TH = 30;                      // initial TH condition
bool flag = false;                  // comma flag
String tempSet;                     // input variable from bluetooth module

void initAdaotiveTempControl(void)
{
    // put your setup code here, to run once:
    Serial.begin(9600);
    pinMode(vScPin, INPUT);
    pinMode(redLed, OUTPUT);
    pinMode(blueLed, OUTPUT);
    pinMode(greenLed, OUTPUT);
    pinMode(in1m, OUTPUT);
    pinMode(in2m, OUTPUT);
    pinMode(tungLampPin, OUTPUT);
    pinMode(fanPin2, OUTPUT);
    // init cool hot
    digitalWrite(redLed, LOW);
    digitalWrite(blueLed, LOW);
    digitalWrite(greenLed, LOW);
    digitalWrite(in1m, LOW);
    digitalWrite(in2m, LOW);
    digitalWrite(tungLampPin, HIGH);
    digitalWrite(fanPin2, LOW);
    digitalWrite(fanPin1, LOW);
    // init lcd
    lcd.init();
    lcd.backlight();
    lcd.clear();
}

// heater control by relay
void heater(bool condition)
{
    // if condition is true open heater else close it
    if (condition)
    {
        digitalWrite(tungLampPin, HIGH);
    }
    else
    {
        digitalWrite(tungLampPin, LOW);
    }
}

// fan controlled by L293 motor driver
void fan(bool condition)
{
    // if condition is true open cooler else close it
    if (condition)
    {
        digitalWrite(fanPin2, HIGH);
    }
    else
    {
        digitalWrite(fanPin2, LOW);
    }
}

////fan controlled by L293 motor driver
void motorDir(bool dir)
{
    // if condition is true motor set to cw else ccw
    if (dir)
    {
        digitalWrite(in1m, HIGH);
        digitalWrite(in2m, LOW);
    }
    else
    {
        digitalWrite(in1m, LOW);
        digitalWrite(in2m, HIGH);
    }
}

// convert input analog voltage to the current temprature
double getTemptature(double vInA)
{
    // just moving backward from the end of signal conditioning design calculations
    double Vo = (vInA / 1023) * 4.5;                               // convert analog signal to digital one
    double Vab = (Vo - 2.042) / 0.518;                             // get the output from the bridge after 1st diff amp with gain = 1
    double R4 = (114.4 - 23.82 * Vab) / (10.0 + 2.382 * Vab);      // get R sensor from bridge equation
    double T = 1.0 / ((log(R4 / 10.0) / 3950.0) + (1.0 / 298.15)); // get current temp in kelvin
    /*
                                       ##serial plotter##
                               #measure change of our variables#
       plot VinA -> analog signal, Vo -> digital signal , T -> current temp , Vab -> bridge voltage, R4 -> our sensor
    */
    // Serial.print(vInA);
    /*Serial.print("\t");
    Serial.print(Vo);
    Serial.print("\t");
    Serial.print(Vab);
    Serial.print("\t");
    Serial.print(R4);
    Serial.print("\t");
    Serial.println(T - 273.15);*/
    return T - 273.15; // return the current temprature in celisus
}

void adaotiveTempControl(void)
{

    // put your main code here, to run repeatedly:
    /*
    get input TL &  TH From user via bluetooth module
    the format sent by the user is as follow: TL,TH
    */
    if (Serial.available() > 0)
    {
        tempSet = Serial.readStringUntil('\n');
        float tLow = 0;
        float tHot = 0;
        int i = 0;
        while (tempSet[i] != '\n' && i < tempSet.length())
        {
            if (tempSet[i] == ',')
            {
                flag = true;
            }
            else if (isdigit(tempSet[i]))
            {
                if (!flag)
                {
                    tLow = tLow * 10 + (tempSet[i] - '0');
                }
                else
                {
                    tHot = tHot * 10 + (tempSet[i] - '0');
                }
            }
            i++;
        }
        // set TL & TH , RESET FLAG
        if (flag)
        {
            Serial.print("Low Temperature: ");
            Serial.println(tLow);
            Serial.print("High Temperature: ");
            Serial.println(tHot);
            TL = tLow;
            TH = tHot;
            flag = false;
        }
    }

    // get the input analog signal
    double vSc = analogRead(vScPin);
    // get the current temprature from the input signal
    double Ta = getTemptature(vSc);
    //
    Serial.print("temprature range is ");
    Serial.print(TL);
    Serial.print(" To ");
    Serial.println(TH);
    Serial.print("Current Temprature = ");
    Serial.println(Ta);
    // show the values on the LCD
    lcd.setCursor(0, 0);
    lcd.print("TL=");
    lcd.setCursor(3, 0);
    lcd.print(TL);
    lcd.setCursor(8, 0);
    lcd.print("TH=");
    lcd.setCursor(11, 0);
    lcd.print(TH);
    lcd.setCursor(0, 1);
    lcd.print("Ta=");
    lcd.setCursor(3, 1);
    lcd.print(Ta);
    lcd.setCursor(10, 1);
    lcd.print("C");

    // control the temprature from the ntc 10k ohm thermistor to the drsired range between TL - TH
    if (Ta > TH)
    {
        // OPEN HEATER & CLOSE COOLER
        heater(LOW);
        fan(true);
        digitalWrite(greenLed, LOW);
        digitalWrite(blueLed, LOW);
        digitalWrite(redLed, HIGH);
        motorDir(true);
    }
    else if (Ta < TL)
    {
        // OPEN COOLER & CLOSE HEATER
        heater(HIGH);
        fan(false);
        digitalWrite(greenLed, LOW);
        digitalWrite(redLed, LOW);
        digitalWrite(blueLed, HIGH);
        motorDir(false);
    }
    else if (Ta < TH && Ta > TL)
    {
        // Ta is within the desired range
        digitalWrite(redLed, LOW);
        digitalWrite(blueLed, LOW);
        digitalWrite(greenLed, HIGH);
    }
    delay(1000);
}