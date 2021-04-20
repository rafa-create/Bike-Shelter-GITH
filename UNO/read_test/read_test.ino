//Teste d'abord exactement ce code, ensuite tu devrais pouvoir supprimer des parties si ca marche 

// les librairies : https://github.com/don/NDEF.git et https://github.com/Seeed-Studio/PN532.git
//download zip  ...  extracter ... mettre dans C:\Users\Tobias\Documents\Arduino\libraries  ...
//Pour PN532 : penser à sortir les dossiers du dossier avant de les mettres dans "librairie" (il ne faut pas de dossier intérmediaire)
//Aide en + : https://www.arduino.cc/en/Guide/Libraries#.UxU8mdzF9H0 
#include <Wire.h> 
#include <PN532_I2C.h> 
#include <PN532.h>   // The following files are included in the libraries Installed
#include <NfcAdapter.h>

PN532_I2C pn532_i2c(Wire);
NfcAdapter nfc = NfcAdapter(pn532_i2c);  // Indicates the Shield you are using

void setup(void) {
  Serial.begin(9600);
  Serial.println("NFC TAG READER"); // Header used when using the serial monitor
  nfc.begin();
}

void loop(void) {
  Serial.println("\nScan your NFC tag on the NFC Shield\n");  // Affichage pour l'utilisateur 

  if (nfc.tagPresent())
  {
    NfcTag tag = nfc.read();
    Serial.println(tag.getTagType());
    Serial.print("UID: ");Serial.println(tag.getUidString()); // Retrieves the Unique Identification from your tag
    
//Je pense qu'on poura supprimer cette partie si ca marche :
    if (tag.hasNdefMessage()) // If your tag has a message
    {

      NdefMessage message = tag.getNdefMessage();
      Serial.print("\nThis Message in this Tag is ");
      Serial.print(message.getRecordCount());
      Serial.print(" NFC Tag Record");
      if (message.getRecordCount() != 1) { 
        Serial.print("s");
      }
      Serial.println(".");
      // If you have more than 1 Message then it wil cycle through them
      int recordCount = message.getRecordCount();
      for (int i = 0; i < recordCount; i++)
      {
        Serial.print("\nNDEF Record ");Serial.println(i+1);
        NdefRecord record = message.getRecord(i);

        int payloadLength = record.getPayloadLength();
        byte payload[payloadLength];
        record.getPayload(payload);


        String payloadAsString = ""; // Processes the message as a string vs as a HEX value
        for (int c = 0; c < payloadLength; c++) {
          payloadAsString += (char)payload[c];
        }
        Serial.print("  Information (as String): ");
        Serial.println(payloadAsString);


        String uid = record.getId(); 
        if (uid != "") {
        Serial.print("  ID: ");Serial.println(uid); // Prints the Unique Identification of the NFC Tag 
//Jusque là (pas sur : à tester)
        }
      }
    }
  }
  delay(10000);
}
