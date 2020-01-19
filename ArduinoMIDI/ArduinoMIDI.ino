#include <stdint.h>
#include <Keypad_Matrix.h>
#include <ardumidi.h>

/*
 4 pins for col (output)
  3 pins for rows (input)
  7 total pins necessary, pins are pulled high until pressed 

*/

const byte ROWS = 3;
const byte COLS = 4;

// how the keypad has its keys laid out
const char keys[ROWS][COLS] = {
  {MIDI_F + MIDI_SHARP, MIDI_G + MIDI_SHARP, MIDI_A + MIDI_SHARP, MIDI_C + MIDI_SHARP},
  {MIDI_D + MIDI_SHARP, MIDI_E, MIDI_D, MIDI_C},
  {MIDI_B, MIDI_A, MIDI_G, MIDI_F},
};

const byte rowPins[ROWS] = {6, 7, 8}; //connect to the row pinouts of the keypad
const byte colPins[COLS] = {2, 3, 4, 5}; //connect to the column pinouts of the keypad

Keypad_Matrix kpd = Keypad_Matrix( makeKeymap (keys), rowPins, colPins, ROWS, COLS );

void keyDown (const char which)
{
  midi_note_on(0, which, 0xff);
}

void keyUp (const char which)
{
  midi_note_off(0, which, 0xff);
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
