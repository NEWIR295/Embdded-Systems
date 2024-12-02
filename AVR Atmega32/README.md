# AVR Programmer access Setup on Linux 

This guide will help you setup an AVR programmer on a Linux machine or to allow your virtual machine (VM) on linux machineto recognize it.

## Steps

1. **Install avr toolchain and plugins**
   - Open a terminal and run the following command to install avr toolchain:
     ```
     $ sudo apt-get install gcc-avr binutils-avr gdb-avr avr-libc avrdude
     ```
     
2. **Verify Device Connection**
   - Open a terminal and run the following command to check if the AVR programmer is connected:
     ```
     $ lsusb
     ```
   - You should see an output similar to the following:
     ```
     Bus 001 Device 005: ID 16c0:05dc Van Ooijen Technische Informatica shared
     ```
   - Note the `idVendor` and `idProduct` values (`16c0` and `05dc` in this example) as you will need them in the next steps.

3. **Grant Device Permission**
   - Open the terminal and edit the USB rules file:
     ```
     $ sudo nano /etc/udev/rules.d/60-usbasp.rules
     ```
   - Add the following line to the file, replacing `idVendor` and `idProduct` with the values specific to your AVR programmer:
     ```
     $ SUBSYSTEM=="usb", ATTR{idVendor}=="16c0", ATTR{idProduct}=="05dc", MODE="0666"
     ```
   - Save the file and exit nano.

4. **Reload udev Rules**
   - In the terminal, run the following commands to reload the udev rules and trigger the changes:
     ```
     $ sudo udevadm control --reload-rules
     $ sudo udevadm trigger
     ```
   - Unplug and replug the USBasp device.

5. **Add User to linux and vboxusers Group**

   - Run the following command to add your user to Linux machine:
     ```
     $ sudo usermod -aG vboxusers $USER
     ```

   - Run the following command to add your user to the `vboxusers` group:
     ```
     $ sudo usermod -aG vboxusers $USER
     ```

6. **Reboot the System**
   - Reboot your machine. After rebooting, the AVR programmer should appear in both  your linux machine or virtual machine.

---

Following these steps should enable your Linux system to recognize the AVR programmer within your Linux or virtual machine environment.
