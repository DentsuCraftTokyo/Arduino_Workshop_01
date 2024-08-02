
#include <MozziGuts.h>
#include <Oscil.h> // oscillator
#include <tables/sin2048_int8.h> // table for Oscils to play
#include <ADSR.h>
#include <mozzi_midi.h>
#include <EventDelay.h>

Oscil <SIN2048_NUM_CELLS, AUDIO_RATE> aSin(SIN2048_DATA);
ADSR <AUDIO_RATE, AUDIO_RATE> envelope;//エンベロープをかけるためのクラス
unsigned int Dur, Atk, Dec, Sus, Rel;//
EventDelay noteDelay;

#define CONTROL_RATE 64 // Hz, powers of 2 are most reliable
const int button01Pin = 1;
const int button02Pin = 2;
const int button03Pin = 3;
const int button04Pin = 4;
const int button05Pin = 5;
const int button06Pin = 6;
const int button07Pin = 7;
const int button08Pin = 8;
const int button09Pin = 15;

int button01State = 1;
int button02State = 1;
int button03State = 1;
int button04State = 1;
int button05State = 1;
int button06State = 1;
int button07State = 1;
int button08State = 1;
int tempButton01State = 1;
int tempButton02State = 1;
int tempButton03State = 1;
int tempButton04State = 1;
int tempButton05State = 1;
int tempButton06State = 1;
int tempButton07State = 1;
int tempButton08State = 1;

const int analog01Pin = 29;
const int analog02Pin = 28;
const int analog03Pin = 27;
const int analog04Pin = 26;
int analog01Val = 0;  // variable to store the value coming from the sensor
int analog02Val = 0;  // variable to store the value coming from the sensor
int analog03Val = 0;  // variable to store the value coming from the sensor
int analog04Val = 0;  // variable to store the value coming from the sensor


int freq;
int gain;
int is_down = 0;
unsigned long currentTime;
unsigned long timeStamp;
unsigned int down_time = 0;

const byte volume = 10;

void setFreqonDown(int notenumber){
  freq = mtof(notenumber);
  if(is_down==0){
    envelope.noteOn();
    is_down = 1;
    timeStamp = currentTime;
  } else {
    down_time = currentTime - timeStamp;
  }
}

void setup() {
  Serial.begin(115200); // set up the Serial output so we can look at the piezo values // set up the Serial output so we can look at the piezo values
  startMozzi(CONTROL_RATE);

  pinMode(button01Pin, INPUT_PULLUP);
  pinMode(button02Pin, INPUT_PULLUP);
  pinMode(button03Pin, INPUT_PULLUP);
  pinMode(button04Pin, INPUT_PULLUP);
  pinMode(button05Pin, INPUT_PULLUP);
  pinMode(button06Pin, INPUT_PULLUP);
  pinMode(button07Pin, INPUT_PULLUP);
  pinMode(button08Pin, INPUT_PULLUP);
  pinMode(button09Pin, INPUT_PULLUP);
  
  Atk = 10;
  Dec = 10;
  Sus = 100;
  Rel = 500;
  envelope.setADLevels(255, 128); //Decay Level = Sustain Level
  envelope.setTimes(Atk, Dec, 65535, Rel); 
  // noteDelay.set(2000);
}


void loop() {
  audioHook();
}


void updateControl(){
  
  button01State = (digitalRead(button01Pin));
  button02State = (digitalRead(button02Pin));
  button03State = (digitalRead(button03Pin));
  button04State = (digitalRead(button04Pin));
  button05State = (digitalRead(button05Pin));
  button06State = (digitalRead(button06Pin));
  button07State = (digitalRead(button07Pin));
  button08State = (digitalRead(button08Pin));

  analog01Val = analogRead(analog01Pin); // value is 0-1023
  analog02Val = analogRead(analog02Pin); // value is 0-1023
  analog03Val = analogRead(analog03Pin); // value is 0-1023
  analog04Val = analogRead(analog04Pin); // value is 0-1023

  // if(envelope.playing() == false){
    Atk = map(analog01Val, 0, 1023, 0, 2000);
    Dec = map(analog02Val, 0, 1023, 0, 2000);
    Sus = map(analog03Val, 0, 1023, 0, 255);
    Rel = map(analog04Val, 0, 1023, 0, 3000);
    envelope.setDecayLevel(Sus);
    envelope.setSustainLevel(Sus);
    envelope.setTimes(Atk, Dec, 65535, Rel);
  // }

  currentTime = millis();

  if (button08State == LOW){
    setFreqonDown(60);
  }
  else if (button07State == LOW){
    setFreqonDown(62);
  }
  else if (button06State == LOW){
    setFreqonDown(64);
  }
  else if (button05State == LOW){
    setFreqonDown(65);
  }
  else if (button04State == LOW){
    setFreqonDown(67);
  }
  else if (button03State == LOW){
    setFreqonDown(69);
  }
  else if (button02State == LOW){
    setFreqonDown(71);
  }
  else if (button01State == LOW){
    setFreqonDown(72);
  } else {
    is_down = 0;
    down_time = 0;
    envelope.noteOff();
  }

  aSin.setFreq(freq);

  Serial.print("digi:");
  Serial.print(button01State);
  Serial.print(button02State);
  Serial.print(button03State);
  Serial.print(button04State);
  Serial.print(button05State);
  Serial.print(button06State);
  Serial.print(button07State);
  Serial.print(button08State);
  Serial.print(","); // print tab

  // // print the value to the Serial monitor for debugging
  Serial.print("Atk");
  Serial.print(Atk);
  Serial.print(","); // print tab
  Serial.print("Dec");
  Serial.print(Dec);
  Serial.print(","); // print tab
  Serial.print("Sus");
  Serial.print((int)Sus / 255.f * 100.f);
  Serial.print(","); // print tab
  Serial.print("Rel");
  Serial.print(Rel);
  Serial.print(","); // print tab

  // print the frequency to the Serial monitor for debugging
  Serial.print("freq:");
  Serial.print(freq);
  Serial.print(","); // print tab
  Serial.print("vol:");
  Serial.print((int)volume);
  Serial.print(","); // print tab
  Serial.print("update env: ");
  Serial.print(down_time < Atk+Dec);
  Serial.print("play env:");
  Serial.print(envelope.playing());
  Serial.println();


}

AudioOutput_t updateAudio() {
  envelope.update();
  gain =  (int)(envelope.next() * volume)>>8;
  return MonoOutput::from16Bit((int) (gain * aSin.next()));

}

