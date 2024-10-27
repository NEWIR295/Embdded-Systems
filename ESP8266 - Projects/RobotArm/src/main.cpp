#include <Arduino.h>
#include <Servo.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

/* Wifi  settings */
/* Put your SSID & Password */
const char *ssid = "NEWIRESP8266"; // Enter SSID here
const char *password = "12345678"; // Enter Password here

/* Put IP Address details */
IPAddress local_ip(192, 168, 1, 1);
IPAddress gateway(192, 168, 1, 1);
IPAddress subnet(255, 255, 255, 0);

ESP8266WebServer server(80);

/*  Define the pin connections for the 4 DOF robot arm servo motors */
#define SERVO_1 5 /* Base  servo motor */
#define SERVO_2 4 /* Shoulder servo motor */
#define SERVO_3 0 /* Elbow servo motor */
#define SERVO_4 2 /* Gripper  servo motor */

/* Define the servo motor objects */
Servo servo1;
Servo servo2;
Servo servo3;
Servo servo4;

int angle1 = 90;
int angle2 = 90;
int angle3 = 90;
int angle4 = 90;

void setup()
{

  Serial.begin(38400); /* Start serial for debug output */

  /* setup the servo motor pins */
  servo1.attach(SERVO_1);
  servo2.attach(SERVO_2);
  servo3.attach(SERVO_3);
  servo4.attach(SERVO_4);

  /* set the initial servo motor angles */
  servo1.write(angle1);
  servo2.write(angle2);
  servo3.write(angle3);
  servo4.write(angle4);

  /* set ESP as our  access point */
  WiFi.softAP(ssid, password);                  /* Start Access Point */
  WiFi.softAPConfig(local_ip, gateway, subnet); /* Set IP Address */
  delay(100);

  /* Define web server routes */
  server.on("/", handleRoot);
  server.on("/update", handleUpdate);
  server.onNotFound(handleNotFound);

  /* Start the web server */
  server.begin();
}

void loop()
{
  server.handleClient(); /*  handle incoming requests */
}

/* Handle Root Page Request */
void handleRoot()
{
  server.send(200, "text/html", generateHTML());
}

/* Handle Servo Angle Updates */
void handleUpdate()
{

  /*  Read the servo angles as String then convert it to intger to update servo position */
  if (server.hasArg("servo1"))
  {
    angle1 = server.arg("servo1").toInt();
    if (angle1 >= 0 && angle1 <= 180)
    {
      servo1.write(angle1);
    }
  }
  if (server.hasArg("servo2"))
  {
    angle2 = server.arg("servo2").toInt();
    if (angle2 >= 0 && angle2 <= 180)
    {
      servo2.write(angle2);
    }
  }
  if (server.hasArg("servo3"))
  {
    angle3 = server.arg("servo3").toInt();
    if (angle3 >= 0 && angle3 <= 180)
    {
      servo3.write(angle3);
    }
  }
  if (server.hasArg("servo4"))
  {
    angle4 = server.arg("servo4").toInt();
    if (angle4 >= 0 && angle4 <= 180)
    {
      servo4.write(angle4);
    }
  }

  /* Send Response */
  server.send(200, "application/json", 
              "{ \"servo1\": " + String(angle1) +
              ", \"servo2\": " + String(angle2) +
              ", \"servo3\": " + String(angle3) +
              ", \"servo4\": " + String(angle4) + " }");
}

/* Handle 404 Not Found */
void handleNotFound()
{
  server.send(404, "text/plain", "Not Found");
}

/* 
* Generate HTML Web Page 
* Allows dynamic servo angles change 
*/
String generateHTML() {
  String html = "<!DOCTYPE html><html><head>";
  html += "<meta name='viewport' content='width=device-width, initial-scale=1.0'>";
  html += "<title>4-DOF Robot Arm Control</title>";
  html += "<style>body { font-family: Arial; text-align: center; margin-top: 30px; }";
  html += "input[type='range'] { width: 80%; margin: 10px 0; }</style>";

  html += "<script>function updateServo(servo, angle) {";
  html += "var xhr = new XMLHttpRequest(); xhr.open('GET', '/update?' + servo + '=' + angle, true); xhr.send();";
  html += "}</script></head><body>";

  html += "<h1>4-DOF Robot Arm Control</h1>";
  html += "<p>Servo 1: <input type='range' min='0' max='180' value='" + String(angle1) +
          "' oninput=\"updateServo('servo1', this.value); document.getElementById('servo1Val').innerText = this.value;\"></p>";
  html += "<p>Angle: <span id='servo1Val'>" + String(angle1) + "</span></p>";

  html += "<p>Servo 2: <input type='range' min='0' max='180' value='" + String(angle2) +
          "' oninput=\"updateServo('servo2', this.value); document.getElementById('servo2Val').innerText = this.value;\"></p>";
  html += "<p>Angle: <span id='servo2Val'>" + String(angle2) + "</span></p>";

  html += "<p>Servo 3: <input type='range' min='0' max='180' value='" + String(angle3) +
          "' oninput=\"updateServo('servo3', this.value); document.getElementById('servo3Val').innerText = this.value;\"></p>";
  html += "<p>Angle: <span id='servo3Val'>" + String(angle3) + "</span></p>";

  html += "<p>Servo 4: <input type='range' min='0' max='180' value='" + String(angle4) +
          "' oninput=\"updateServo('servo4', this.value); document.getElementById('servo4Val').innerText = this.value;\"></p>";
  html += "<p>Angle: <span id='servo4Val'>" + String(angle4) + "</span></p>";

  html += "</body></html>";
  return html;  // return the generated HTML
}
