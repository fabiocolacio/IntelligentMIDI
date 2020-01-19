#include <Keypad_Matrix.h>
/*
 4 pins for col (output)
  3 pins for rows (input)
  7 total pins necessary, pins are pulled high until pressed 

*/

const byte ROWS = 3;
const byte COLS = 4;

// how the keypad has its keys laid out
const char keys[ROWS][COLS] = {
  {'1', '2', '3', '4'},
  {'5', '6', '7', '8'},
  {'9', 'A', 'B', 'C'},
};

const byte rowPins[ROWS] = {6, 7, 8}; //connect to the row pinouts of the keypad
const byte colPins[COLS] = {2, 3, 4, 5}; //connect to the column pinouts of the keypad

Keypad_Matrix kpd = Keypad_Matrix( makeKeymap (keys), rowPins, colPins, ROWS, COLS );

void keyDown (const char which)
  {
  Serial.print (F("Key down: "));
  Serial.println (which);
  if (which >= '0' && which <= '9')
    {
    if (kpd.isKeyDown ('1'))
      Serial.println ("1 is down as well.");
    if (kpd.isKeyDown ('2'))
      digitalWrite(9, HIGH);
      Serial.println ("2 is down as well.");
    if (kpd.isKeyDown ('3'))
      Serial.println ("3 is down as well.");
    if (kpd.isKeyDown ('4'))
      Serial.println ("4 is down as well.");
    if (kpd.isKeyDown ('5'))
      Serial.println ("5 is down as well.");
    if (kpd.isKeyDown ('6'))
      digitalWrite(9, LOW);
      Serial.println ("6 is down as well.");
    if (kpd.isKeyDown ('7'))
      Serial.println ("7 is down as well.");
    if (kpd.isKeyDown ('8'))
      Serial.println ("8 is down as well.");
    if (kpd.isKeyDown ('9'))
      Serial.println ("9 is down as well.");
    if (kpd.isKeyDown ('A'))
      Serial.println ("10 is down as well.");
    if (kpd.isKeyDown ('B'))
      Serial.println ("11 is down as well.");
    if (kpd.isKeyDown ('C'))
      Serial.println ("12 is down as well.");
  }
  }

void keyUp (const char which)
  {
  Serial.print (F("Key up: "));
  Serial.println (which);
  }


void setup() 
{
  pinMode(9, OUTPUT);
  Serial.begin (115200);
  Serial.println ("Starting.");
  kpd.begin ();
  kpd.setKeyDownHandler (keyDown);
  kpd.setKeyUpHandler   (keyUp);
}

void loop() 
{
  kpd.scan ();
}
