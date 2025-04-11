// C++ code
//
int pinRed1 = 11;
int pinBlue1 = 6;
int pinGreen1 = 3;
int analogPin = 0;
int value;
int redState = LOW;
int blueState = LOW;
int greenState = LOW;

void setup()
{
  pinMode(pinRed1, OUTPUT);
  pinMode(pinBlue1, OUTPUT);
  pinMode(pinGreen1, OUTPUT);  
}

void loop()
{
  
  value = map(analogRead(analogPin), 0, 1023, 0, 255);
  
  if (value < 255 / 12 * 3 || value > 255 / 12 * 9){
  	redState = HIGH;
  } else {
    redState = LOW;
  }
  if (value > 255 / 12 && value < 255 / 12 * 7) {
    greenState = HIGH;
  } else {
  	greenState = LOW;
  } 
  if (value > 255 / 12 * 5 && value < 255 / 12 * 11) {
    blueState = HIGH;
  } else {
    blueState = LOW;
  }
  
  digitalWrite(pinRed1, redState);
  digitalWrite(pinGreen1, greenState);
  digitalWrite(pinBlue1, blueState);
 
}