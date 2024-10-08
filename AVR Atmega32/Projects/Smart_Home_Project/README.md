# Smart Home Automation System

### By Mohamed Newir

## Description

This project implements a **Smart Home Automation System** using the **ATmega32** microcontroller. The system is designed to automate the control of lighting, fan speed, and fire detection based on real-time environmental conditions. It utilizes various sensors (LDR, LM35, Flame Sensor) to provide an intelligent and safe living environment.

The key components of the system include:
- **Lighting Control**: Adjusts LED brightness based on ambient light.
- **Fan Speed Control**: Automatically regulates fan speed according to the room temperature.
- **Fire Detection System**: Detects fire and triggers a critical alert.
- **LCD Display**: Provides real-time feedback on system status including temperature, light intensity, and fan status.

This project is built with efficiency and real-time responsiveness in mind, using an interrupt-based approach for critical fire detection.

---

## Objective

The objective of this project is to design and implement a smart home system that:
- **Automatically controls lighting** based on the ambient light detected by an LDR sensor.
- **Adjusts fan speed** proportionally to room temperature using the LM35 temperature sensor.
- **Detects fire** with a flame sensor, activating a buzzer and alerting the user via an LCD display.
- **Displays real-time information** such as fan status, temperature, and light intensity on a 16x2 LCD.

---

## Features

- **Automatic Lighting Control**:
    - Based on the LDR sensor readings, the system controls three LEDs according to light intensity thresholds.
    - Light Intensity < 15%: All three LEDs (Red, Green, Blue) are ON.
    - Light Intensity 16–50%: Red and Green LEDs are ON.
    - Light Intensity 51–70%: Only the Red LED is ON.
    - Light Intensity > 70%: All LEDs are OFF.
  
- **Automatic Fan Speed Control**:
    - The system automatically adjusts the fan speed using **PWM** based on the room temperature.
    - Temperature ≥ 40°C: Fan runs at 100% speed.
    - Temperature 35°C to < 40°C: Fan runs at 75% speed.
    - Temperature 30°C to < 35°C: Fan runs at 50% speed.
    - Temperature 25°C to < 30°C: Fan runs at 25% speed.
    - Temperature < 25°C: Fan is turned OFF.

- **Fire Detection and Alert**:
    - The flame sensor detects a fire and triggers an immediate alarm.
    - The system activates a buzzer and displays a "Critical Alert!" message on the LCD.
    - The system remains in alert mode until the fire is no longer detected.

- **LCD Display**:
    - Provides real-time feedback:
        - **Fan Status**: "FAN is ON" or "FAN is OFF".
        - **Temperature**: Displayed in degrees Celsius.
        - **Light Intensity**: Displayed as a percentage.

---

## Components Used

- **Microcontroller**: ATmega32
- **Light Sensor**: LDR (Light Dependent Resistor)
- **Temperature Sensor**: LM35
- **Flame Sensor**: Digital flame sensor
- **Fan**: Controlled via PWM and H-Bridge circuit
- **LEDs**: Red, Green, and Blue LEDs for light intensity indication
- **Buzzer**: Activates on fire detection
- **LCD**: 16x2 display in 8-bit mode for real-time feedback

---

## Project Structure

The project follows a **modular driver-based structure** where each component has its own dedicated driver, allowing easy maintenance and scalability.

### Drivers Included:
- **ADC Driver**: Converts analog sensor data to digital values.
- **GPIO Driver**: Handles basic pin input/output configurations.
- **PWM Driver**: Controls fan speed using PWM.
- **LCD Driver**: Displays real-time data on a 16x2 LCD.
- **LDR Driver**: Reads light intensity from the LDR sensor.
- **LM35 Driver**: Reads temperature data from the LM35 sensor.
- **Flame Sensor Driver**: Detects fire using a flame sensor.
- **Buzzer Driver**: Activates/deactivates the buzzer on fire detection.
- **LED Driver**: Controls the state of the Red, Green, and Blue LEDs.
- **Motor Driver**: Controls the direction and speed of the DC motor (fan).

---

## How to Use


1. **Build the project** using an AVR toolchain (e.g., Atmel Studio or AVR-GCC) and upload it to the ATmega32 microcontroller on the development board.

2. **Connect the hardware components** according to the circuit diagram (not provided here).

3. **Power up the system** and observe the automatic control of lighting, fan speed, and fire detection on the LCD display.

---



## Contributor

This project was designed and implemented by:

- **Mohamed Newir** - Main Contributor  
  - [LinkedIn](https://www.linkedin.com/in/mohamed-newir-a8a572182/)

Feel free to explore, modify, and improve this project. If you have any suggestions or find any issues, feel free to open an issue or submit a pull request.

---

## License

This project is open-source and available under the [BSD-3 License](LICENSE).


