void initRfid();
void runRFID();

#include "MFRC522.h"

// Sette opp RFID
#define RST_PIN D2 // RST-PIN for RC522 - RFID - SPI - Modul GPIO15 
#define SS_PIN  D8  // SDA-PIN for RC522 - RFID - SPI - Modul GPIO2
// Sette opp LED-ring

MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance

void initRfid() {
  SPI.begin();           // Init SPI bus
  mfrc522.PCD_Init();    // Init MFRC522 
  
  Serial.println("Connected to RFID");
}

void runRFID() { 
  // Look for new cards
  
  if ( ! mfrc522.PICC_IsNewCardPresent()) {
    delay(50);
    return;
  }
  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial()) {
    delay(50);
    return;
  }
  
  String card = "";
    for (byte i = 0; i < 4; i++) {
      card += String(mfrc522.uid.uidByte[i], HEX);
    }
  
  // Show some details of the PICC (that is: the tag/card)
  Serial.print(F("Card UID:"));
  Serial.print(card);
  delay(1000);
  sendGet(card);
}
