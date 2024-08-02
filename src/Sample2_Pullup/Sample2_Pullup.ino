

const int analog01Pin = 29;
int analog01Val = 0;  // variable to store the value coming from the sensor
float vol;


void setup() {
  Serial.begin(115200); // set up the Serial output so we can look at the piezo values // set up the Serial output so we can look at the piezo values
}
// 1023 = 3.3V

void loop(){

  analog01Val = analogRead(analog01Pin); // value is 0-1023
  vol = (float)analog01Val / 1023.f * 3.3;

  // // print the value to the Serial monitor for debugging
  Serial.print("a01:");
  Serial.print(analog01Val);
  Serial.print(", Voltage:"); // print tab
  Serial.print(vol);
  Serial.println(","); // print tab
}


