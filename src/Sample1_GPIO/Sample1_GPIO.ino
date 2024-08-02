

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
int button09State = 1;
int tempButton01State = 1;
int tempButton02State = 1;
int tempButton03State = 1;
int tempButton04State = 1;
int tempButton05State = 1;
int tempButton06State = 1;
int tempButton07State = 1;
int tempButton08State = 1;
int tempButton09State = 1;

const int analog01Pin = 29;
const int analog02Pin = 28;
const int analog03Pin = 27;
const int analog04Pin = 26;
int analog01Val = 0;  // variable to store the value coming from the sensor
int analog02Val = 0;  // variable to store the value coming from the sensor
int analog03Val = 0;  // variable to store the value coming from the sensor
int analog04Val = 0;  // variable to store the value coming from the sensor


void setup() {
  Serial.begin(115200); // set up the Serial output so we can look at the piezo values // set up the Serial output so we can look at the piezo values

  pinMode(button01Pin, INPUT_PULLUP);
  pinMode(button02Pin, INPUT_PULLUP);
  pinMode(button03Pin, INPUT_PULLUP);
  pinMode(button04Pin, INPUT_PULLUP);
  pinMode(button05Pin, INPUT_PULLUP);
  pinMode(button06Pin, INPUT_PULLUP);
  pinMode(button07Pin, INPUT_PULLUP);
  pinMode(button08Pin, INPUT_PULLUP);
  pinMode(button09Pin, INPUT_PULLUP);

  
}



void loop(){

  button01State = (digitalRead(button01Pin));
  button02State = (digitalRead(button02Pin));
  button03State = (digitalRead(button03Pin));
  button04State = (digitalRead(button04Pin));
  button05State = (digitalRead(button05Pin));
  button06State = (digitalRead(button06Pin));
  button07State = (digitalRead(button07Pin));
  button08State = (digitalRead(button08Pin));
  button09State = (digitalRead(button09Pin));



  analog01Val = analogRead(analog01Pin); // value is 0-1023
  analog02Val = analogRead(analog02Pin); // value is 0-1023
  analog03Val = analogRead(analog03Pin); // value is 0-1023
  analog04Val = analogRead(analog04Pin); // value is 0-1023

  Serial.print("digi:");
  Serial.print(button01State);
  Serial.print(button02State);
  Serial.print(button03State);
  Serial.print(button04State);
  Serial.print(button05State);
  Serial.print(button06State);
  Serial.print(button07State);
  Serial.print(button08State);
  Serial.print(button09State);
  Serial.print(","); // print tab

  // // print the value to the Serial monitor for debugging
  Serial.print("a01:");
  Serial.print(analog01Val);
  Serial.print(","); // print tab
  Serial.print("a02:");
  Serial.print(analog02Val);
  Serial.print(","); // print tab
  Serial.print("a03:");
  Serial.print(analog03Val);
  Serial.print(","); // print tab
  Serial.print("a04:");
  Serial.print(analog04Val);
  Serial.println(","); // print tab
}


