/* Copyright (c) 2023 Mattias Ohlsson. All rights reserved.
 * 
 * This work is licensed under the terms of the MIT license.  
 * For a copy, see <https://opensource.org/licenses/MIT>.
 */
#include <Keyboard.h>
#include <SPI.h>
#include <MFRC522.h>
#include <Keyboard_sv_SE.h>

#define RST_PIN         2         // Configurable, see typical pin layout above
#define SS_PIN          6         // Configurable, see typical pin layout above

MFRC522 rfid(SS_PIN, RST_PIN); // Instance of the class
 
MFRC522::MIFARE_Key key; 
 
void setup() {                    
  SPI.begin(); // Init SPI bus
  rfid.PCD_Init(); // Init RC522 
  Keyboard.begin();
}
 
void loop() {
 
  // Reset the loop if no new card present on the sensor/reader. This saves the entire process when idle.
  if ( ! rfid.PICC_IsNewCardPresent())
    return;
 
  // Verify if the NUID has been readed
  if ( ! rfid.PICC_ReadCardSerial())
    return;
 
  MFRC522::PICC_Type piccType = rfid.PICC_GetType(rfid.uid.sak);
 
  printHex(rfid.uid.uidByte, rfid.uid.size);      
  //creates the variable uid
  char uid[16], *head = uid;
  for(int i = 0; i < 3; i++, head += 3)
    snprintf(head, 4, "%02X>", (byte)rfid.uid.uidByte[i]);
  snprintf(head, 3, "%02X", (byte)rfid.uid.uidByte[3]);

  //writes uid and goes to next form
  Keyboard.print(uid);
  Keyboard.write('\t');
  delay(10000);
 
  rfid.PICC_HaltA(); // Halt PICC
}
 
//Routine to dump a byte array as hex values to Serial. 
void printHex(byte *buffer, byte bufferSize) {
  for (byte i = 0; i < bufferSize; i++) {
    Serial.print(buffer[i] < 0x10 ? " 0" : " ");
    Serial.print(buffer[i], HEX);
  }
}
