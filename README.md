# WSU_RoboticsClub_PIDTutorial
All the info you need to get ready for the robotics club tutorial

## Learning about PID and the Zeigler-Nichols method for tuning (before the tutorial)
1. Read the PDF in this repository about PID and Zeigler Nichols
2. Come ready to implement this tuning method on your motor.

## Installing Arduino software and PID packages (before tutorial)
1. Download and install the Arduino IDE (I am using version 1.8.5)
2. Install the Chipkit board package in the ArduinoIDE
   * From the Arduino IDE, select Tools->Board->Board Manager
   * Search for Chipkit and install the latest board package
   * Restart Arduino IDE
3. Install the Arduino PID library
   * From the Arduino IDE, select Sketch->Include Library->Manage Libraries
   * Search for PID v1.2.1 by Brett Beauregard and install the library
   * Restart Arduino IDE

## Setting up your Chipkit and motor shield (at the tutorial)
1. If not already done, stack the Motor Shield on top of the Chipkit
2. Ensure jumper JP5 is installed
3. Install a jumper wire from +VM header pin to the +J14 header pin. (Ask for help if you can't find it)
4. Plug the cable connecting the DC motor to the motor shield in header J3

## Testing the example code that (at the tutorial)
1. Download the PIDFromQuadrature sketch from this repository
2. Plug the chipkit into your computer via USB and set the correct serial port that appears (if you have never ins
   * If you have never used a USB->Serial device before, you may need to install drivers (see https://chipkit.net/wiki/index.php?title=ChipKIT_Drivers)
3. Load the sketch, compile, and load to the board
4. Open the serial port in the ArduinoIDE. You should see an output showing the current position setpoint, the current reading input from the quadrature sensor, and the current output to the motor driver.
5. You can send the character 'a' or 'z' to the chipkit to increase or decrease the setpoint

