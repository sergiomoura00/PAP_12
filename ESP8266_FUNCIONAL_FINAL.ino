//////////////////////////////////////////////////////////////
//                   Plataforma Elevatória                  //
//              Segurança e Controlo Industrial             //
//                  Criado por Sérgio Moura                 //
//////////////////////////////////////////////////////////////

#define BLYNK_PRINT Serial

#include <SPI.h>
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <TimeLib.h>
#include <WidgetRTC.h>
#include <LiquidCrystal_I2C.h>

char auth[] = "c70ebd9de3e8447ca7970242fec67098";
/*char auth[] = "c4e5f1c8ca734c15b721792a44f98685";*/
char ssid[] = "Vodafone-3F67B0";
char pass[] = "PASS***********";

LiquidCrystal_I2C lcd(0x3F, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);
BlynkTimer timer;
WidgetRTC rtc;

//--------------------------------------

const int hallSensorPin1 =  1;
const int hallSensorPin2 =  16;
const int hallSensorPin3 =  0;
const int hallSensorPin4 =  2;

int hallstate1 = 0;    
int hallstate2 = 0;    
int hallstate3 = 0;    
int hallstate4 = 0;   

int ledPin1 =  14;    
int ledPin2 =  12;    
int ledPin3 =  13;    
int ledPin4 =  15;   
 
int mensagem;

//--------------------------------------

 byte oooo[8] = {
  0b00001, 
  0b00010, 
  0b01110,
  0b10001,
  0b10001,
  0b10001,
  0b01110,
  0b00000
};

//--------------------------------------

unsigned long clockatual;
unsigned long clocksalvo = 0;
unsigned long toggleatual;
unsigned long togglesalvo = 0;
unsigned long mensatual;
unsigned long menssalvo = 0;

long clockresult = 1000;
long toggleresult = 3000;
long mensresult = 1000;

//-------------------------------------

void setup(){
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass);
  lcd.begin (20,4);
  
  setSyncInterval(10 * 60);
  timer.setInterval(1000L, clockDisplay);
  
  lcd.createChar(0, oooo);
  lcd.setBacklight(LOW);
  lcd.setBacklight(HIGH);
 
  pinMode(ledPin1, OUTPUT);
  pinMode(ledPin2, OUTPUT);
  pinMode(ledPin3, OUTPUT);
  pinMode(ledPin4, OUTPUT);

  pinMode(hallSensorPin1, INPUT);
  pinMode(hallSensorPin2, INPUT);
  pinMode(hallSensorPin3, INPUT);
  pinMode(hallSensorPin4, INPUT);

 digitalWrite(ledPin1, LOW);
 digitalWrite(ledPin2, LOW);     
 digitalWrite(ledPin3, LOW);     
 digitalWrite(ledPin4, LOW);      
  
  
  mensagem = 0;
  }

//----------------------------------------------

 void loop()
 { 
 Blynk.run();
 timer.run();
 Tempos();
 BUTTON();
 
 clockatual = millis();
 toggleatual = millis();
 mensatual = millis();
 
 hallstate1 = digitalRead(hallSensorPin1);
 hallstate2 = digitalRead(hallSensorPin2);
 hallstate3 = digitalRead(hallSensorPin3);
 hallstate4 = digitalRead(hallSensorPin4);
 }


 //--------------------------------------

void Tempos()
{  
  if (clockatual - clocksalvo >= clockresult){
    clockDisplay();
    clocksalvo = clockatual;}

  if (toggleatual - togglesalvo >= toggleresult){
    Toggle();
    togglesalvo = toggleatual;}
  
  if (mensatual - menssalvo >= mensresult){
    Mensagem();
    menssalvo = mensatual;}
}

//--------------------------------------

void Toggle()
{
  if(mensagem == 0){
    mensagem = 1;
    }else{
    mensagem = 0;}
    }
    
//--------------------------------------

void Mensagem()
{
  if(mensagem == 1){
   lcd.setCursor(0,3);
     lcd.print("                    ");
   lcd.setCursor(0,3);
     lcd.print("Plat. Elevat");
     lcd.write(byte(0));
     lcd.print("ria");}
  if(mensagem == 0){
   lcd.setCursor(0,3);
     lcd.print("                    ");
   lcd.setCursor(0,3);
     lcd.print("Projeto PAP - 12GEI");
     }
  }
  
//--------------------------------------

void clockDisplay()
{
  String currentTime = String(hour()) + ":" + minute();
  String currentDate = String(day()) + "/" + month() + "/" + year();
  lcd.setCursor(0,0);
  lcd.write("                    ");
  lcd.setCursor(0,0);
  lcd.print(currentTime);
  lcd.setCursor(11,0);
  lcd.print(currentDate);
  Blynk.virtualWrite(V4, currentTime);
  Blynk.virtualWrite(V5, currentDate);
}
BLYNK_CONNECTED() {
  rtc.begin();
}

//---------------------------------------

 void BUTTON()
 {
   if(hallstate1 == HIGH){
   digitalWrite(ledPin1, HIGH);
   digitalWrite(ledPin2, LOW);
   digitalWrite(ledPin3, LOW);
   digitalWrite(ledPin4, LOW);

   lcd.setCursor(5,2);
   lcd.print("                                ");
   lcd.print("Piso 1");
  }
  
   if(hallstate2 == HIGH){
   digitalWrite(ledPin2, HIGH);
   digitalWrite(ledPin1, LOW);
   digitalWrite(ledPin3, LOW);
   digitalWrite(ledPin4, LOW);

   lcd.setCursor(5,2);
   lcd.print("                                ");
   lcd.print("Piso 2");
  }
  
   if(hallstate3 == HIGH){
   digitalWrite(ledPin3, HIGH);
   digitalWrite(ledPin1, LOW);
   digitalWrite(ledPin2, LOW);
   digitalWrite(ledPin4, LOW);
   
   lcd.setCursor(5,2);
   lcd.print("                                ");
   lcd.print("Piso 3");
  }
  
   if(hallstate4 == HIGH){
   digitalWrite(ledPin4, HIGH);
   digitalWrite(ledPin1, LOW);
   digitalWrite(ledPin2, LOW);
   digitalWrite(ledPin3, LOW);

   lcd.setCursor(5,2);
   lcd.print("                                ");
   lcd.print("Piso 4");
  }
 }
 
//--------------------------------------

/*
BLYNK_WRITE(V0)
{  
int pinValue = param.asInt();
if (pinValue==1){
        lcd.setCursor(7,1);
        lcd.print("      ");
        lcd.setCursor(7,1);
        lcd.print("PISO 1");}}
        
BLYNK_WRITE(V1)
{  
int pinValue = param.asInt();
if (pinValue==1){
        lcd.setCursor(7,1);
        lcd.print("      ");
        lcd.setCursor(7,1);
        lcd.print("PISO 2");}}
        
BLYNK_WRITE(V2)
{  
int pinValue = param.asInt();
if (pinValue==1){
        lcd.setCursor(7,1);
        lcd.print("      ");
        lcd.setCursor(7,1);
        lcd.print("PISO 3");}}
        
BLYNK_WRITE(V3)
{  
int pinValue = param.asInt();
if (pinValue==1){
        lcd.setCursor(7,1);
        lcd.print("      ");
        lcd.setCursor(7,1);
        lcd.print("PISO 4");}}
        */
