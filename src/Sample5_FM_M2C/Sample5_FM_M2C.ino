
#include <MozziGuts.h>
#include <Oscil.h>                // oscillator
#include <tables/sin2048_int8.h>  // table for Oscils to play

#include <ADSR.h>
#include <mozzi_midi.h>

Oscil<SIN2048_NUM_CELLS, AUDIO_RATE> aSin(SIN2048_DATA);
Oscil<SIN2048_NUM_CELLS, AUDIO_RATE> aModulator1(SIN2048_DATA);
Oscil<SIN2048_NUM_CELLS, AUDIO_RATE> aModulator2(SIN2048_DATA);

ADSR<AUDIO_RATE, AUDIO_RATE> envelope;  //エンベロープをかけるためのクラス
unsigned int Dur, Atk, Dec, Sus, Rel;   //ADSRの長さを入れておく変数

#define CONTROL_RATE 128  // Hz, powers of 2 are most reliable

const int button01Pin = 8;
const int button02Pin = 7;
const int button03Pin = 6;
const int button04Pin = 5;
const int button05Pin = 4;
const int button06Pin = 3;
const int button07Pin = 2;
const int button08Pin = 1;
const int button09Pin = 15;

int button01State, button02State, button03State, button04State, button05State, button06State, button07State, button08State, button09State= 1;
int tempButton01State, tempButton02State, tempButton03State, tempButton04State, tempButton05State, tempButton06State, tempButton07State, tempButton08State, tempButton09State = 1;

const int analog01Pin = 29;
const int analog02Pin = 28;
const int analog03Pin = 27;
const int analog04Pin = 26;
int analog01Val, analog02Val, analog03Val, analog04Val = 0;  // variable to store the value coming from the sensor

// float harm_ratio;
int harm_ratio;
float harm_range = 4.f;
float mod_freq_1;
/*
harmonicity ratio; Modulatorの周波数 mod_freq = キャリア周波数 freq * harm_ratio
harm_ratioが整数の時、綺麗な倍音が出ることが知られている
harm_rangeはharm_ratioの最大値
*/

int freq;
// float mod_index_1;
long mod_dev_1;
float mod_index_range = 10.f;
/*
modulatorの振幅; mod_amp = Modulatorの周波数 mod_freq * mod_index
mod_indexで倍音の含まれ方を様々に変えることができる。
mod_index_range; mod_indexの最大値
*/

long modulation_1;
byte volume;

void readInterface() {
  button01State = (digitalRead(button01Pin));
  button02State = (digitalRead(button02Pin));
  button03State = (digitalRead(button03Pin));
  button04State = (digitalRead(button04Pin));
  button05State = (digitalRead(button05Pin));
  button06State = (digitalRead(button06Pin));
  button07State = (digitalRead(button07Pin));
  button08State = (digitalRead(button08Pin));

  analog01Val = analogRead(analog01Pin);  // value is 0-1023
  analog02Val = analogRead(analog02Pin);  // value is 0-1023
  analog03Val = analogRead(analog03Pin);  // value is 0-1023
  analog04Val = analogRead(analog04Pin);  // value is 0-1023
}

void setup() {
  Serial.begin(115200);  // set up the Serial output so we can look at the piezo values // set up the Serial output so we can look at the piezo values
  startMozzi(CONTROL_RATE);

  // set pinMode to pullup
  pinMode(button01Pin, INPUT_PULLUP);
  pinMode(button02Pin, INPUT_PULLUP);
  pinMode(button03Pin, INPUT_PULLUP);
  pinMode(button04Pin, INPUT_PULLUP);
  pinMode(button05Pin, INPUT_PULLUP);
  pinMode(button06Pin, INPUT_PULLUP);
  pinMode(button07Pin, INPUT_PULLUP);
  pinMode(button08Pin, INPUT_PULLUP);

  Atk = 5;
  Dec = 10;
  Sus = 100;
  Rel = 100;

  envelope.setADLevels(255, 128);
  envelope.setTimes(Atk, Dec, Sus, Rel);
}

void printInfo(int mf, float mi){

  // print the frequency to the Serial monitor for debugging
  Serial.print("freq:");
  Serial.print(freq);
  Serial.print(",");  // print tab
  Serial.print("vol:");
  Serial.print((int)volume);
  Serial.print(",");  // print tab
  Serial.print("harm_ratio:");
  Serial.print(harm_ratio);
  Serial.print(",");  // print tab
  Serial.print("mod_index_1:");
  Serial.print(mi);
  Serial.print(",");  // print tab
  Serial.print("mod_dev_1:");
  Serial.print(mod_dev_1);
  Serial.print(",");  // print tab
  Serial.print("mod_freq_1:");
  Serial.print(mf);
  Serial.print(",");  // print tab
  // Serial.print("mod_amp_1:");
  // Serial.print(modulation_1);
  Serial.println();
}


void loop() {
  audioHook();
}


void updateControl() {
  readInterface();

  if (button01State == LOW) {
    freq = mtof(60);
    envelope.noteOn();
  }
  if (button02State == LOW) {
    freq = mtof(62);
    envelope.noteOn();
  }
  if (button03State == LOW) {
    freq = mtof(64);
    envelope.noteOn();
  }
  if (button04State == LOW) {
    freq = mtof(65);
    envelope.noteOn();
  }
  if (button05State == LOW) {
    freq = mtof(67);
    envelope.noteOn();
  }
  if (button06State == LOW) {
    freq = mtof(69);
    envelope.noteOn();
  }
  if (button07State == LOW) {
    freq = mtof(71);
    envelope.noteOn();
  }
  if (button08State == LOW) {
    freq = mtof(72);
    envelope.noteOn();
  }


  harm_ratio = analog02Val / 1023.f * harm_range;
  volume = map(analog01Val, 0, 1023, 0, 255);

  //calculate the modulation frequency to stay in ratio
  int mod_freq_1 = freq * harm_ratio;

  // set the FM oscillator frequencies to the calculated values
  aSin.setFreq(freq);
  aModulator1.setFreq(mod_freq_1);

  float mod_index_1 = float(analog03Val) / 1023.f * mod_index_range;
  mod_dev_1 = (long)((float)mod_freq_1 * mod_index_1);

  printInfo(mod_freq_1, mod_index_1);
}

AudioOutput_t updateAudio() {
  envelope.update();
  int gain = (int)(envelope.next() * volume) >> 8;
  long modulation_1 = mod_dev_1 * aModulator1.next();

  return MonoOutput::from16Bit((int)(gain * aSin.phMod(modulation_1)));
}
