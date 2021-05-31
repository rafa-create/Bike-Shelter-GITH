

#define LED_G 6 //define green LED pin
#define LED_R 4 //define red LED
#define LED_Y 1 //define Yellow LED
#define BUZZER 5 //buzzer pin

int Relay1 = 8;    
int lock1=3;

void setup() 
{
  Serial.begin(57600);   // Initiate a serial communication
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
}
void loop() {
  char static msgPi;
  digitalWrite(LED_Y, LOW);
  int statelock1=digitalRead(lock1);
  if (statelock1==0){//verrou utilisé
    digitalWrite(LED_Y, HIGH); 
    //tone(BUZZER, 600);
    // Look for new cards
    
    if(Serial.available()>0)
  { msgPi=char(Serial.read());
  Serial.print(msgPi);
  Serial.write(Serial.read());
    if(msgPi=='True')
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
    Serial.print("CSN courant ?");
    if(Serial.available()>0)
  { msgPi=char(Serial.read());
  Serial.write(Serial.read());
    if(msgPi==true)
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
     }
     }
     msgPi = 0;
}
