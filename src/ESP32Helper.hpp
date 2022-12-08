/*
Helper functions for ESP32
includes all the header files for the RC522 RFID reader
and the SSD1306 OLED display
*/

#include <Adafruit_SSD1306.h>
#include <MFRC522.h>

#include "pinSettings.hpp"  // import pin numbers

MFRC522 rfid(SS_PIN, RST_PIN);
Adafruit_SSD1306 display(OLED_RESET);

void displayText(String text) {
    // display text on OLED
    display.clearDisplay();
    display.setTextSize(3);
    display.setTextColor(WHITE);
    display.setCursor(0, 0);
    display.println(text);
    display.display();
}

String getCardID() {
    // if card detected return its id
    if (rfid.PICC_IsNewCardPresent() && rfid.PICC_ReadCardSerial()) {
        // convert UID to string
        String content = "";
        for (byte i = 0; i < rfid.uid.size; i++) {
            content.concat(String(rfid.uid.uidByte[i] < 0x10 ? " 0" : " "));
            content.concat(String(rfid.uid.uidByte[i], HEX));
        }
        content.toUpperCase();
        content.trim();

        while (rfid.PICC_IsNewCardPresent() && rfid.PICC_ReadCardSerial()) {
            // do nothing
        }

        rfid.PICC_HaltA();
        rfid.PCD_StopCrypto1();
        return content;
    } else {
        return "";
    }
}