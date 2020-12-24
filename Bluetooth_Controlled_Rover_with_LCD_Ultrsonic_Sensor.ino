#include <LiquidCrystal_I2C.h>

const int drivingPinCC= 2;
const int drivingPinAC= 3;
const int SteeringPinCC= 4;
const int SteeringPinAC= 5;
const int trigPin= 6;
const int echoPin= 7;
int counter= 0;
int state= 0;
String scmd;                  //Serial Command

LiquidCrystal_I2C lcd(0x27, 16, 2);

void start(){
  digitalWrite(drivingPinCC, HIGH);
  digitalWrite(drivingPinAC, LOW);
  scmd="";
  state= 1;
}

void right(){
  digitalWrite(SteeringPinCC,HIGH);
  digitalWrite(SteeringPinAC, LOW);
  delay(525);
  digitalWrite(SteeringPinCC,LOW);
  digitalWrite(SteeringPinAC, LOW);
  delay(500);
  digitalWrite(SteeringPinCC,LOW);
  digitalWrite(SteeringPinAC, HIGH);
  delay(535);
  digitalWrite(SteeringPinCC,LOW);
  digitalWrite(SteeringPinAC, LOW);
  scmd="";
  state= 2;
}

void left(){
  digitalWrite(SteeringPinCC,LOW);
  digitalWrite(SteeringPinAC, HIGH);
  delay(470);
  digitalWrite(SteeringPinCC,LOW);
  digitalWrite(SteeringPinAC, LOW);
  delay(500);
  digitalWrite(SteeringPinCC,HIGH);
  digitalWrite(SteeringPinAC, LOW);
  delay(530);
  digitalWrite(SteeringPinCC,LOW);
  digitalWrite(SteeringPinAC, LOW);
  scmd="";
  state= 3;
}

void uTurn(){
  digitalWrite(SteeringPinCC,HIGH);
  digitalWrite(SteeringPinAC, LOW);
  delay(525);
  digitalWrite(SteeringPinCC,LOW);
  digitalWrite(SteeringPinAC, LOW);
  delay(1000);
  digitalWrite(SteeringPinCC,LOW);
  digitalWrite(SteeringPinAC, HIGH);
  delay(535);
  digitalWrite(SteeringPinCC,LOW);
  digitalWrite(SteeringPinAC, LOW);
  scmd="";
  state= 4;
}

void reverse(){
  digitalWrite(drivingPinCC, LOW);
  digitalWrite(drivingPinAC, HIGH);
  scmd="";
  state= 5;
}

void halt(){
  digitalWrite(drivingPinCC, LOW);
  digitalWrite(drivingPinAC, LOW);
  scmd="";
  state=0;
}

void setup() {

 pinMode(drivingPinCC, OUTPUT);
 pinMode(drivingPinAC, OUTPUT);
 pinMode(SteeringPinCC, OUTPUT);
 pinMode(SteeringPinAC, OUTPUT);
 pinMode(trigPin, OUTPUT);
 pinMode(echoPin, INPUT);
 
 Serial.begin(9600);

 lcd.init();
 lcd.backlight();
 
 lcd.setCursor(1,0);
 lcd.print("Enter Command");
}

void loop() {

 long duration, distance;
 
  if(Serial.available()){
    scmd= Serial.readString();
    scmd.trim();
    lcd.clear();
    if(scmd.equalsIgnoreCase("start") || scmd.equalsIgnoreCase("forward")){
      start();
      lcd.setCursor(15,0);
      lcd.print("Going Forward");
      for(int i=3; i<16; i++){
        lcd.scrollDisplayLeft();
        delay(89);
      }
      delay(1500);
      lcd.clear();
    }
    else if(scmd.equalsIgnoreCase("right")){
      right();
      lcd.setCursor(15,0);
      lcd.print("Turned Right");
      for(int i=3; i<16; i++){
        lcd.scrollDisplayLeft();
        delay(89);
      }
      delay(1500);
      lcd.clear();
    }
    else if(scmd.equalsIgnoreCase("left")){
      left();
      lcd.setCursor(15,0);
      lcd.print("Turned Left");
      for(int i=3; i<16; i++){
        lcd.scrollDisplayLeft();
        delay(89);
      }
      delay(1500);
      lcd.clear();
    }
    else if(scmd.equalsIgnoreCase("U turn")){
      uTurn();
      lcd.setCursor(15,0);
      lcd.print("Took U-Turn");
      for(int i=3; i<16; i++){
        lcd.scrollDisplayLeft();
        delay(89);
      }
      delay(1500);
      lcd.clear();
    }
    else if(scmd.equalsIgnoreCase("reverse")){
      reverse();
      lcd.setCursor(15,0);
      lcd.print("Reversed");
      for(int i=6; i<16; i++){
        lcd.scrollDisplayLeft();
        delay(89);
      }
      delay(1500);
      lcd.clear();
    }
    else if(scmd.equalsIgnoreCase("stop")){
      halt();
      lcd.setCursor(15,0);
      lcd.print("Stopped");
      for(int i=6; i<16; i++){
        lcd.scrollDisplayLeft();
        delay(89);
      }
      delay(1500);
      lcd.clear();
    }
    else{
      Serial.println("Incorrect Command");

      lcd.clear();
      lcd.setCursor(1,0);
      lcd.print("Dyslexic? Gawar");
      lcd.setCursor(1,1);
      lcd.print("theek se likh");
    }
  }
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration= pulseIn(echoPin, HIGH);
  distance= (duration/2)/29.1;

  if(distance < 12 && state != 0){
    
    if(counter < 3){
      Serial.println("Insufficient space to move ahead.");
      Serial.println("Correcting path!\n");

      lcd.setCursor(15,0);
      lcd.print("Correcting Path!");
      for(int i=1; i<16; i++){
        lcd.scrollDisplayLeft();
        delay(12);
      }
      
      if(state == 1){
        reverse();
        delay(2000);
        start();
        delay(3000);
      }
      else if(state == 2){
        reverse();
        delay(100);
        left();
        delay(100);
        start();
        delay(2500);
      }
      else if(state == 3){
        reverse();
        delay(100);
        right();
        delay(100);
        start();
        delay(2500);
      }
      else if(state == 4){
        reverse();
        delay(100);
        left();
        delay(100);
        start();
        delay(100);
        right();
        delay(1000);
      }
      lcd.clear();
    }
    else{
      halt();
      state= 0;
      Serial.println("Major road block ahead.");
      Serial.println("Re-adjust the Rover!\n\n");

      lcd.setCursor(15,0);
      lcd.print("Re-adjust Rover!");
      for(int i=1; i<16; i++){
        lcd.scrollDisplayLeft();
        delay(89);
      }
      delay(1500);
    }
    counter++;
  }
  else{
    counter= 0;
  }
}
