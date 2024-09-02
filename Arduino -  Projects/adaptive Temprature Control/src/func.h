#ifndef ADAPTIVE_TEMP_CTRL
#define ADAPTIVE_TEMP_CTRL

// used libraries
#include <Arduino.h>
#include <math.h>
#include <LiquidCrystal_I2C.h>

// arduino pins
#define vScPin A0      // input signal from signal conditioning signal
#define redLed 27      // led for hot T
#define blueLed 24     // led for cold T
#define greenLed 26    // led for T within the range
#define in1m 4         // in3 for l298 motor driver
#define in2m 5         // in4 for l298 motor driver
#define fanPin2 7      // in1 for l298 motor driver
#define fanPin1 6      // set in2 to low for l298 motor driver
#define tungLampPin 12 // relay in pin

void initAdaotiveTempControl(void);
void heater(bool condition);
void fan(bool condition);
void motorDir(bool dir);
double getTemptature(double vInA);
void adaotiveTempControl(void);

#endif