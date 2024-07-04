# AHRS-IMU/gamepad-tracker (macOS - WarThunder/X-plane)
Created as an addition to AHRS Razor tracker, aim to bring it to macOS (via gamepad/joystick functionality - will work with selected games only).


As EDTracker is no longer supported and has limited options in terms of Sensors (6050 & 91(2)50 only). The 6050 option works fine for first 5 minutes, but has a lot of drift caused by temperature changes, the option with 9250 - didn't manage to run due to a poor sensor. I needed the same functionality i.e. gamepad outut, as EDTracker has, for another project.

The original project is RAZOR AHRS here: https://sites.google.com/site/diyheadtracking/home/5dof-tracker 

Has a much broader sensor selection - over 12 options, can use 5DOF and 3DOF configs, wireless (battery powered).

This code is just an add-on to convert degrees into axis movements to use as a substitution for EDTracker to play certain games on MacOS with head tracking (e.g. flight sims). Arduino Joystick library by Hieronimus has been used.

The original project uses OpenTrack protocol and works like a charm by itself, but OpenTrack is not an option on macOS because of a lack of support.

# Usage
Compile the original project, and calibrate sensors. Make sure the secure wires connection (poor connection may cause troubles with sensor readings, use breadboard for the initial testing only, but for calibration, it won't work as you will need to calibrate the magnetometer, so make sure you calibrate it with a completed device). 

Save calibration values into Arduino memory. 

Put the code into the corresponding sections of the original code and recompile. After code uploading new controller should appear in game devices. At this point Head tracker is usable to game. You may concider to rename your board as well.

Angle limits for head movements could be changed in map function.

I added a button to recenter the tracker position (tied to Pin 7). Properly calibrated sensors will stay centered, button is needed at the first launch or to trim the head position corresponding to the body position during the game. Still the device can be used on a Win machines as originally designed, but additionally, you will have Gamepad connected (my requirements were 2 axes only, so it is a 2DOF tracker - Yaw and Pitch).

Tested on macbook air M1 in Warthunder and X-plane games. 

# Known issues
For initial calibration Win machine is needed (as it will write the EEPROM data), modification of gamepad code could be done on Mac machine afterwards.
You may need to launch IDE and monitor the output first, before opening the game. You can use Serial monitor to send the commands into the tracker as well.
Joystick should be calibrated in the game settings to correctly show the max and min head movements. It is recommended to turn off autocentering and apply some deadzone
On Leonardo board code may stutter or board may stuck.
