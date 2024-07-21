


#include "HX711.h"
#include <Servo.h>


#define DOUT  3
#define CLK  2

HX711 scale;
Servo monservo;


float calibration_factor = -7500; 
int positionservo = 0;



void setup() {
  Serial.begin(9600);
  Serial.println("HX711 calibration sketch");
  Serial.println("Remove all weight from scale");
  Serial.println("After readings begin, place known weight on scale");
  Serial.println("Press + or a to increase calibration factor");
  Serial.println("Press - or z to decrease calibration factor");

  scale.begin(DOUT, CLK);
  scale.set_scale();
  scale.tare(); 

  monservo.attach(9);
monservo.write (0);



  long zero_factor = scale.read_average(); 
  Serial.print("Zero factor: ");  
  Serial.println(zero_factor);
}

void loop() {

  scale.set_scale(calibration_factor); 
  Serial.print("Reading: ");
  Serial.print(scale.get_units(), 1);
  Serial.print(" lbs");  
  Serial.print(" calibration_factor: ");
  Serial.print(calibration_factor);
  Serial.println();
  Serial.print(" position servo ");
Serial.print(positionservo);
Serial.println();
  if(Serial.available())
  {
    char temp = Serial.read();
    if(temp == '+' || temp == 'a')
      calibration_factor += 10;
    else if(temp == '-' || temp == 'z')
      calibration_factor -= 10;
  
 }

 
int pression = scale.get_units();


if (pression > 0 and pression < 10 ) {
    
  positionservo = 0;
   monservo.write (positionservo);
   delay(200);
   
 
   
 }
if (pression > 10 and pression < 20  ) {
    
  positionservo = +30;
   monservo.write (positionservo);
   delay(200);
   
 
   
 }
 if (pression > 20 and pression < 30 ) {
    
  positionservo = +60;
   monservo.write (positionservo);
   delay(200);
   
 
   
 }
 if (pression > 30 and pression < 40 ) {
    
  positionservo = +90;
   monservo.write (positionservo);
   delay(200);
   
 
   
 }
 if (pression > 40 and pression < 50 ) {
    
  positionservo = +120;
   monservo.write (positionservo);
   delay(200);
   
 
   
 }
 if (pression > 50 and pression < 60 ) {
    
  positionservo = +150;
   monservo.write (positionservo);
   delay(200);
   
 
   
 }

  if (pression > 60 and pression < 70 ) {
    
  positionservo = +180;
   monservo.write (positionservo);
   delay(200);
   
 
   
 }
 if (pression >70 and positionservo== 180) {
    
  positionservo = +180;
   monservo.write (positionservo);
   delay(200);
   
 
   
 }
   
 
}
