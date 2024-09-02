/*
                     #industrial instrumation EPMN-303 Project
                     #DR AHMED KAMEL
                     #TA ENG ABD EL FATAH
                     #TA ENG OSAMA MORSI
                     #PROJECT 4 - TEMPRATURE CONTROL
                     #TEAM MEMBERS :
                                   1- MOHAMED ABD EL TWAB NEWIR 

      * REQUIRMENT TO SET RANGE FOR TEMPRATURE AND KEEP THE CURRENT TEMPRATURE TO BE WITHIN THE RANGE
      - WE USED NTC 10 KOHM THERMISTOR TO MEASURE THE CURRENT TEMPRATURE
      - WE PUT THE THERMISTOR AS R4 IN WHEATSTONE BRIDGE
      - WE DESIGNED A SIGNAL CONDITIONAING CIRCUIT TO READ THE CURRENT TEMPRATURE
      - WE USED 5 UA-741 OP AMP IC :
                                   2 ICs WILL ACT AS VOLTAGE FOLLOWER
                                   2 ICs WIIL ACT AS DIFFRENTIAL AMP
                                   1 IC WILL ACT AS INVERTER AMP
      - OUR EQUATIONS :
                  Vab = Vs((R2R3-R4R1)/((R2+R4)(3+R1R))) -> Vs = 9v & R1 = R2 = 10KOHM, R3 = 11.44KOHM (TO NULL THE BRIDGE) -> Vab range is (-3.942 to 4.743) // WE USED DIFFRENTIAL AMP WITH GAIN 1 TO GET Vab
                  Vo = mVab + c //our range wiil be between 0 to 4.5 not 5 to protect arduino if it take Vin > 5 due to some errors n the circuit -> m = 0.518, c = 2.042
                  Vo = 0.518Vab + 2.042 = .518(Vab-(-3.942)) -> R2/R1(V2-V1) -> R1 = 10 KOHM, R2 = 5.18 KOHM // WE GET R2 FROM POTENTIOMETER BEC IT'SNOT STD VALUE
                  // -3.942 V we get it from inverter amp-> 3.942 = R2/R1*9 , R1 = 10KOHM -> R2 = 4.38KOHM // WE GET R2 FROM POTENTIOMETER BEC IT'SNOT STD VALUE
      - AFTER WE GET Vo IT WOUL BE AN INPUT IN THE ANALOGE PIN THEN WE APPLY OUR IVERSE EQUATIONS TO GET THE CURRENT TEMPRATURE
      -INVRERSE EQUATIONS:
                           Vo = (vInA / 1023) * 4.5 , convert analog signal to digital one
                           Vab = (Vo - 2.042) / 0.518 , get the output from the bridge after 1st diff amp with gain = 1
                           R4 = (114.4 - 23.82 * Vab) / (10.0 + 2.382 * Vab) , get R sensor from bridge equation
                           T = 1.0 / ((ln(R4 / 10.0) / B) + (1.0 / 298.15)) ,CURRENT TEMPRAURE IN KELVIN NOT THAT THE CONSTANT OF NTC 10 KOHM THERMISTOR SENSOR: B = 3950
                           T = T - 273.15 CURRENT TEMPRATURE IN CELISUS
      - AFTER WE GET T CURREBT WE COMPARE IT WITH TLOW  AND THIGH, WE SET IT INITIAL TO BE BETWEEN 20 - 100 C:
                      - IF CURRENT TEMP > THIGH : CLOSE THE HEATER, OPEN THE FAN, GET THE MOTOR TO CCW DIR OPEN RED LED
                      - IF CURRENT TEMP < THIGH : OPEN THE HEATER, CLOSE THE FAN, GET THE MOTOR TO CW DIR OPEN BLUE LED
                      - IF CURRENT TEMP IS WITHIN THE RANGE OPEN GREEN LED
      - OUR HARDWAERE COMPONENTS:
                                RELAY TO CONTROL THE HEATER
                                TUNGESTIN LAMP 100W ACT ACT AS OUR HEATER
                                H-BRIDGE L298 TO CONTROL THE FAN AND MOTOR
                                3 LEDS
                                BLUETOOTH MODULE TO SET TEMP RANGE
                                ARDUINO MEGA
                                5V/1A ADAPTER FOR THE MOTOR AND THE FAN
*/
#include "func.h"

void setup()
{
  initAdaotiveTempControl();
}

void loop()
{
  adaotiveTempControl();
}