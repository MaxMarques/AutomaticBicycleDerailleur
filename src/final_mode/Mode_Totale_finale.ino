
#include "IRremote.h"
#include "HX711.h"
#include <Servo.h>
#include <LiquidCrystal.h>
#define DOUT  3
#define CLK  2

int receiver = 6; 
int choix = 0;
float calibration_factor = -41000; 
int positionservo = 0;
int vitesse=0;
int boutonG = 4;
int etatboutonG = 0;
int boutonD = 5;
int etatboutonD = 0;

HX711 scale;
Servo monservo;
LiquidCrystal lcd(7,8,10,11,12,13);
IRrecv irrecv(receiver);     
decode_results results;      

void translateIR() 
{
switch(results.value)
{
  case 0xFF30CF: Serial.println("mode automatique");  choix = 1;  break;
  case 0xFF18E7: Serial.println("mode semi-automatique"); choix = 2;   break;
 default: 
  
  Serial.println("appuyer sur 1 ou 2");
}
 delay(500); 
} 
 
 void setup()  
{
  Serial.begin(9600);
 
 
 lcd.begin(16,2);
 lcd.print(" Choix du mode:"   );
 lcd.setCursor(0,1);
 lcd.print (" A-> 1 // S-> 2" );
 lcd.setCursor(0,2);
 
  Serial.println("## BONJOUR   ## "); 
  Serial.println("Choix du mode: "); 
  irrecv.enableIRIn();
/*
  Serial.println("HX711 calibration sketch");
  Serial.println("Remove all weight from scale");
  Serial.println("After readings begin, place known weight on scale");
  Serial.println("Press + or a to increase calibration factor");
  Serial.println("Press - or z to decrease calibration factor");*/
  scale.begin(DOUT, CLK);
  scale.set_scale();
  scale.tare(); 
  monservo.attach(9);
  monservo.write (0);

long zero_factor = scale.read_average(); 
  /*Serial.print("Zero factor: ");  
  Serial.println(zero_factor);*/
  pinMode (boutonG, INPUT);
  monservo.attach(9);
  monservo.write (0);
  pinMode (boutonD, INPUT);
}
void loop() 
{
  if (irrecv.decode(&results)) {

translateIR();
irrecv.resume();
} 
 
 if ( choix ==1) { 
  
 scale.set_scale(calibration_factor); 
  Serial.print("Reading: ");
  Serial.print(scale.get_units(), 1);
  float jauge = jauge / 10;
  Serial.print(" Kgs");  
  Serial.print(" calibration_factor: ");
  Serial.print(calibration_factor);
  Serial.println();
  Serial.print(" position servo ");
Serial.print(positionservo);
Serial.println();

lcd.begin(16,2);
lcd.print("A     vitesse: "   );
lcd.print(vitesse);
lcd.setCursor(0,1);
lcd.print (" pression: " );
lcd.print(scale.get_units());
lcd.setCursor(0,2); 

delay(500);
  
  if(Serial.available())
{
    char temp = Serial.read();
    if(temp == '+' || temp == 'a')
      calibration_factor += 10;
    else if(temp == '-' || temp == 'z')
      calibration_factor -= 10;
  
 }

 int pression = scale.get_units();


if (pression > 40 and positionservo <= 50 ) {
    
  positionservo = positionservo +10;
   
  pression = pression -20;    
  monservo.write (pression); 
   monservo.write (positionservo);
   delay(200);
 }

if (pression < 20 and positionservo >0  ) {
    
  positionservo = positionservo -10;
   
   pression = pression +1;
      monservo.write (pression);
   monservo.write (positionservo);
   delay(200);
   
}
   
 if(positionservo == 0 ) {

  vitesse = 7;
}

 if(positionservo == 10 ) {

  vitesse = 6;
}

 if(positionservo == 20 ) {

  vitesse = 5;
}

 if(positionservo == 30 ) {

  vitesse = 4;
}

 if(positionservo == 40 ) {

  vitesse = 3;
}

 if(positionservo == 50 ) {

  vitesse = 2;
}

 if(positionservo == 60 ) {

  vitesse = 1;
}
}

else if ( choix == 2) {

 lcd.begin(16,2);
 lcd.print("S     vitesse: ");
 lcd.print(vitesse);
 lcd.setCursor(0,1);

 etatboutonG = digitalRead (boutonG);
 etatboutonD = digitalRead (boutonD);

 if (etatboutonG==HIGH and positionservo<60) {
    
  positionservo = positionservo +10;
   monservo.write (positionservo);
   delay(200);
}

if (etatboutonD==HIGH and positionservo>0) {
positionservo = positionservo -10;
monservo.write (positionservo);
delay(200);
}
  if(positionservo == 0 ) {

 vitesse = 7;
}

 if(positionservo == 10 ) {

  vitesse = 6;
}

 if(positionservo == 20 ) {

  vitesse = 5;
}

 if(positionservo == 30 ) {

  vitesse = 4;
}

 if(positionservo == 40 ) {

  vitesse = 3;
}

 if(positionservo == 50 ) {

  vitesse = 2;
}

 if(positionservo == 60 ) {

  vitesse = 1;
}

}
}






 
