//HOME AUTOMATION CODDED BY SURYA PRAKASH GUPTA
//VERSION 1.2
//COMPATABLE WITH ARDINO NANO
#include <IRremote.h>
#include<dht.h>
dht DHT;
#define DHT11_PIN 3
float temp;
int sensorPin = A7; // select the input pin for ldr
int sensorValue = 0; // variable to store the value coming from the sensor
int ledpin = 8; 
int RECV_PIN = A0;
int RELAY1 = A5;
int RELAY2 = A2;
int RELAY3 = A3;
int RELAY4 = A4;
int smokeA0 = A1;
int tempPin =A6;
int inputPin = 7;  
int itsON =1;
int pirState = LOW;             // we start, assuming no motion detected
int val = 0;
int delayValue = 1000;
int OFFDELAY=1000;
 int aut = 1;
IRrecv irrecv(RECV_PIN);
decode_results results;
void setup() {                
  // initialize the digital pin as an output.  
   
  pinMode(RECV_PIN, INPUT); 
  pinMode(RELAY1, OUTPUT);
  pinMode(RELAY2, OUTPUT);
  pinMode(RELAY3, OUTPUT);
  pinMode(RELAY4, OUTPUT);
  pinMode(ledpin, OUTPUT);
  pinMode(smokeA0, INPUT);
   pinMode(inputPin, INPUT);     // declare  motion sensor as input
  digitalWrite(RELAY1,HIGH);
  digitalWrite(RELAY2,HIGH);
  digitalWrite(RELAY3,HIGH);
  digitalWrite(RELAY4,HIGH);

  irrecv.enableIRIn(); // Start the receiver
  Serial.begin(9600);
  
}
void loop() {

  if (aut==0)
  {
    digitalWrite(ledpin,LOW);//
 
 
 autonomous();
  }
 else
 {
 digitalWrite(ledpin,HIGH);

  }
   if (irrecv.decode(&results)) { 
        
   translateIR();
     irrecv.resume(); // Receive the next value  
       
   } 
   }

void autonomous()
{
// ***********TEMPARATURE PART***********
temp = analogRead(tempPin);
temp = temp * 0.03828125;
Serial.print("TEMPRATURE = ");
Serial.print(temp);
Serial.print("*C");
Serial.println();

if (temp > 60)
{
   Serial.println("Danger ahead");
    digitalWrite(RELAY4,LOW); 
}

//*************************GAS DETECTION PART***************
int analogSensor = analogRead(smokeA0);


 Serial.print("Gas Value ");
  sensorValue = analogSensor; // read the value from the sensor
Serial.println(sensorValue); //prints the values coming from the sensor on the screen


delay(1000);
if (sensorValue>400)
{
  Serial.println("Danger ahead");
    digitalWrite(RELAY4,LOW);
}
else
{
    digitalWrite(RELAY4,HIGH);
}

//***************LIGHT PART  ********

int sensorldr = analogRead(sensorPin); // read the value from the sensor
Serial.println(sensorldr);
if (sensorldr<300)
{
  Serial.println("nightmode on");
    digitalWrite(RELAY3,LOW);
}
else
{
  Serial.println("nightmode off");
    digitalWrite(RELAY3,HIGH);
}



//**********PIR SECTION

val = digitalRead(inputPin);  // read input value
  if (val == HIGH) {            // check if the input is HIGH
     digitalWrite(RELAY1,HIGH); 
    
    if (pirState == LOW) {
      // we have just turned on
      Serial.println("Motion detected!");
      digitalWrite(RELAY1,LOW);
    }
  } else {
    digitalWrite(RELAY1, HIGH); // turn LED OFF
    if (pirState == HIGH){
      // we have just turned of
      Serial.println("Motion ended!");
      digitalWrite(RELAY1, HIGH);
  
    }
  }




  }

//***********REMOTE PART*********  
void translateIR()
 {
switch(results.value){
  case 0x1FE48B7 : 
   
    Serial.println(" ALL OFF   "); 
    if (itsON ==0){
   digitalWrite(RELAY1, HIGH);
     digitalWrite(RELAY2, HIGH);
       digitalWrite(RELAY3, HIGH);
         digitalWrite(RELAY4,HIGH);
         itsON=1;
         aut =1;
         delay(delayValue);
    }
    else
    {
       Serial.println(" ALL on   "); 
        digitalWrite(RELAY1, LOW);
        digitalWrite(RELAY2, LOW);
        digitalWrite(RELAY3, LOW);
        digitalWrite(RELAY4,LOW);
         itsON=0;
         aut=1;
         delay(delayValue);
    }
    break;
  case 0x1FE50AF:  //relay1 
   if (itsON ==0){
    Serial.println("  Relay 1 OF          ");
     digitalWrite(RELAY1, HIGH); 
      itsON=1;
      delay(delayValue);
   }
   else
   {
     digitalWrite(RELAY1,LOW);
         itsON=0;
         delay(delayValue);
   }
    break;
  case 0x1FED827:  //2
    if (itsON ==0){
    Serial.println("  Relay 2 OF          ");
     digitalWrite(RELAY2, HIGH); 
      itsON=1;
      delay(delayValue);
   }
   else
   {
     digitalWrite(RELAY2,LOW);
         itsON=0;
         delay(delayValue);
   }
    break;
  case 0x1FEF807:  //3
     if (itsON ==0){
    Serial.println("  Relay 3 OF          ");
     digitalWrite(RELAY3, HIGH); 
      itsON=1;
      delay(delayValue);
   }
   else
   {
     digitalWrite(RELAY3,LOW);
         itsON=0;
         delay(delayValue);
   }
    break;
     case 0x1FE30CF:  //4
    if (itsON ==0){
    Serial.println("  Relay 4 OF          ");
     digitalWrite(RELAY4, HIGH); 
      itsON=1;
      delay(delayValue);
   }
   else
   {
     digitalWrite(RELAY4,LOW);
         itsON=0;
         delay(delayValue);
   }
    break;
  case 0x1FE40BF: //LEFT KEY
   if (itsON ==0){
    Serial.println("  Relay 1,2 OF          ");
     digitalWrite(RELAY1, HIGH);
     digitalWrite(RELAY2, HIGH);  
      itsON=1;
      delay(OFFDELAY);
   }
   else
   {
     digitalWrite(RELAY1,LOW);
     digitalWrite(RELAY2,LOW);
         itsON=0;
         delay(delayValue);
   }
    break;
  case 0x1FEC03F: //right KEY
   if (itsON ==0){
    Serial.println("  Relay 1,2 OF          ");
     digitalWrite(RELAY4, HIGH);
     digitalWrite(RELAY3, HIGH);  
      itsON=1;
      delay(OFFDELAY);
   }
   else
   {
     digitalWrite(RELAY3,LOW);
     digitalWrite(RELAY4,LOW);
         itsON=0;
         delay(delayValue);
   }
    break;
    
    case 0xFFFFFFFF:
      Serial.println("You have pressed the buton for long time");
      break;
      case 0x1FE20DF:
      Serial.println("Ghost Mode // Test mode");
       
              digitalWrite(RELAY1, LOW);
              delay(1000);
              Serial.println("Done");
        digitalWrite(RELAY2, LOW);
         delay(1000);
         Serial.println("Done");
        digitalWrite(RELAY3, LOW);
         delay(1000);
         Serial.println("Done");
        digitalWrite(RELAY4,LOW);
         delay(1000);
         Serial.println("Done");
      digitalWrite(RELAY1, HIGH);
       delay(1000);
       Serial.println("Done");
     digitalWrite(RELAY2, HIGH);
     delay(1000);
     Serial.println("Done");
       digitalWrite(RELAY3, HIGH);
       delay(1000);
       Serial.println("Done");
         digitalWrite(RELAY4,HIGH);
          delay(1000);
          Serial.println("Done");
     Serial.println("Test Done Hope you can listen 8 sound to confirm the working");  
    break; 
  case 0x1FE906F:
  Serial.print("AUTOMATION MODE ON");
autonomous();
 if (itsON ==0){
    aut=1;
      itsON=1;
     //  digitalWrite(ledpin,HIGH);
      delay(delayValue);
   }
   else
   {
     aut =0;
         itsON=0;
         delay(delayValue);
         // digitalWrite(ledpin,LOW);
   }

//Serial.println(analogSensor);

break;
 

 default: 
    Serial.println("Unknown Input From Remote");
    Serial.println(results.value, HEX);


break;
    
 }
delay(1);
 }
                  


