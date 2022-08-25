#include <Arduino.h>
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

// Joystick 1 inputs
#define j1BIn 11  // Digital pin 11
#define j1XIn A10 // D10 or A10
#define j1YIn A9  // D9 or A9

// Joystick 2 inputs
#define j2BIn 7  // D7
#define j2XIn A8 // D8 or A8
#define j2YIn A7 // D6 or A7 - *Need to make sure we are using the digital numbers

// Potentiometer
#define potIn A6 // D4 or A6 - *Need to make sure we are using the digital numbers

// Sound Buttons 1-8
#define s1In 18 // D18
#define s2In 19 // D19
#define s3In 20 // D20
#define s4In 21 // D21
#define s5In 22 // D22
#define s6In 23 // D23
#define s7In 5  // D5
#define s8In 13 // D13

// Other
#define modeIn 2   // D2 driving/positioning mode switch //!REDO
#define powerIn 12 // D12

//* variable to store previous values
bool sound1Pressed = true;
bool sound2Pressed = true;
bool sound3Pressed = true;
bool sound4Pressed = true;
bool sound5Pressed = true;
bool sound6Pressed = true;
bool sound7Pressed = true;
bool sound8Pressed = true;

// The joysticks are on the 0-255 scale, not the 0-1023
int joystick1XValue = 126;
int joystick1YValue = 126;
int joystick2XValue = 126;
int joystick2YValue = 126;
bool joystick1ButtonPressed = true;
bool joystick2ButtonPressed = true;

bool drivingMode = true;
bool powerOn = true;

struct Data_Transmission
{
  byte soundButtons; // A 8-bit number representing the sound buttons 1-8. 1=pressed
  byte j1X;
  byte j1Y;
  byte j2X;
  byte j2Y;
  byte pot1;
  byte other; // 8 bits devoted to other functions:
  // bit 0: mode selection (0 = Driving, 1 = positioning)
  // bit 1: power off (1 = power off arduino)
  // bit 2: joystick 1 button
  // bit 3: joystick 2 button
};

Data_Transmission data; // The data package that we're going to send

void setup()
{
  // put your setup code here, to run once:

  //*Setting up inputs

  // Joystick buttons
  pinMode(j1BIn, INPUT_PULLUP);
  pinMode(j2BIn, INPUT_PULLUP);

  // Sound buttons
  pinMode(s1In, INPUT_PULLUP);
  pinMode(s2In, INPUT_PULLUP);
  pinMode(s3In, INPUT_PULLUP);
  pinMode(s4In, INPUT_PULLUP);
  pinMode(s5In, INPUT_PULLUP);
  pinMode(s6In, INPUT_PULLUP);
  pinMode(s7In, INPUT_PULLUP);
  pinMode(s8In, INPUT_PULLUP);
}

void loop()
{

  // if something has changed:
  data.j1X = map(analogRead(j1XIn), 0, 1023, 0, 255);
  data.j1Y = map(analogRead(j1YIn), 0, 1023, 0, 255);
  data.j2X = map(analogRead(j2XIn), 0, 1023, 0, 255);
  data.j2Y = map(analogRead(j2YIn), 0, 1023, 0, 255);
  data.pot1 = map(analogRead(potIn), 0, 1023, 0, 255);
  data.soundButtons = (digitalRead(s1In) | (digitalRead(s2In) << 1) | (digitalRead(s3In) << 2) | (digitalRead(s4In) << 3) | (digitalRead(s5In) << 4) | (digitalRead(s6In) << 5) | (digitalRead(s7In) << 6) | (digitalRead(s8In) << 7));
  data.other = (digitalRead() | digitalRead() | digitalRead());
  // put your main code here, to run repeatedly:
}

bool updateData()
{
  // Checks if any of the inputs have changed

  bool nothingChanged = true;
  int j1xTemp = map(analogRead(j1XIn), 0, 1023, 0, 255);
  int j1yTemp = map(analogRead(j1YIn), 0, 1023, 0, 255);
  int j2xTemp = map(analogRead(j2XIn), 0, 1023, 0, 255);
  int j2yTemp = map(analogRead(j2YIn), 0, 1023, 0, 255);
  int potTemp = map(analogRead(potIn), 0, 1023, 0, 255);

  // For the record, these have pull-up resistors so 1 = not pressed, 0 = pressed
  bool s1PressTemp = digitalRead(s1In);
  bool s2PressTemp = digitalRead(s2In);
  bool s3PressTemp = digitalRead(s3In);
  bool s4PressTemp = digitalRead(s4In);
  bool s5PressTemp = digitalRead(s5In);
  bool s6PressTemp = digitalRead(s6In);
  bool s7PressTemp = digitalRead(s7In);
  bool s8PressTemp = digitalRead(s8In);

  bool j1ButtonTemp = true;
  bool j2ButtonTemp = true;

  if (abs(joystick1XValue - j1xTemp) >= 8 || abs(joystick1YValue - j1yTemp) >= 8 || joystick1ButtonPressed != j1ButtonTemp) // If the x or y value has changed by at least 8 or the button state has switched
  {                                                                                                                         // Checking Joystick 1 X, Y, button
    nothingChanged = false;
  }
  if (abs(joystick2XValue - j2xTemp) >= 8 || abs(joystick2YValue - j2yTemp) >= 8 || joystick2ButtonPressed != j2ButtonTemp) // If the x or y value has changed by at least 8 or the button state has switched
  {                                                                                                                         // Checking Joystick 2 X, Y, button
    nothingChanged = false;
  }
  if ()
  { // Checking sound and other multiplexed buttons

    nothingChanged = false;
  }
}