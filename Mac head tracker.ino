//This is an addition to the original Razor AHRS 5DOF Tracker firmware version [20191019]
//Include the code below as a part of original tracker file to the corresponding parts

//Include Joystic (Hieronimus) library https://github.com/MHeironimus/ArduinoJoystickLibrary/releases
#include "Joystick.h"
// Define the scaling factor for the angles
#define SCALE 127


// !!!!!Define joystick object
    Joystick_ HeadTracker(JOYSTICK_DEFAULT_REPORT_ID, JOYSTICK_TYPE_MULTI_AXIS, 0, 0, true, true, false, false, false, false, false, false, false, false);

    const int buttonPin = 7; // Use the appropriate pin number
    boolean buttonState = false;
    boolean lastButtonState = false;
    unsigned long lastDebounceTime = 0;
    unsigned long debounceDelay = 50; // Adjust debounce delay as needed
    

//Setup() function

void setup()
{

    // Initialize Joystick library
  HeadTracker.begin();
  HeadTracker.setXAxisRange( -127, 127);
  HeadTracker.setYAxisRange( -127, 127);

  pinMode(buttonPin, INPUT);
  digitalWrite(buttonPin, HIGH); // Enable internal pull-up resistor
  
  // Setup END
}

//================================================
// Main loop
//------------------------------------------------
void loop()
{

  int reading = digitalRead(buttonPin);
  
  if (reading != lastButtonState) {
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {
    if (reading != buttonState) {
      buttonState = reading;

      if (buttonState == LOW) {
        // Button is pressed, call the FixCenter() function
        FixCenter();
      }
    }
  }

  lastButtonState = reading;
    
  //map yaw and pitch angles to variables to reuse them as a values for axis:
  int newx = map(YPR_head[0], -17, 17, 0, SCALE); // Assuming -17 to 17 degrees range of head movement for yaw
  int newy = map(YPR_head[1], -10, 15, 0, SCALE); //

  //constrain values to the SCALE
  newx = constrain (newx, 0, SCALE);
  newy = constrain (newy, 0, SCALE);


  // Set the joystick axes values
  HeadTracker.setXAxis(newx);
  HeadTracker.setYAxis(newy);

  HeadTracker.sendState();
  
  //Use it for debug the output. If you can not see angle values (nan) - board has stuck, i found that reseting it might help (clear EEPROM, get back to the original sketch, open calibration values file, write to arduino and flash it with modified code again).
  Serial.print('\n');
  Serial.print("Yaw: ");
  Serial.print(YPR_head[0]);
  Serial.print("  Pitch: ");
  Serial.println(YPR_head[1]);
  Serial.print("X: ");
  Serial.print(newx);
  Serial.print("  Y: ");
  Serial.println(newy);
    

  delay(10);
  
}
