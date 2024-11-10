/*
  File Name: main.cpp
  Author: Mohamed Newir
  Project Description: Publish String over ESP32 Bluetooth
  Reference: I have Included BluetoothHardware.h from https://github.com/sktometometo/M5Stack_Bluetooth_rosserial_example.git Repo
*/


#include <Arduino.h>

/* essential libraries */
#include <ros.h>
#include <BluetoothHardware.h>
#include <std_msgs/String.h>

/* time interval */
#define INTERVAL 1000
unsigned long prevTime = 0; //init prev time with 0

/* ros node handle */
ros::NodeHandle_<BluetoothHardware> nh; /* node handle instance  for bluetooth connection with ros */

std_msgs::String msg; /* string data type */
ros::Publisher espPub("newir", &msg); /* Publisher definition  */

/* String to be Published */
char NEWIR[] = "Yeah, Newir make it" ;

/* counter */
static char count_s[20];
static int count = 0;


void setup()
{
  setCpuFrequencyMhz(80); /* set esp32 frequency to 80MHz */
  // nh.getHardware()->setBaud(38400); // we don't need it since we have included  BluetoothHardware template
  nh.initNode(); /* initialize ros node */
  nh.advertise(espPub); /* advertise the publisher */

  /* wait till our ESP32 node connected with our ROS Master */
  while (not nh.connected()) {
      nh.spinOnce();
      delay(100);
  }
}

void loop()
{
  

  /* Check if ESP32 node connected to ROS master Before Publishing String Topic */
  if(nh.connected()){
    unsigned long currentTime = millis(); // get the current time
    if (currentTime - prevTime > INTERVAL) {  // check if enough time has elapsed since the last Publisher
      msg.data = itoa(count,count_s,10);
      espPub.publish(&msg);
      msg.data = NEWIR;
      espPub.publish(&msg); /* publishing string msg */
      count++;
      prevTime = currentTime;
    }
  }
  else{
    // Serial.println("ESP32 Node is not connected to ROS Master");
  }
  
  nh.spinOnce();
}