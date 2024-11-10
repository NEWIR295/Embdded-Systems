/*
  File Name: main.cpp
  Author: Mohamed Newir
  Project Description: Publish String over ESP32 WiFi to ROS
*/

#include <Arduino.h>

/* essential libraries */
#include "WiFi.h"
#include <ros.h>
#include <std_msgs/String.h>
#include <ESP32Hardware.h>

/* WiFi credentials and ROS master IP */
const char *ssid = "BLACK_KNIGHT529";     // Replace with your WiFi SSID
const char *password = "N_2024_B";       // Replace with your WiFi password 
IPAddress server_ip(192, 168, 140, 86); // Replace with your ROS master's IP
const uint16_t server_port = 11411;    // Port of ROS master

/* time interval */
#define INTERVAL 1000
unsigned long prevTime = 0;

/* ros node handle */
ros::NodeHandle_<Esp32Hardware> nh; /* node handle instance for WiFi connection with ros */

std_msgs::String msg;                 /* string data type */
ros::Publisher espPub("newir", &msg); /* Publisher definition */

/* String to be Published */
char NEWIR[] = "Yeah, Newir made it over WiFi!";

/* counter */
static char count_s[20];
static int count = 0;

void setup()
{
  setCpuFrequencyMhz(80); /* set ESP32 frequency to 80MHz */
  
  // Set Wi-Fi credentials and ROS server details
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
  }
  
  nh.getHardware()->setConnection(server_ip, server_port); /* Set ROS server details */

  // Initialize ROS
  nh.initNode();        /* initialize ROS node */
  nh.advertise(espPub); /* advertise the publisher */

  /* Wait till our ESP32 node connects to our ROS Master */
  while (!nh.connected())
  {
    nh.spinOnce();
    delay(100);
  }
}

void loop()
{
  /* Check if ESP32 node is connected to ROS master before publishing */
  if (nh.connected())
  {
    unsigned long currentTime = millis(); // get the current time
    if (currentTime - prevTime > INTERVAL)
    { // check if enough time has elapsed since the last publish
      msg.data = itoa(count, count_s, 10);
      espPub.publish(&msg);
      msg.data = NEWIR;
      espPub.publish(&msg); /* publishing string msg */
      count++;
      prevTime = currentTime;
    }
  }
  else
  {
    /*
      in case ESP32 Node is not connected to ROS Master
    */
    WiFi.reconnect(); /* try to reconnect */
  }

  nh.spinOnce();
}

