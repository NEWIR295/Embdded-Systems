
# Car Parking Sensor System

### By Mohamed Newir

## Description

This project implements a **Car Parking Sensor System** using the **ATmega32 microcontroller**, an ultrasonic sensor, LCD display, LEDs, and a buzzer. The system helps drivers avoid collisions by measuring the distance between the vehicle and nearby obstacles, providing real-time feedback through both visual and auditory indicators.

The system is designed to enhance parking safety by displaying the distance on an LCD and triggering LED and buzzer alerts based on proximity thresholds.

---

## Objective

The objective of this project is to design a parking assistance system that:
- **Measures the distance** between the vehicle and nearby obstacles using an ultrasonic sensor.
- **Displays the distance** on a 16x2 LCD in centimeters.
- **Provides LED and buzzer alerts** to guide the driver:
  - LED indicators show the obstacle's proximity.
  - The buzzer sounds when the object is dangerously close (≤ 5 cm).
- **Improves parking safety** by giving real-time feedback on distance and warnings to prevent collisions.

---

## Features

- **Ultrasonic Distance Measurement**:
    - Uses the **HC-SR04** ultrasonic sensor to measure the distance between the car and obstacles.
  
- **LCD Display**:
    - Shows the distance in centimeters.
    - Displays **"Stop"** if the distance is less than 5 cm.

- **LED Indicators**:
    - Three LEDs (Red, Green, Blue) light up based on the proximity of the obstacle:
      - **Distance ≤ 5 cm**: All LEDs flash (Red, Green, Blue), and the buzzer sounds.
      - **6 cm ≤ Distance ≤ 10 cm**: All LEDs ON (No buzzer).
      - **11 cm ≤ Distance ≤ 15 cm**: Red and Green LEDs ON, Blue LED OFF.
      - **16 cm ≤ Distance ≤ 20 cm**: Only Red LED ON.
      - **Distance > 20 cm**: All LEDs OFF.

- **Buzzer Alert**:
    - The buzzer activates when the obstacle is **5 cm or closer**.

---

## Components Used

- **Microcontroller**: ATmega32
- **Ultrasonic Sensor**: HC-SR04
- **LCD Display**: 16x2 in 4-bit mode
- **LEDs**: Red, Green, and Blue
- **Buzzer**: Provides auditory alert

---

## Pin Connections

- **ATmega32 Microcontroller**:
  - **Port A**:
    - PA1: LCD RS
    - PA2: LCD E
    - PA3–PA6: LCD Data (D4–D7)
  - **Port B**:
    - PC0: Red LED  
    - PC1: Green LED  
    - PC2: Blue LED
  - **Port C**:
    - PC5: Buzzer control via transistor  
  - **Port D**:
    - PD6: Echo (Ultrasonic Sensor)  
    - PD7: Trigger (Ultrasonic Sensor)

- **Ultrasonic Sensor**:  
  - Echo → PD6  
  - Trigger → PD7

---

## Operation

1. The ultrasonic sensor emits ultrasonic waves and listens for the reflection.
2. The **ATmega32** calculates the distance based on the time taken for the wave to return.
3. The LCD displays the measured distance in real-time.
4. The system updates LED and buzzer status based on predefined distance thresholds.

---

## Drivers Used

- **GPIO Driver**: Manages pin configurations.
- **ICU Driver**:
  - Configured to detect the rising edge and use **F_CPU/8** frequency.
  - Initializes within the ultrasonic driver to handle timing.
- **Buzzer Driver**:
  - Controls buzzer activation when the distance is ≤ 5 cm.
- **LCD Driver**:  
  - Operates in 4-bit mode to display distance and alerts.
- **Ultrasonic Driver**:  
  - Handles distance measurement and integrates with the ICU driver.

---

## How to Use

1. **Build the project** using an AVR toolchain (e.g., Atmel Studio or AVR-GCC).
2. **Upload the code** to the ATmega32 microcontroller.
3. **Connect the components** as per the pin connections described above or according to your hardware connections.
4. **Power up the system** and observe the real-time distance measurement on the LCD, along with LED and buzzer alerts.

---

## Contributor

This project was designed and implemented by:

- **Mohamed Newir** - Main Contributor  
  - [LinkedIn](https://www.linkedin.com/in/mohamed-newir-a8a572182/)

Feel free to explore, modify, and improve this project. If you have any suggestions or find any issues, feel free to open an issue or submit a pull request.

---

## License

This project is open-source and available under the [BSD-3 License](LICENSE).
