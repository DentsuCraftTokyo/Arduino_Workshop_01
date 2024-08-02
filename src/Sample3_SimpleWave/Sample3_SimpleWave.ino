
#include <MozziGuts.h>
#include <Oscil.h> // oscillator
#include <tables/sin2048_int8.h> // table for Oscils to play
#include <tables/triangle2048_int8.h>
#include <tables/square_analogue512_int8.h>
#include <tables/pinknoise8192_int8.h>
#include <Smooth.h>

#include <ADSR.h>
#include <mozzi_midi.h>

Oscil <SIN2048_NUM_CELLS, AUDIO_RATE> aSin(SIN2048_DATA);
Oscil<TRIANGLE2048_NUM_CELLS, AUDIO_RATE> aTri(TRIANGLE2048_DATA);
Oscil<SQUARE_ANALOGUE512_NUM_CELLS, AUDIO_RATE> aSquare(SQUARE_ANALOGUE512_DATA);
Oscil<PINKNOISE8192_NUM_CELLS, AUDIO_RATE> aNoise(PINKNOISE8192_DATA);
#define CONTROL_RATE 64 // Hz, powers of 2 are most reliable

int freq;
byte volume;

const int analog01Pin = 29;
const int analog02Pin = 28;
const int button09Pin = 15;

int analog01Val = 0;  // variable to store the value coming from the sensor
int analog02Val = 0;  // variable to store the value coming from the sensor
int button09State = 1;
int tempButton09State = 1;

int waveform = 0;
int is_down = 0;


void setup() {
  Serial.begin(115200); // set up the Serial output so we can look at the piezo values // set up the Serial output so we can look at the piezo values
  pinMode(button09Pin, INPUT_PULLUP);
  startMozzi(CONTROL_RATE);
}
// 1023 = 3.3V

void loop(){
  audioHook();
}

void updateControl(){
  analog01Val = analogRead(analog01Pin); // value is 0-1023
  analog02Val = analogRead(analog02Pin); // value is 0-1023
  button09State = (digitalRead(button09Pin));

  if (button09State == LOW) {
    if (is_down == 0){
      waveform = (waveform + 1) % 4;
      is_down = 1;
    }
  } else {
    is_down = 0;
  }


  freq = (int)map(analog01Val, 10, 1023, 50, 6000);
  volume = map(analog02Val, 0, 1023, 0, 255);

  aSin.setFreq(freq);
  aTri.setFreq(freq);
  aSquare.setFreq(freq);
  aNoise.setFreq(freq);

  // print the value to the Serial monitor for debugging
  Serial.print("analog01= ");
  Serial.print(analog01Val);
  Serial.print("\t"); // print tab
  Serial.print("analog02= ");
  Serial.print(analog02Val);
  Serial.print("\t"); // print tab

  // print the frequency to the Serial monitor for debugging
  Serial.print("freq= ");
  Serial.print(freq);
  Serial.print("\t"); // prints tab
  Serial.print("vol= ");
  Serial.print((int)volume);
  Serial.print("\t"); // prints tab
  Serial.print("waveform:");
  Serial.print(waveform);
  Serial.println();
}

AudioOutput_t updateAudio() {
  switch(waveform){
    case 0: //sin wave
      return MonoOutput::from16Bit((int) (volume * aSin.next()));
    case 1: //tri wave
      return MonoOutput::from16Bit((int) (volume * aTri.next()));
    case 2: //square ware
      return MonoOutput::from16Bit((int) (volume * aSquare.next()));
    case 3: //noise
      return MonoOutput::from16Bit((int) (volume * aNoise.next()));
    default:
      return 0;
  }
  
}



