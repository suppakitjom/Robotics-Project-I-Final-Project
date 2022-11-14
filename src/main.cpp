/*
main file for ESP32 microcontroller
will communicate with spotify controller file
using Serial communication
 */
#include <Arduino.h>
#include <MFRC522.h>
#include <SPI.h>

int PLAYPAUSEBUTTON;
int NEXTBUTTON;
int PREVBUTTON;
int VOLUMEKNOB;
int REPEATBUTTON;
int SHUFFLEBUTTON;

const int SS_PIN = 5;
const int RST_PIN = 27;

int volume;
String cardID;

MFRC522 rfid(SS_PIN, RST_PIN);

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

void setup() {
    pinMode(PLAYPAUSEBUTTON, INPUT_PULLUP);
    pinMode(NEXTBUTTON, INPUT_PULLUP);
    pinMode(PREVBUTTON, INPUT_PULLUP);
    pinMode(VOLUMEKNOB, INPUT);

    Serial.begin(115200);
    SPI.begin();
    while (!Serial) {
        ;
    }
    rfid.PCD_Init();  // init MFRC522
}
String temp;
void loop() {
    temp = getCardID();

    if (temp != cardID) {
        cardID = temp;
        Serial.println(cardID);

        if (cardID.equals(String("81 C0 D7 1B"))) {
            Serial.println("PLAYLIST CHRISTMAS HITS");
        } else if (cardID.equals(String("E3 3D F0 9A"))) {
            Serial.println("TRACK NEVER GONNA GIVE YOU UP");
        } else {
            Serial.println("PAUSE");
        }
    } else {
        cardID = temp;
    }

    if (cardID != "") {
        // reads volume knob input and broadcast change if exist
        // if (volume) {
        //     int newvolume = map(analogRead(VOLUMEKNOB), 0, 4095, 0, 100);
        //     if (newvolume != volume) {
        //         volume = newvolume;
        //         Serial.print("Volume");
        //         Serial.println(volume);
        //     }
        // } else {
        //     volume = map(analogRead(VOLUMEKNOB), 0, 4095, 0, 100);
        //     Serial.print("Volume ");
        //     Serial.println(volume);
        // }

        // // reads play/pause button input and print to Serial if pressed
        // if (digitalRead(PLAYPAUSEBUTTON) == LOW) {
        //     Serial.println("Toggle Playback");
        // }

        // // reads repeat button input and print to Serial if pressed
        // if (digitalRead(REPEATBUTTON) == LOW) {
        //     Serial.println("Toggle Repeat");
        // }

        // // reads shuffle button input and print to Serial if pressed
        // if (digitalRead(SHUFFLEBUTTON) == LOW) {
        //     Serial.println("Toggle Shuffle");
        // }

        // // reads next button input and print to Serial if pressed
        // if (digitalRead(NEXTBUTTON) == LOW) {
        //     Serial.println("Next");
        // }

        // // reads previous button input and print to Serial if pressed
        // if (digitalRead(PREVBUTTON) == LOW) {
        //     Serial.println("Previous");
        // }
    }
}

// // reads volume knob input and broadcast change if exist
//     if (volume) {
//         int newvolume = map(analogRead(VOLUMEKNOB), 0, 4095, 0, 100);
//         if (newvolume != volume) {
//             volume = newvolume;
//             Serial.print("Volume");
//             Serial.println(volume);
//         }
//     } else {
//         volume = map(analogRead(VOLUMEKNOB), 0, 4095, 0, 100);
//         Serial.print("Volume ");
//         Serial.println(volume);
//     }

//     // reads play/pause button input and print to Serial if pressed
//     if (digitalRead(PLAYPAUSEBUTTON) == LOW) {
//         Serial.println("Toggle Playback");
//     }

//     // reads repeat button input and print to Serial if pressed
//     if (digitalRead(REPEATBUTTON) == LOW) {
//         Serial.println("Toggle Repeat");
//     }

//     // reads shuffle button input and print to Serial if pressed
//     if (digitalRead(SHUFFLEBUTTON) == LOW) {
//         Serial.println("Toggle Shuffle");
//     }

//     // reads next button input and print to Serial if pressed
//     if (digitalRead(NEXTBUTTON) == LOW) {
//         Serial.println("Next");
//     }

//     // reads previous button input and print to Serial if pressed
//     if (digitalRead(PREVBUTTON) == LOW) {
//         Serial.println("Previous");
//     }