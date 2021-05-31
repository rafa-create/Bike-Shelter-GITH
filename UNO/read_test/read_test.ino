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
  nfc.begin();
}

void loop(void) {
  if (nfc.tagPresent())
  {
    NfcTag tag = nfc.read();
    Serial.println(tag.getUidString());
  }
}
