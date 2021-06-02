#include <Wire.h> 
#include <PN532_I2C.h> 
#include <PN532.h>   // The following files are included in the libraries Installed
#include <NfcAdapter.h>
PN532_I2C pn532_i2c(Wire);
NfcAdapter nfc = NfcAdapter(pn532_i2c);

#define LED_G 13 //define green LED pin
#define LED_R 4 //define red LED
#define LED_B 6 //define blue LED
#define BUZZER 5 //buzzer pin
int Relay1 = 2;    
int lock1=11;

int Relay2 = 7;    
int lock2=9;

int Relay3 = 8;    
int lock3=12;

int Relay4 = 10;    
int lock4=3;


void setup() 
{
  nfc.begin();
  Serial.begin(57600);
  pinMode(LED_G, OUTPUT);
  digitalWrite(LED_G, LOW);
  pinMode(LED_R, OUTPUT);
  digitalWrite(LED_R, LOW);
  pinMode(LED_B, OUTPUT);
  digitalWrite(LED_B, LOW);
  pinMode(BUZZER, OUTPUT);
  noTone(BUZZER);
  pinMode(lock1, INPUT_PULLUP);           
  pinMode(Relay1, OUTPUT); 
  pinMode(lock2, INPUT_PULLUP);           
  pinMode(Relay2, OUTPUT);
  pinMode(lock3, INPUT_PULLUP);           
  pinMode(Relay3, OUTPUT); 
  pinMode(lock4, INPUT_PULLUP);           
  pinMode(Relay4, OUTPUT); 
}

void loop() {
  int statelock1=digitalRead(lock1);
  int statelock2=digitalRead(lock2);
  int statelock3=digitalRead(lock3);
  int statelock4=digitalRead(lock4);
  static String cardlock1= "nothing";
  static String cardlock2= "nothing";
  static String cardlock3= "nothing";
  static String cardlock4= "nothing";
  //lock1
  if (statelock1==0 && cardlock1== "nothing"){
    wait();
    NfcTag tag = nfc.read();
    if (tag.getUidString().length()==20) {
      good_card_registred();
      cardlock1=tag.getUidString();
      Serial.println(tag.getUidString());
      }
    else   { bad_card_eject(Relay1);}
      }
  //lock2
  if (statelock2==0 && cardlock2== "nothing"){
    wait();
    NfcTag tag = nfc.read();
    if (tag.getUidString().length()==20) {
      good_card_registred();
      cardlock2 = tag.getUidString();
      Serial.println(tag.getUidString());
      }
    else   {
      bad_card_eject(Relay2);
      }
  }
  //lock3
  if (statelock3==0 && cardlock3== "nothing"){
    wait();
    NfcTag tag = nfc.read();
    if (tag.getUidString().length()==20) {
      good_card_registred();
      cardlock3 = tag.getUidString();
      Serial.println(tag.getUidString());
      }
    else   {
      bad_card_eject(Relay3);
      }
  }
   //lock4
  if (statelock4==0 && cardlock4== "nothing"){
    wait();
    NfcTag tag = nfc.read();
    if (tag.getUidString().length()==20) {
      good_card_registred();
      cardlock4=tag.getUidString();
      Serial.println(tag.getUidString());}
    else   { bad_card_eject(Relay4);}
      }
    if (nfc.tagPresent()){
    NfcTag tag = nfc.read();
    if (tag.getUidString()==cardlock1) {
      good_card_ejected(Relay1);
      cardlock1="nothing";
      Serial.println(tag.getUidString());
      }
      else if (tag.getUidString()==cardlock2) {
      good_card_ejected(Relay2);
      cardlock2="nothing";
      Serial.println(tag.getUidString());
      }
      else if (tag.getUidString()==cardlock3) {
      good_card_ejected(Relay3);
      cardlock3="nothing";
      Serial.println(tag.getUidString());
      }
     else if (tag.getUidString()==cardlock4) {
      good_card_ejected(Relay4);
      cardlock4="nothing";
      Serial.println(tag.getUidString());}
     else   {
      bad_card();
      }
      //delay(500);
      }
}




void bad_card_eject(int Relay){
      digitalWrite(LED_B, LOW); 
      noTone(BUZZER);
      delay(50);
      digitalWrite(LED_R, HIGH);          
      tone(BUZZER, 300);
      delay(500);
      noTone(BUZZER);
      digitalWrite(Relay, HIGH); 
      delay(900);
      digitalWrite(Relay, LOW);
      digitalWrite(LED_R, LOW);
      Serial.println("Pas carte UL ou dans CSN courant donc verrou éjécté");
    }

void bad_card(){
      digitalWrite(LED_R, HIGH);          
      tone(BUZZER, 300);
      delay(500);
      noTone(BUZZER);
      digitalWrite(LED_R, LOW);
      Serial.println("Tu n'as pas de vélo garé désolé");
     }

 void good_card_registred(){
      noTone(BUZZER);
      digitalWrite(LED_B, LOW);
      delay(50);
      digitalWrite(LED_G, HIGH);
      tone(BUZZER, 500);
      delay(500);
      noTone(BUZZER);
      digitalWrite(LED_G, LOW);
      Serial.println("Velo gare !");
 }

void good_card_ejected(int Relay){
      digitalWrite(LED_G, HIGH);
      tone(BUZZER, 500);
      delay(500);
      noTone(BUZZER);
      digitalWrite(Relay, HIGH); 
      delay(900);
      digitalWrite(Relay, LOW);
      digitalWrite(LED_G, LOW);
      Serial.println("Velo pris !");
}
void wait(void){
    digitalWrite(LED_B, HIGH); 
    tone(BUZZER, 100);
    while ( ! nfc.tagPresent()){
      tone(BUZZER, 100);
      delay(100);
      noTone(BUZZER);
      }
}
