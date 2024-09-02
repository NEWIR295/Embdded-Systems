# Industrial Instrumentation EPMN-303 Project

## Project 4: Temperature Control

### Supervisor
- **Dr. Ahmed Kamel**

### Teaching Assistants
- **Eng. Abd El Fatah**
- **Eng. Osama Morsi**

### Team Members
- **Mohamed Abd El Twab Newir**

## Project Overview
This project aims to set a temperature range and maintain the current temperature within that range.

### Key Components
- **NTC 10 KΩ Thermistor:** Used to measure the current temperature.
- **Wheatstone Bridge:** The thermistor is placed as R4 in the bridge.
- **Signal Conditioning Circuit:** Designed to read the current temperature.
- **Operational Amplifiers (UA-741):** 
  - 2 ICs as voltage followers.
  - 2 ICs as differential amplifiers.
  - 1 IC as an inverting amplifier.

### Circuit Design & Equations
1. **Wheatstone Bridge Output (Vab):**
    ```
    Vab = Vs((R2R3 - R4R1) / ((R2 + R4)(R3 + R1)))
    ```
- Vs = 9V, R1 = R2 = 10 KΩ, R3 = 11.44 KΩ (to null the bridge).
- Vab range: -3.942V to 4.743V.
- Differential amplifier with gain 1 used to get Vab.

2. **Output Voltage (Vo):**
    ```
    Vo = mVab + c    
    ```
- To protect the Arduino (Vin ≤ 5V), the range is set between 0 to 4.5V.
- m = 0.518, c = 2.042.
- Vo = 0.518(Vab - (-3.942)).

3. **Resistor Calculation (R2):**
- Using a potentiometer as R2 due to its non-standard value:
  ```
  R2/R1 * (V2 - V1) 
  ```
- R1 = 10 KΩ, R2 = 5.18 KΩ.
- -3.942V obtained from the inverting amplifier:
  ```
  3.942 = R2/R1 * 9
  ```
- R2 = 4.38 KΩ (also adjusted with a potentiometer).

### Temperature Calculation
1. **Inverse Equations:**
- Convert analog signal to digital:
  ```
  Vo = (VinA / 1023) * 4.5
  ```
- Obtain the output from the bridge after the first differential amplifier:
  ```
  Vab = (Vo - 2.042) / 0.518
  ```
- Calculate the sensor resistance (R4) from the bridge equation:
  ```
  R4 = (114.4 - 23.82 * Vab) / (10.0 + 2.382 * Vab)
  ```
- Determine the current temperature in Kelvin:
  ```
  T = 1.0 / ((ln(R4 / 10.0) / B) + (1.0 / 298.15))
  ```
  - B (constant for NTC 10 KΩ thermistor) = 3950.
  - Convert to Celsius: 
    ```
    T = T - 273.15
    ```

2. **Temperature Control Logic:**
- Initial temperature range: **20°C to 100°C**.
- **If current temperature > T_high:**
  - Close the heater.
  - Open the fan.
  - Set motor to counter-clockwise (CCW) direction.
  - Turn on the red LED.
- **If current temperature < T_low:**
  - Open the heater.
  - Close the fan.
  - Set motor to clockwise (CW) direction.
  - Turn on the blue LED.
- **If current temperature is within the range:**
  - Turn on the green LED.

### Hardware Components
- Relay to control the heater.
- Tungsten lamp (100W) as the heater.
- H-Bridge L298 to control the fan and motor.
- 3 LEDs.
- Bluetooth module to set the temperature range.
- Arduino Mega.
- 5V/1A adapter for the motor and fan.
