#include <stdint.h>
#include <Keypad_Matrix.h>
#include <ardumidi.h>

/*
 4 pins for col (output)
  3 pins for rows (input)
  7 total pins necessary, pins are pulled high until pressed 

*/
 const int MAX_Y = 1024;
 const byte ROWS = 3;
 const byte COLS = 4;
 int octave[] = {13,12,11,10,9};

byte recording[1024];
int recLen = 0;
 
 int joyPin1 = 0;                 // slider variable connecetd to analog pin 0
 int joyPin2 = 1;                 // slider variable connecetd to analog pin 1
 const int midVal = 52;           // constant for value of specific joystick at center
 bool isCentered = true;
 int value1 = 0;                  // variable to read the value from the analog pin 0
 int value2 = 0;                  // variable to read the value from the analog pin 1
 int curLED = 2;
 
// how the keypad has its keys laid out
/*const*/ char keys[ROWS][COLS] = {
  {MIDI_C + MIDI_SHARP, MIDI_D + MIDI_SHARP, MIDI_F + MIDI_SHARP, MIDI_G + MIDI_SHARP},
  {MIDI_A + MIDI_SHARP, MIDI_B, MIDI_A, MIDI_G},
  {MIDI_F, MIDI_E, MIDI_D, MIDI_C},
};
  /*{MIDI_F + MIDI_SHARP, MIDI_G + MIDI_SHARP, MIDI_A + MIDI_SHARP, MIDI_C + MIDI_SHARP},
  {MIDI_D + MIDI_SHARP, MIDI_E, MIDI_D, MIDI_C},
  {MIDI_B, MIDI_A, MIDI_G, MIDI_F},*/

const byte rowPins[ROWS] = {6, 7, 8}; //connect to the row pinouts of the keypad
const byte colPins[COLS] = {2, 3, 4, 5}; //connect to the column pinouts of the keypad

Keypad_Matrix kpd = Keypad_Matrix( makeKeymap (keys), rowPins, colPins, ROWS, COLS );

void keyDown (const char which)
{
  midi_note_on(0, which, 100);
}

void keyUp (const char which)
{
  midi_note_off(0, which, 100);
}

void check_X_Direct()
{
  value1 = analogRead(joyPin1);
  if((treatValue(value1)< midVal) && (keys[1][3] > 48) && (isCentered == true)){
    isCentered = false;
    digitalWrite(octave[curLED], LOW);
    for (int i = 0; i < ROWS; ++i){
      for(int j = 0; j < COLS; ++j){
        keys[i][j] = keys[i][j] - MIDI_OCTAVE;
      }
    }
    curLED = curLED - 1;
    digitalWrite(octave[curLED],HIGH);
  }
  else if((treatValue(value1)> midVal) && (keys[1][3] < 84) && (isCentered == true)){
    isCentered = false;
    digitalWrite(octave[curLED],LOW);
    for (int i = 0; i < ROWS; ++i){
      for(int j = 0; j < COLS; ++j){
        keys[i][j] = keys[i][j] + MIDI_OCTAVE;
      }
    }
    curLED = curLED + 1;
    digitalWrite(octave[curLED],HIGH);
  }
  else{
    isCentered = true;
  }
}

void check_Y_Direct()
{
  value2 = analogRead(joyPin2);
  midi_pitch_bend(0, treatValueY(value2));
}

void setup() 
{
  pinMode(octave[0], OUTPUT);         // initializes digital pins 0 to 7 as outputs
  pinMode(octave[1], OUTPUT);
  pinMode(octave[2], OUTPUT);
  pinMode(octave[3], OUTPUT);
  pinMode(octave[4], OUTPUT);
  
  Serial.begin (115200);
  Serial.println ("Starting.");
  kpd.begin ();
  kpd.setKeyDownHandler (keyDown);
  kpd.setKeyUpHandler   (keyUp);
}

int treatValue(int data) {
  return (data * 9 / 1024)+ 48;
 }
int treatValueY(int data) {
  data = MAX_Y - data;
  data =(16384*data/MAX_Y);
  if (data == 8128){
    return 8192;
  }
  return data;
}
 
void loop() 
{
  kpd.scan ();
  digitalWrite(octave[curLED], HIGH);

  check_X_Direct();
  
  delay(100);            
  // reads the value of the variable resistor 
  check_Y_Direct();
  
  /*digitalWrite(ledPin, HIGH);          
  delay(value1);
  digitalWrite(ledPin, LOW);
  delay(value2);
  Serial.print('J');
  Serial.print(treatValue(value1));
  Serial.println(treatValue(value2));*/
}
