#include <MFRC522.h>//carte
#include <SPI.h>//carte
 
#define SS_PIN 10
#define RST_PIN 9
#define LED_G 6 //define green LED pin
#define LED_R 4 //define red LED
#define LED_Y 1 //define Yellow LED
#define BUZZER 5 //buzzer pin
MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance.

int Relay1 = 8;    
int lock1=3;

void setup() 
{
  SPI.begin();//Initiate SPI for card reading
  Serial.begin(57600);   // Initiate a serial communication
  mfrc522.PCD_Init();   // Initiate MFRC522
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
  int etatverrou1=digitalRead(lock1); 
}
void loop() {
  digitalWrite(LED_Y, LOW);
  if (statelock1==0){//verrou utilisé
    digitalWrite(LED_Y, HIGH); 
    //tone(BUZZER, 600);
    // Look for new cards
    if ( ! mfrc522.PICC_IsNewCardPresent()) { return;}
    if ( ! mfrc522.PICC_ReadCardSerial()){return;}
    String content= "";
    byte letter;
    for (byte i = 0; i < mfrc522.uid.size; i++) 
    { Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
      Serial.print(mfrc522.uid.uidByte[i], HEX);
      content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
      content.concat(String(mfrc522.uid.uidByte[i], HEX));}
    Serial.print("Carte UL et pas CSN courant ?");
    content.toUpperCase();
    if(Serial.available()>0)
  { uart_rx_buf=char(Serial.read());
  Serial.print(uart_rx_buf);
  Serial.write(Serial.read());
    if(uart_rx_buf=='True')
    { digitalWrite(LED_Y, LOW); 
      noTone(BUZZER);
      digitalWrite(LED_Y, LOW);
      delay(500);
      digitalWrite(LED_G, HIGH);
      tone(BUZZER, 500);
      delay(300);
      noTone(BUZZER);
      delay(3000);
      digitalWrite(LED_G, LOW);
      Serial.println("Velo gare !");
      }
    else   {
      noTone(BUZZER);
      Serial.println("Pas carte UL ou dans CSN courant donc verrou éjécté");
      Serial.println();
      digitalWrite(LED_R, HIGH);          
      tone(BUZZER, 300);
      delay(1000);
      noTone(BUZZER);
      digitalWrite(Relay1, HIGH); 
      delay(2000);
      digitalWrite(Relay1, LOW);
      digitalWrite(LED_R, LOW);
      }
    }
      // Look for new cards
    if ( ! mfrc522.PICC_IsNewCardPresent()) { return;}
    if ( ! mfrc522.PICC_ReadCardSerial()){return;}
    Serial.print("ID card:");
    String content="";
    byte letter;
    for (byte i = 0; i < mfrc522.uid.size; i++) 
    { Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
      Serial.print(mfrc522.uid.uidByte[i], HEX);
      content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
      content.concat(String(mfrc522.uid.uidByte[i], HEX));}
    content.toUpperCase();
    Serial.print("CSN courant ?");
    if(Serial.available()>0)
  { uart_rx_buf=char(Serial.read());
  Serial.write(Serial.read());
    if(uart_rx_buf==true)
    { digitalWrite(LED_G, HIGH);
      tone(BUZZER, 500);
      delay(300);
      noTone(BUZZER);
      digitalWrite(Relay1, HIGH); 
      delay(2000);
      digitalWrite(Relay1, LOW);
      digitalWrite(LED_G, LOW);
      Serial.println("Velo pris !");
    }
     else   {
      digitalWrite(LED_R, HIGH);          
      tone(BUZZER, 300);
      delay(1000);
      noTone(BUZZER);
      digitalWrite(LED_R, LOW);
      Serial.println("Pas de vélo garé désolé");
      }
      uart_rx_buf = 0;//sait pas à quoi ca sert
}
