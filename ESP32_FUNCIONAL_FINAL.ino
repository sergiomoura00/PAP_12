//////////////////////////////////////////////////////////////
//                   Plataforma Elevatória                  //
//              Segurança e Controlo Industrial             //
//                  Criado por Sérgio Moura                 //
//////////////////////////////////////////////////////////////

#define BLYNK_PRINT Serial
#define STEPS 200

#include <Stepper.h>
#include <SPI.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

char auth[] = "c70ebd9de3e8447ca7970242fec67098";
char ssid[] = "Vodafone-3F67B0";
char pass[] = "PASS***********";

Stepper stepper(STEPS, 32, 33, 27, 4);

  int Piso1;
  int Piso2;
  int Piso3;
  int Piso4;
  
  int MOTOR1 = 32;
  int MOTOR2 = 33;
  int MOTOR3 = 27;
  int MOTOR4 = 4;

  int ledPin1 =  25;    
  int ledPin2 =  26;    
  int ledPin3 =  22;    
  int ledPin4 =  21;   

  int buttonState1 = 0;
  int buttonState2 = 0;
  int buttonState3 = 0;
  int buttonState4 = 0;

  const int BUTTON1 =  34;
  const int BUTTON2 =  35;
  const int BUTTON3 =  16;
  const int BUTTON4 =  17;

  
//-------------------------------------

void setup(){
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass);
  stepper.setSpeed(250);
    
  pinMode(MOTOR1, OUTPUT);
  pinMode(MOTOR2, OUTPUT);
  pinMode(MOTOR3, OUTPUT);
  pinMode(MOTOR4, OUTPUT);

  pinMode(ledPin1, OUTPUT);
  pinMode(ledPin2, OUTPUT);
  pinMode(ledPin3, OUTPUT);
  pinMode(ledPin4, OUTPUT);

  pinMode(BUTTON1, INPUT);
  pinMode(BUTTON2, INPUT);
  pinMode(BUTTON3, INPUT);
  pinMode(BUTTON4, INPUT);
  }

//----------------------------------------------

 void loop()
 {
 Blynk.run();
 BUTTON();
 
 buttonState1 = digitalRead(BUTTON1);
 buttonState2 = digitalRead(BUTTON2);
 buttonState3 = digitalRead(BUTTON3);
 buttonState4 = digitalRead(BUTTON4);
 }
 
//-----------------------------------------

 void LEDPIN1()
 {
digitalWrite(ledPin1, HIGH);
digitalWrite(ledPin2, LOW);
digitalWrite(ledPin3, LOW);
digitalWrite(ledPin4, LOW);
 }
 
 void LEDPIN2()
 {
digitalWrite(ledPin2, HIGH);
digitalWrite(ledPin1, LOW);
digitalWrite(ledPin3, LOW);
digitalWrite(ledPin4, LOW);
 }
 
 void LEDPIN3()
 {
digitalWrite(ledPin3, HIGH);
digitalWrite(ledPin1, LOW);
digitalWrite(ledPin2, LOW);
digitalWrite(ledPin4, LOW);
 }
 
 void LEDPIN4()
 {
digitalWrite(ledPin4, HIGH);
digitalWrite(ledPin1, LOW);
digitalWrite(ledPin2, LOW);
digitalWrite(ledPin3, LOW);
 }

//------------------------------------------
 
 void OFF()
{
  digitalWrite(MOTOR1, LOW);
  digitalWrite(MOTOR2, LOW);
  digitalWrite(MOTOR3, LOW);
  digitalWrite(MOTOR4, LOW);
  }

//------------------------------------------

 void BUTTON()
 {
  if(buttonState1 == HIGH){
   PISO0();
  }
  
   if(buttonState2 == HIGH){
   PISO1();
  }
  
   if(buttonState3 == HIGH){
   PISO2();
  }
  
   if(buttonState4 == HIGH){
   PISO3();
  }
 }

//------------------------------------------

  void PISO0()
  {
      if (Piso1 == 0) {         
        if (Piso2 == 0) {
           if (Piso3 == 0) {
              if (Piso4 == 0) {
              stepper.step(-10950);
              Piso1 = 1;
              Piso4 = 0;
            }else{
              stepper.step(-10950);
              Piso1 = 1;
              Piso4 = 0;}
            }else{    
              stepper.step(-7150);
              Piso1 = 1;
              Piso3 = 0;}
            }else{    
              stepper.step(-3550);
              Piso1 = 1;
              Piso2 = 0;} 
            }else{
              Piso1 = 1;}
   OFF();
   LEDPIN1();
  }

  void PISO1()
  {
    if (Piso1 == 0) {         
        if (Piso2 == 0) {
           if (Piso3 == 0) {
              if (Piso4 == 0) {
              stepper.step(-7400);
              Piso2 = 1;
              Piso4 = 0;
            }else{
              stepper.step(-7400);
              Piso2 = 1;
              Piso4 = 0;}
            }else{    
              stepper.step(-3600);
              Piso2 = 1;
              Piso3 = 0;}
            }else{
              Piso2 = 1;} 
            }else{
              stepper.step(3550);
              Piso2 = 1;
              Piso1 = 0;}
   OFF();
   LEDPIN2();
  }

  void PISO2()
  {
     if (Piso1 == 0) {         
        if (Piso2 == 0) {
           if (Piso3 == 0) {
              if (Piso4 == 0) {
              stepper.step(-3800);
              Piso3 = 1;
              Piso4 = 0;
            }else{
              stepper.step(-3800);
              Piso3 = 1;
              Piso4 = 0;}
            }else{
              Piso3 = 1;}
            }else{    
              stepper.step(3600);
              Piso3 = 1;
              Piso2 = 0;} 
            }else{
              stepper.step(7150);
              Piso3 = 1;
              Piso1 = 0;}
   OFF();
   LEDPIN3();
   }
  
  void PISO3()
  {
    if (Piso1 == 0) {         
        if (Piso2 == 0) {
           if (Piso3 == 0) {
              if (Piso4 == 0) {
              Piso4 = 1;
            }else{
              Piso4 = 1;}
            }else{    
              stepper.step(3800);
              Piso4 = 1;
              Piso3 = 0;}
            }else{    
              stepper.step(7400);
              Piso4 = 1;
              Piso2 = 0;} 
            }else{
              stepper.step(10950);
              Piso4 = 1;
              Piso1 = 0;}
   OFF();
   LEDPIN4();
  }

//----------------------------------------------
 
BLYNK_WRITE(V0)
{  
int pinValue = param.asInt();
 if (pinValue==1){
  PISO0();
      }
      }

BLYNK_WRITE(V1)
{
int pinValue = param.asInt();
 if (pinValue==1){
  PISO1();
      }
      }
      
BLYNK_WRITE(V2)
{
int pinValue = param.asInt();
 if (pinValue==1){
  PISO2();
      } 
      }
      
BLYNK_WRITE(V3)
{
int pinValue = param.asInt();
 if (pinValue==1){
  PISO3();
      }
      }

