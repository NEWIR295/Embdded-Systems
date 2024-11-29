/*
  Author: Mohamed Newir
  File Name: main.cpp
  Date: 27/11/2024
  Description: Water level control System
*/

#include <Arduino.h>

/* Define the pins for the Level sensors */
#define WATER_LEVEL_SENSOR_LOW_PIN 8
#define WATER_LEVEL_SENSOR_HIGH_PIN 12

/* Define the pins for the Pump and Valve */
#define PUMP_PIN 6
#define VALVE_PIN 7

/* Sensor active is High since it is a Normal open sensor */
#define SENSOR_ACTIVE HIGH

/* to prevent debouncing effect */
#define INTERVAL 1000 // 1 second

unsigned long previousMillis = 0;
unsigned long currentMillis = 0;

/* Global variables to store the water level sensors values*/
int lowLevelSensorCurrent = 0;
int lowLevelSensorPrev = 0;
int highLevelSensorCurrent = 0;
int highLevelSensorPrev = 0;

void setup()
{

  Serial.begin(9600);

  /* Set the pins as input for the sensors */
  pinMode(WATER_LEVEL_SENSOR_LOW_PIN, INPUT);
  pinMode(WATER_LEVEL_SENSOR_HIGH_PIN, INPUT);

  /* Set the pins as output for bot pump and valve */
  pinMode(PUMP_PIN, OUTPUT);
  pinMode(VALVE_PIN, OUTPUT);

  // Ensure actuators are initially off
  digitalWrite(PUMP_PIN, LOW);
  digitalWrite(VALVE_PIN, LOW);

  // Initialize previous sensor states
  lowLevelSensorPrev = digitalRead(WATER_LEVEL_SENSOR_LOW_PIN);
  highLevelSensorPrev = digitalRead(WATER_LEVEL_SENSOR_HIGH_PIN);
}

void loop()
{

  currentMillis = millis();

  if (currentMillis - previousMillis >= INTERVAL)
  {

    // Read the sensor states
    lowLevelSensorCurrent = digitalRead(WATER_LEVEL_SENSOR_LOW_PIN);
    highLevelSensorCurrent = digitalRead(WATER_LEVEL_SENSOR_HIGH_PIN);

    /*
      control logic:
      - If the low level sensor is inactive (i.e., water level is low) , turn on the pump and turn off the valve
      - If the high level sensor is active (i.e., water level is high) , turn off the pump and turn on the valve
    */
    if (lowLevelSensorCurrent != SENSOR_ACTIVE && lowLevelSensorPrev == SENSOR_ACTIVE)
    {
      Serial.println("PUMP on");
      digitalWrite(VALVE_PIN, LOW);
      digitalWrite(PUMP_PIN, HIGH);
    }
    else if (highLevelSensorCurrent == SENSOR_ACTIVE && highLevelSensorPrev != SENSOR_ACTIVE)
    {
      Serial.println("VALVE on");
      digitalWrite(PUMP_PIN, LOW);
      digitalWrite(VALVE_PIN, HIGH);
    }
    // else
    // {
    //   // Default state: Turn off both actuators
    //   Serial.println("System idle");
    //   digitalWrite(PUMP_PIN, LOW);
    //   digitalWrite(VALVE_PIN, LOW);
    // }
    highLevelSensorPrev = highLevelSensorCurrent;
    lowLevelSensorPrev = lowLevelSensorCurrent;

    previousMillis = currentMillis;
  }
}
