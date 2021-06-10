//idées : fct setup qui initialise les varibles au démarage à partir du pi puis mode auto en continuant de mettre à j les cartes sur le pi
//hybrid si jamais plus de co avec le pi
//mémoire physique ajoutée sur l'arduino
#include <Wire.h> 
#include <PN532_I2C.h> 
#include <PN532.h>   // The following files are included in the libraries Installed
#include <NfcAdapter.h>
PN532_I2C pn532_i2c(Wire);
NfcAdapter nfc = NfcAdapter(pn532_i2c);

#define LED_G 13 //define green LED pin
#define LED_R 4 //define red LED
#define LED_Y 6 //define blue LED
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
  digitalWrite(LED_Y, LOW);
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
  char static msgPi;
  int statelock1=digitalRead(lock1);
  int statelock2=digitalRead(lock2);
  int statelock3=digitalRead(lock3);
  //lock1
  if (statelock1==0 && """FCT1 nobody at this lock (faire en sorte de pas aller chercher par radio){
    wait();
    NfcTag tag = nfc.read();
    if () {
      good_card_registred();
      Serial.println(tag.getUidString());//card added on the Pi
      }
    else   { bad_card_eject(Relay1);}
      }
  //lock2
 
  //lock3
 
   //lock4
  
    //card passed
      if (nfc.tagPresent()){
    NfcTag tag = nfc.read();
    if ("""FCT3 num carte pour lock1) {
      good_card_ejected(Relay1);
      Serial.println(lock1)//???
      Serial.println(tag.getUidString());//card lock1 deleted on the Pi
      }
    else if 2
    else if 3
    else if 4
     else   {
      bad_card();
      }
      //delay(500);
      }
}



void CSN_courant(String CSN){
    Serial.print("CSN courant ?");
    if(Serial.available()>0)
    { msgPi=char(Serial.read());
    Serial.write(Serial.read());}
    return msgPi
 }

void UL_et_non_courant(string CSN){
    Serial.print("Carte UL et pas CSN courant ?");
    if(Serial.available()>0)
    { msgPi=char(Serial.read());
    Serial.write(Serial.read());}
    return msgPi
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
      Serial.println("Velo gare !");//Website updated
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
      Serial.println("Velo pris !");//website updated
}
void wait(void){
    digitalWrite(LED_B, HIGH); 
    while ( ! nfc.tagPresent()){
      tone(BUZZER, 100);
      delay(200);
      noTone(BUZZER);
      }
}
