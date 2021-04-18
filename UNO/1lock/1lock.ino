 
 /*RST/Reset   RST          9             5         D9         RESET/ICSP-5     RST
 * SPI SS      SDA(SS)      10            53        D10        10               10
 * SPI MOSI    MOSI         11 / ICSP-4   51        D11        ICSP-4           16
 * SPI MISO    MISO         12 / ICSP-1   50        D12        ICSP-1           14
 * SPI SCK     SCK          13 / ICSP-3   52        D13        ICSP-3           15
 */
 
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
  int statelock1=digitalRead(lock1);
  static String cardlock1= "nothing";
  if (statelock1==0 && cardlock1== "nothing"){
    digitalWrite(LED_Y, HIGH); 
    //tone(BUZZER, 600);
    // Look for new cards
    if ( ! mfrc522.PICC_IsNewCardPresent()) { return;}
    if ( ! mfrc522.PICC_ReadCardSerial()){return;}
    Serial.print("Card ID :");
    String content= "";
    byte letter;
    for (byte i = 0; i < mfrc522.uid.size; i++) 
    { Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
      Serial.print(mfrc522.uid.uidByte[i], HEX);
      content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
      content.concat(String(mfrc522.uid.uidByte[i], HEX));}
    Serial.println();
    Serial.print("Student card: ");
    content.toUpperCase();
    if (content.substring(1).length()==20 ||content.substring(1).length() =="04 33 5B B2 7A 57 80") {
      cardlock1 = content.substring(1);
      digitalWrite(LED_Y, LOW); 
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
      noTone(BUZZER);
      Serial.println(" No, so lock ejected");
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
    Serial.println();
    Serial.print("Do you have a bike locked ?");
    content.toUpperCase();
    if (content.substring(1) ==cardlock1) {
      Serial.println(" Yes, so lock ejected");
      Serial.println();
      digitalWrite(LED_G, HIGH);
      tone(BUZZER, 500);
      delay(300);
      noTone(BUZZER);
      digitalWrite(Relay1, HIGH); 
      delay(2000);
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
}
