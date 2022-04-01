
#include <LiquidCrystal.h>
#include <Wire.h> 
#include <Servo.h>

#define echoPin 2 // attach pin D2 Arduino to pin Echo of HC-SR04
#define trigPin 3 //attach pin D3 Arduino to pin Trig of HC-SR04
#define echoPin2 4
#define trigPin2 5
Servo myServo,myServo1;

int cnt = 50;//50 parking spots

LiquidCrystal lcd(12, 11, 10, 9, 8, 7);

int ledRosu = A0;
int ledVerde = A1;

// defines variables
long duration1,duration2; // variable for the duration of sound wave travel
int distance1,distance2; // variable for the distance measurement
void setup() {
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an OUTPUT
  pinMode(echoPin, INPUT); // Sets the echoPin as an INPUT
  pinMode(trigPin2, OUTPUT); 
  pinMode(echoPin2, INPUT);
  pinMode(ledRosu,OUTPUT);
  pinMode(ledVerde,OUTPUT);
  Serial.begin(9600); // // Serial Communication is starting with 9600 of baudrate speed
  myServo.attach(6);
  myServo1.attach(13);
  lcd.clear();
  lcd.setCursor(1,0);
}
void loop() {
  myServo.write(0);
  myServo1.write(0);
  delay(1000);
   // Clears the trigPin condition
  digitalWrite(trigPin2, LOW);
  delayMicroseconds(2);
  // Sets the trigPin HIGH (ACTIVE) for 10 microseconds
  digitalWrite(trigPin2, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin2, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration2 = pulseIn(echoPin2, HIGH);
  // Calculating the distance
  distance2 = duration2 * 0.034 / 2; // Speed of sound wave divided by 2 (go and back)
  // Displays the distance on the Serial Monitor
  Serial.print("distance2:");
  Serial.println(distance2);
  if(distance2 <50 && cnt < 50){
    cnt++;
    myServo1.write(90);
    delay(1000);
  }
  
  if(cnt == 0) {
    lcd.clear();
    lcd.print("No empty spots");
    analogWrite(ledRosu,255);
    analogWrite(ledVerde,0);
    delay(1000);
  }else{
  	analogWrite(ledRosu,0);
    analogWrite(ledVerde,255);
    // Clears the trigPin condition
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    // Sets the trigPin HIGH (ACTIVE) for 10 microseconds
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    // Reads the echoPin, returns the sound wave travel time in microseconds
    duration1 = pulseIn(echoPin, HIGH);
    // Calculating the distance
    distance1 = duration1 * 0.034 / 2; // Speed of sound wave divided by 2 (go and back)
    // Displays the distance on the Serial Monitor

    //check if a car go in
    Serial.print("distance1:");
  	Serial.println(distance1);

    if(distance1 <50){
      cnt--;
      myServo.write(90);
      delay(1000);
    }


    lcd.print("Empty spots: ");
    lcd.print(cnt);
    
    delay(1000);
   	
    lcd.clear();
  }
}
