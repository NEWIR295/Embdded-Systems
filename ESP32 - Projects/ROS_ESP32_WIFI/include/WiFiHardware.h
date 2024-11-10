/*
    Author: Mohamed Newir
    File Description: This file contains the implementation of Wifi Node class.
    For further information, please refer  repo
*/


#ifndef ROS_ARDUINO_WIFI_HARDWARE_H_NEWIR
#define ROS_ARDUINO_WIFI_HARDWARE_H_NEWIR

#include <Arduino.h>
#include <WiFi.h>

class WiFiHardware {
public:

  /*
    Constructor that accepts WiFi credentials and ROS server information
  */
  WiFiHardware() : server_ip(), server_port(0), ssid(nullptr), password(nullptr) {}

  /*
    Set connection with Newir Access Point
  */
  void setConnection(const char* ssid, const char* password, IPAddress server_ip, uint16_t server_port) {
    this->ssid = ssid;
    this->password = password;
    this->server_ip = server_ip;
    this->server_port = server_port;
  }

    /*
        Initialize Newir ESP32
    */
 void init() {
  // Start Wi-Fi connection
  WiFi.begin(ssid, password);
  int retries = 0;

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000); // Increase delay for retries
    retries++;

    // Limit the number of retries for connection
    if (retries > 20) { // Adjust as needed
      ESP.restart();  // Restart the ESP if it fails to connect
    }
  }

  // Connect to ROS server
  connectToServer();
}

    /*
        read data from Newir Machine
    */
  int read() {
    if (client.connected() && client.available()) {
      return client.read();
    }
    return -1;
  }

    /*
        write data to send to Newir Machine
    */
  void write(const uint8_t* data, int length) {
    if (client.connected()) {
      client.write(data, length);
    } else {
      reconnect();
    }
  }

  unsigned long time() {
    return millis();
  }

protected:
  WiFiClient client;
  IPAddress server_ip;
  uint16_t server_port;
  const char* ssid;
  const char* password;

     /*
        Connect with Newir Hotspot
    */
  void connectToServer() {
    while (!client.connect(server_ip, server_port)) {
      delay(1000);
    }
  }

    /*
        in case we lost connection with Newir Hotspot
    */
  void reconnect() {
    if (!client.connected()) {
      client.stop();
      connectToServer();
    }
  }
};

#endif
