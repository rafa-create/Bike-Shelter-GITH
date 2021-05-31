#include <Wire.h> 
#include <PN532_I2C.h> 
#include <PN532.h>   // The following files are included in the libraries Installed
#include <NfcAdapter.h>
PN532_I2C pn532_i2c(Wire);
NfcAdapter nfc = NfcAdapter(pn532_i2c);

#define LED_G 6 //define green LED pin
#define LED_R 4 //define red LED
#define LED_Y 13 //define Yellow LED
#define BUZZER 5 //buzzer pin
int Relay1 = 2;    
int lock1=11;
int Relay2 = 7;    
int lock2=9;

void setup(void) 
{
  nfc.begin();
  Serial.begin(57600);
  pinMode(LED_G, OUTPUT);
  digitalWrite(LED_G, LOW);
  pinMode(LED_R, OUTPUT);
  digitalWrite(LED_R, LOW);
  pinMode(LED_Y, OUTPUT);
  digitalWrite(LED_Y, LOW);
  pinMode(BUZZER, OUTPUT);
  noTone(BUZZER);
  pinMode(lock1, INPUT_PULLUP);           
  pinMode(Relay1, OUTPUT); 
  pinMode(lock2, INPUT_PULLUP);           
  pinMode(Relay2, OUTPUT); 
}

void loop(void) {
  int statelock1=digitalRead(lock1);
  int statelock2=digitalRead(lock2);
  static String cardlock1= "nothing";
  static String cardlock2= "nothing";
  //lock1
  if (statelock1==0 && cardlock1== "nothing"){
    digitalWrite(LED_Y, HIGH); 
    tone(BUZZER, 600);
    // Look for new cards to register
     while ( ! nfc.tagPresent()){}//wait
     if (nfc.tagPresent()){
      NfcTag tag = nfc.read();
    Serial.println(tag.getUidString());
    Serial.println("Student card ?");
    if (tag.getUidString().length()==20) {
      cardlock1 = tag.getUidString();
      noTone(BUZZER);
      digitalWrite(LED_Y, LOW);
      Serial.println(" Yes, so registred a this lock");
      Serial.println();
      delay(500);
      digitalWrite(LED_G, HIGH);
      tone(BUZZER, 500);
      delay(300);
      noTone(BUZZER);
      delay(3000);
      digitalWrite(LED_G, LOW);
      }
    else   {
      digitalWrite(LED_Y, LOW); 
      noTone(BUZZER);
      Serial.println(" No, so lock ejected");
      Serial.println();
      digitalWrite(LED_R, HIGH);          
      tone(BUZZER, 300);
      delay(1000);
      noTone(BUZZER);
      digitalWrite(Relay1, HIGH); 
      delay(1000);
      digitalWrite(Relay1, LOW);
      digitalWrite(LED_R, LOW);
      }
    }
  }
  //lock2
  if (statelock2==0 && cardlock2== "nothing"){
    digitalWrite(LED_Y, HIGH); 
    tone(BUZZER, 600);
    // Look for new cards to register
     while ( ! nfc.tagPresent()){}//wait
     if (nfc.tagPresent()){
      NfcTag tag = nfc.read();
    Serial.println(tag.getUidString());
    Serial.println("Student card ?");
    if (tag.getUidString().length()==20) {
      cardlock2 = tag.getUidString();
      noTone(BUZZER);
      digitalWrite(LED_Y, LOW);
      Serial.println(" Yes, so registred a this lock");
      Serial.println();
      delay(500);
      digitalWrite(LED_G, HIGH);
      tone(BUZZER, 500);
      delay(300);
      noTone(BUZZER);
      delay(3000);
      digitalWrite(LED_G, LOW);
      }
    else   {
      digitalWrite(LED_Y, LOW); 
      noTone(BUZZER);
      Serial.println(" No, so lock ejected");
      Serial.println();
      digitalWrite(LED_R, HIGH);          
      tone(BUZZER, 300);
      delay(1000);
      noTone(BUZZER);
      digitalWrite(Relay2, HIGH); 
      delay(1000);
      digitalWrite(Relay2, LOW);
      digitalWrite(LED_R, LOW);
      }
    }
  }
      // Look for new cards to take a bike
      if (nfc.tagPresent()){
    NfcTag tag = nfc.read();
    Serial.println(tag.getUidString());
    Serial.print("Do you have a bike locked ?");//"\nDo you have a bike locked ?\n"
    if (tag.getUidString()==cardlock1) {
      Serial.println(" Yes, so lock ejected");
      Serial.println();
      digitalWrite(LED_G, HIGH);
      tone(BUZZER, 500);
      delay(300);
      noTone(BUZZER);
      digitalWrite(Relay1, HIGH); 
      delay(1000);
      digitalWrite(Relay1, LOW);
      digitalWrite(LED_G, LOW);
      cardlock1= "nothing";}
     else   {
      Serial.println(" No");
      Serial.println();
      digitalWrite(LED_R, HIGH);          
      tone(BUZZER, 300);
      delay(1000);
      noTone(BUZZER);
      digitalWrite(LED_R, LOW);}
    if (tag.getUidString()==cardlock2) {
      Serial.println(" Yes, so lock ejected");
      Serial.println();
      digitalWrite(LED_G, HIGH);
      tone(BUZZER, 500);
      delay(300);
      noTone(BUZZER);
      digitalWrite(Relay2, HIGH); 
      delay(1000);
      digitalWrite(Relay2, LOW);
      digitalWrite(LED_G, LOW);
      cardlock2= "nothing";}
     else   {
      Serial.println(" No");
      Serial.println();
      digitalWrite(LED_R, HIGH);          
      tone(BUZZER, 300);
      delay(1000);
      noTone(BUZZER);
      digitalWrite(LED_R, LOW);}
      }
      delay(500);
}
