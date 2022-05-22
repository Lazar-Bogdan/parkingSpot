
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <Servo.h>

#define echoPinIntrare 4 // attach pin D2 Arduino to pin Echo of HC-SR04
#define trigPinIntrare 5 //attach pin D3 Arduino to pin Trig of HC-SR04
#define echoPinIesire 8
#define trigPinIesire 9
Servo myServoIntrare,myServoIesire;

int cnt = 22;//22 parking spots

LiquidCrystal_I2C lcd(0x27, 16, 2);

int ledRosu = 2;
int ledVerde = 3;

// defines variables
long durationIntrare,durationIesire; // variable for the duration of sound wave travel
int distanceIntrare,distanceIesire; // variable for the distance measurement
void setup() {
  pinMode(trigPinIntrare, OUTPUT); // Sets the trigPin as an OUTPUT
  pinMode(echoPinIntrare, INPUT); // Sets the echoPin as an INPUT
  pinMode(trigPinIesire, OUTPUT); 
  pinMode(echoPinIesire, INPUT);
  pinMode(ledRosu,OUTPUT);
  pinMode(ledVerde,OUTPUT);
  Serial.begin(9600); // // Serial Communication is starting with 9600 of baudrate speed
  myServoIntrare.attach(6);
  myServoIesire.attach(7);
  lcd.begin();
  myServoIntrare.write(180);
  myServoIesire.write(0);
  lcd.backlight();
  lcd.clear();
}
int state1=0;
void loop() {
//  delay(2000);
//  myServoIntrare.write(90);
    myServoIntrare.write(180);
//  delay(5000);
//  myServoIntrare.write(190);
    myServoIesire.write(2);

    
    

   // Clears the trigPin condition
  digitalWrite(trigPinIesire, LOW);
  delayMicroseconds(2);
  // Sets the trigPin HIGH (ACTIVE) for 10 microseconds
  digitalWrite(trigPinIesire, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPinIesire, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  durationIesire = pulseIn(echoPinIesire, HIGH);
  // Calculating the distance
  distanceIesire = durationIesire * 0.034 / 2; // Speed of sound wave divided by 2 (go and back)
  // Displays the distance on the Serial Monitor
  Serial.print("distanceIesire:");
  Serial.println(distanceIesire);
  if(distanceIesire <10 && cnt < 22){
    cnt++;
    myServoIesire.write(90);
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
    digitalWrite(trigPinIntrare, LOW);
    delayMicroseconds(2);
    // Sets the trigPin HIGH (ACTIVE) for 10 microseconds
    digitalWrite(trigPinIntrare, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPinIntrare, LOW);
    // Reads the echoPin, returns the sound wave travel time in microseconds
    durationIntrare = pulseIn(echoPinIntrare, HIGH);
    // Calculating the distance
    distanceIntrare = durationIntrare * 0.034 / 2; // Speed of sound wave divided by 2 (go and back)
    // Displays the distance on the Serial Monitor

    //check if a car go in
    Serial.print("distanceIntrare:");
    Serial.println(distanceIntrare);

    if(distanceIntrare <10 && state1 == 0){
      cnt--;
      myServoIntrare.write(90);
      state1 = 1;
      delay(1000);
    }

    if(distanceIntrare < 10 && state1 == 1){
      myServoIntrare.write(90);
    }

    if(distanceIntrare > 10) {
        delay(1500);
        myServoIntrare.write(180);
        state1 = 0;
    }

    lcd.print("Empty spots: ");
    lcd.print(cnt);
    
    delay(1000);
    
   lcd.clear();
  }
}
