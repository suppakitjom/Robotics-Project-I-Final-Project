/*
main file for ESP32 microcontroller
will communicate with spotify controller file
using Serial communication
 */
#include <Adafruit_SSD1306.h>
#include <Arduino.h>
#include <MFRC522.h>
#include <SPI.h>

#include <cmath>

const int PLAYPAUSEBUTTON = 26;
int NEXTBUTTON;
int PREVBUTTON;
const int VOLUMEKNOB = 25;
int REPEATBUTTON;
int SHUFFLEBUTTON;

const int SS_PIN = 5;
const int RST_PIN = 27;
const int OLED_RESET = 4;
const int MOTORENABLE = 15;
const int MOTORIN1 = 2;
const int MOTORIN2 = 4;

int volume = 0;
String cardID;

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

void setup() {
    pinMode(PLAYPAUSEBUTTON, INPUT_PULLUP);
    // pinMode(NEXTBUTTON, INPUT_PULLUP);
    // pinMode(PREVBUTTON, INPUT_PULLUP);
    pinMode(VOLUMEKNOB, INPUT);
    pinMode(MOTORENABLE, OUTPUT);
    pinMode(MOTORIN1, OUTPUT);
    pinMode(MOTORIN2, OUTPUT);

    Serial.begin(115200);
    SPI.begin();
    while (!Serial) {
        ;
    }
    rfid.PCD_Init();                            // init MFRC522
    display.begin(SSD1306_SWITCHCAPVCC, 0x3c);  // init OLED
}
String temp;
int status;
void loop() {
    temp = getCardID();

    if (temp != cardID) {
        cardID = temp;

        if (cardID.equals(String("81 C0 D7 1B"))) {
            Serial.println(cardID);
            Serial.println("PLAYLIST CHRISTMAS HITS");
            status = 1;
            displayText("PLAYING");
        } else if (cardID.equals(String("E3 3D F0 9A"))) {
            Serial.println(cardID);
            Serial.println("TRACK NEVER GONNA GIVE YOU UP");
            status = 1;
            displayText("PLAYING");
        } else {
            Serial.println("Stop");
            status = 0;
            displayText("STOP");
        }
    } else {
        cardID = temp;
    }

    if (cardID != "") {
        // reads volume knob input and broadcast change if exist
        if (volume != analogRead(VOLUMEKNOB)) {
            // average last 10 readings
            int sum = 0;
            for (int i = 0; i < 3; i++) {
                sum += analogRead(VOLUMEKNOB);
            }
            int newVolume = sum / 3;
            newVolume = map(analogRead(VOLUMEKNOB), 0, 4095, 0, 100);
            if (abs(newVolume - volume) >= 4) {
                volume = newVolume;
                Serial.print("Volume ");
                Serial.println(volume);
            }
        }
        // reads play/pause button input and print to Serial if pressed
        if (digitalRead(PLAYPAUSEBUTTON) == LOW) {
            Serial.println("Toggle Playback");
            if (status) {
                status = 0;
                displayText("PAUSED");
            } else {
                status = 1;
                displayText("PLAYING");
            }
            delay(200);
        }

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

    // if status is 1 turn on motor
    if (status) {
        analogWrite(MOTORENABLE, 40);
        digitalWrite(MOTORIN1, HIGH);
        digitalWrite(MOTORIN2, LOW);
    } else {
        analogWrite(MOTORENABLE, 0);
        digitalWrite(MOTORIN1, LOW);
        digitalWrite(MOTORIN2, LOW);
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