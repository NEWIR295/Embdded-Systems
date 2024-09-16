# Stopwatch with Dual Mode (Increment and Countdown) Using ATmega32 and Seven-Segment Display

## Project Overview

This project implements a digital stopwatch using an **ATmega32 microcontroller**. The stopwatch operates in two modes:
1. **Increment Mode** (Count Up Mode) - Default Mode: The stopwatch counts upwards, displaying hours, minutes, and seconds.
2. **Countdown Mode** (Count Down Mode): The stopwatch counts down from a when where it stopped or user-defined time and triggers a buzzer when the       countdown reaches zero.

The display is handled using six multiplexed seven-segment displays, and several push buttons provide user interaction for controlling the stopwatch.

---

## Features

- **Dual Mode Operation**:
  - **Increment Mode**: The stopwatch starts from 00:00:00 and counts upwards.
  - **Countdown Mode**: The stopwatch counts down from where it stopped or a user-specified time, and an alarm sounds when the countdown reaches zero.
  
- **Reset Function**: Resets the time to 00:00:00 in both modes.
  
- **Pause and Resume**: The stopwatch can be paused and resumed in both modes.

- **Time Adjustment**:
  - Hours, minutes, and seconds can be adjusted using dedicated buttons either by increment or decrement timer (HH:MM:SS).

- **Alarm/Buzzer**: A buzzer is triggered when the countdown reaches zero.

- **LED Indicators**:
  - **Red LED**: Indicates Increment Mode is active.
  - **Yellow LED**: Indicates Countdown Mode is active.

---

## Hardware Components

- **Microcontroller**: ATmega32 (16 MHz clock frequency).
- **Display**: Six multiplexed seven-segment displays (common anode), driven by a 7447 BCD to seven-segment decoder connected to the first 4 pins of **PORTC**.
- **Push Buttons**: 
  - **Reset Button**: Connected to PD2 (INT0) to reset the stopwatch.
  - **Pause Button**: Connected to PD3 (INT1) to pause the stopwatch.
  - **Resume Button**: Connected to PB2 (INT2) to resume the stopwatch.
  - **Mode Toggle Button**: Connected to PB7 to switch between increment and countdown modes.
  - **Hour, Minute, and Second Adjustments**:
    - Increment/Decrement buttons for hours, minutes, and seconds are connected to **PORTB**.
- **Buzzer**: Connected to PD0 and activated when the countdown reaches zero.
- **LED Indicators**: 
  - **Red LED** (PD4) indicates Increment Mode.
  - **Yellow LED** (PD5) indicates Countdown Mode.

---

## Pin Configuration

### Push Button Connections
- **Reset**: PD2 (INT0) – Falling edge.
- **Pause**: PD3 (INT1) – Rising edge.
- **Resume**: PB2 (INT2) – Falling edge.
- **Mode Toggle**: PB7.
- **Hour Adjustments**:
  - Increment: PB1.
  - Decrement: PB0.
- **Minute Adjustments**:
  - Increment: PB4.
  - Decrement: PB3.
- **Second Adjustments**:
  - Increment: PB6.
  - Decrement: PB5.

### Seven-Segment Display
- **PORTA**: Used to control which display is active via multiplexing (first 6 pins of PORTA).
- **PORTC**: Connected to the 7447 BCD to 7-segment decoder (first 4 pins of PORTC control the segments).

### Other Components
- **Buzzer**: PD0.
- **LEDs**: 
  - **Red LED**: PD4.
  - **Yellow LED**: PD5.

---

## Software Implementation

### Timer Configuration
- **Timer1** is configured in **CTC mode** to handle the time counting (increment or countdown).
- The timer is set to count every millisecond and accumulates time up to one second before updating the display.

### External Interrupts
- **INT0 (Reset)**: Configured for a falling edge to reset the stopwatch.
- **INT1 (Pause)**: Configured for a rising edge to pause the stopwatch.
- **INT2 (Resume)**: Configured for a falling edge to resume the stopwatch.

### Multiplexing the Seven-Segment Display
- The six seven-segment displays are multiplexed to save I/O pins.
- **PORTA** is used to enable/disable each display, and the **7447 decoder** on **PORTC** controls the segment data.
- The display is updated using a software-controlled multiplexing technique to refresh each display rapidly, creating the illusion of simultaneous output on all six digits.

### Mode Toggle (Count up vs Count down)
- The stopwatch starts in **Count up Mode** by default.
- When the **Mode Toggle Button** is pressed, it switches to **Count down Mode**, where the user can set the countdown time or from where it stopped. 
- The current mode is indicated by a **red LED** (Count up) or a **yellow LED** (Countdown).

---

## Usage Instructions

1. **Power On**: The stopwatch starts in Count up Mode by default.
2. **Mode Toggle**: Press the **Mode Toggle Button** (PB7) to switch between Count up Mode and Countdown Mode.
3. **Pause/Resume**: 
   - Press the **Pause Button** (PD3) to pause the stopwatch.
   - Press the **Resume Button** (PB2) to resume the stopwatch.
4. **Time Adjustment**: In Pause Mode, use the Hour, Minute, and Second adjustment buttons to set the desired countdown time.
5. **Reset**: Press the **Reset Button** (PD2) to reset the stopwatch.

---

## Operation Flow

1. **Countd up Mode**:
   - The time starts from `00:00:00` and increments continuously.
   - Use the **Pause Button** to pause and **Resume Button** to continue counting.

2. **Count down Mode**:
   - Set the desired countdown time using the Hour, Minute, and Second adjustment buttons.
   - Once the countdown reaches zero, the buzzer sounds.

---

## Code Overview

### Key Functions:

1. `multi7sergment(unsigned char currentTime, unsigned char activate7segment)`
   - Handles the multiplexing of the seven-segment displays by enabling each display and writing the current time values.

2. `ISR(TIMER1_COMPA_vect)`
   - Handles time counting in both Increment Mode and Countdown Mode.
   - In **Coubt up Mode**, it increments the seconds, minutes, and hours.
   - In **Count down Mode**, it decrements the time and triggers the buzzer when time reaches zero.

3. `interrupt_init()`
   - Initializes **Timer1** and the external interrupts (INT0, INT1, INT2) for reset, pause, and resume functionality.

4. `GPIO_init()`
   - Configures the I/O pins for the seven-segment display, push buttons, LEDs, and the buzzer.

---

## Supervisor
- **Eng. Mohamed Tarek**

## Contributors

- **Mohamed Newir** – Original Author
