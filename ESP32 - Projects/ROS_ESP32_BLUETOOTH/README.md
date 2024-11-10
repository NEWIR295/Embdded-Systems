# ROS Publisher Node for ESP32-S (Bluetooth Communication)

This repository contains the ROS Publisher Node for the ESP32-S, connected over Bluetooth to a ROS master. The node reads data from the ESP32 and publishes it to the ROS topic via Bluetooth serial communication.

## Setup Instructions

Before establishing the Bluetooth connection, you need to perform some initial setup in the terminal. Follow these steps:

1. Open a terminal and run the following commands to set up the Bluetooth connection:

```bash
$ sudo bluetoothctl
# power on
# scan on
# trust 00:19:09:01:1E:D1
# pair 00:19:09:01:1E:D1
# exit
```

2. Bind the Bluetooth serial device:

```bash
$ sudo rfcomm bind rfcomm1 00:19:09:01:1E:D1
```

3. Connect to bluetooth (optional)

```bash
$ sudo rfcomm connect rfcomm1 00:19:09:01:1E:D1
```

3. Give access to rfcomm1 

```bash
$ sudo chmod 666 rfcomm1 
```

5. Run the ROS serial node to connect to the ESP32 via Bluetooth:

```bash
$ rosrun rosserial_python serial_node.py _port:=/dev/rfcomm1 _baud:=38400
```

After performing these steps, your ESP32-S should be connected to the ROS master over Bluetooth, and you can start using the publisher node.

## Dependencies

- ROS (Robot Operating System)
- rosserial_python
- Bluetooth (obviously, for serial communication with ESP32)

## Author

- **Mohamed Newir**  
  [LinkedIn Profile](https://www.linkedin.com/in/mohamed-newir-a8a572182)

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.
