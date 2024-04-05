#include <SoftwareSerial.h> // Import SoftwareSerial library for bluetooth communication
int fireSensor = 2; 
int rLED = 3;
int yLED = 5;
int gLED = 7;
int buzzer = 8;
float threshold = 400.00; //This value should be manually changed depending on the ambient air quality
float sensorValue;  //variable to store gas sensor value
SoftwareSerial EEBlue(12, 13); //RX | TX
#define MQ2pin 0 //Analog Pin for MQ-2 Gas Sensor

void setup() {
  Serial.begin(9600); // sets the serial port to 9600
  EEBlue.begin(9600);
  EEBlue.println("MQ2 warming up!");
  delay(5000); // allow the MQ2 to warm up, can be adjusted
  pinMode(rLED, OUTPUT);
  pinMode(yLED, OUTPUT);
  pinMode(gLED, OUTPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(fireSensor, INPUT);
}

void loop() {

int detect = digitalRead(fireSensor);
sensorValue = analogRead(MQ2pin);

if (detect == LOW && sensorValue > threshold)

{
  digitalWrite(rLED, HIGH);
  digitalWrite(yLED, LOW);
  digitalWrite(gLED, LOW);
  digitalWrite(buzzer, HIGH);
  EEBlue.println("FIRE DETECTED AT: ");
  EEBlue.println("1137 Alumni Ave, Kelowna, BC V1V 1V7"); //Address should be set to the user's address

} else if (detect == HIGH && sensorValue > threshold) {
  digitalWrite(yLED, HIGH);
  digitalWrite(rLED, LOW);
  digitalWrite(buzzer, LOW);
  digitalWrite(gLED, LOW);
  EEBlue.println("WARNING. High Fire Chance at: ");
  EEBlue.println("1137 Alumni Ave, Kelowna, BC V1V 1V7");
}

else

{



digitalWrite(rLED, LOW);
digitalWrite(yLED, LOW);
digitalWrite(gLED, HIGH);
digitalWrite(buzzer, LOW);
EEBlue.println("Clear");


} 
  //This is only printed to the serial monitor if the Arduino is powered by a computer
	Serial.print("Sensor Value: ");
  	Serial.println(sensorValue);
	delay(300); // wait 1s for next reading
}
