/*
main file for ESP32 microcontroller
will communicate with spotify controller file
using Serial communication
 */

#include <Adafruit_SSD1306.h>
#include <Arduino.h>
#include <MFRC522.h>
#include <SPI.h>

// pins declaration
const int PLAYPAUSEBUTTON = 26;
const int NEXTBUTTON = 33;
const int PREVBUTTON = 32;
const int VOLUMEKNOB = 25;
const int REPEATBUTTON = 16;
const int SHUFFLEBUTTON = 17;

const int SS_PIN = 5;
const int RST_PIN = 27;
const int OLED_RESET = 4;
const int MOTORENABLE = 15;
const int MOTORIN1 = 2;
const int MOTORIN2 = 4;

int volume = 0;
int newVolume;
String cardID;
String tempCardID;
bool isPlaying;

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
    // set pinMode for all pins
    pinMode(PLAYPAUSEBUTTON, INPUT_PULLUP);
    pinMode(NEXTBUTTON, INPUT_PULLUP);
    pinMode(PREVBUTTON, INPUT_PULLUP);
    pinMode(REPEATBUTTON, INPUT_PULLUP);
    pinMode(SHUFFLEBUTTON, INPUT_PULLUP);
    pinMode(VOLUMEKNOB, INPUT);
    pinMode(MOTORENABLE, OUTPUT);
    pinMode(MOTORIN1, OUTPUT);
    pinMode(MOTORIN2, OUTPUT);

    Serial.begin(115200);
    SPI.begin();
    rfid.PCD_Init();                            // init MFRC522
    display.begin(SSD1306_SWITCHCAPVCC, 0x3c);  // init OLED
}

void loop() {
    // get card id
    tempCardID = getCardID();

    // checks if card id is not the same as the last one
    // if changes, check if it is registered then play corresponding track
    if (tempCardID != cardID) {
        cardID = tempCardID;
        // Serial.println(cardID);
        if (cardID.equals(String("81 C0 D7 1B"))) {
            Serial.println("PLAYLIST CHRISTMAS HITS");
            displayText("PLAYING");
            isPlaying = true;
        } else if (cardID.equals(String("E3 3D F0 9A"))) {
            Serial.println("TRACK NEVER GONNA GIVE YOU UP");
            displayText("PLAYING");
            isPlaying = true;
        } else if (cardID.equals(String("E3 FB 80 04"))) {
            Serial.println("ALBUM BLUE NEIGHBORHOOD");
            displayText("PLAYING");
            isPlaying = true;
        } else if (cardID.equals(String("D3 5D 96 04"))) {
            Serial.println("ALBUM BEINGFUNNYINFOREIGNLANGUAGE");
            displayText("PLAYING");
            isPlaying = true;
        } else if (cardID.equals(String("03 6C EB 05"))) {
            Serial.println("ALBUM SMITHEREENS");
            displayText("PLAYING");
            isPlaying = true;
        } else if (cardID.equals(String("23 62 97 04"))) {
            Serial.println("PLAYLIST JOMS ESSENTIALS");
            displayText("PLAYING");
            isPlaying = true;
        } else if (cardID.equals(String("53 79 83 06"))) {
            Serial.println("ALBUM MAKING STEAK");
            displayText("PLAYING");
            isPlaying = true;
        } else {
            Serial.println("Stop");
            displayText("STOP");
            isPlaying = false;
        }
    }

    if (cardID != "") {
        if (volume != analogRead(VOLUMEKNOB)) {
            // average reading of potentiometer to decrease fluctuations
            int sum = 0;
            for (int i = 0; i < 5; i++) {
                sum += analogRead(VOLUMEKNOB);
            }
            newVolume = sum / 5;
            newVolume = map(newVolume, 0, 4095, 0, 100);
            // only send new volume if it is a significant change
            //(cannot update for every loop as Python script cannot keep up)
            if (abs(newVolume - volume) > 4) {
                volume = newVolume;
                Serial.print("Volume ");
                Serial.println(volume);
            }
        }

        // reads play/pause button input and print to Serial if pressed
        if (digitalRead(PLAYPAUSEBUTTON) == LOW) {
            Serial.println("Toggle Playback");
            if (isPlaying) {
                displayText("PAUSED");
                isPlaying = false;
            } else {
                displayText("PLAYING");
                isPlaying = true;
            }
            delay(200);
        }

        // reads repeat button input and print to Serial if pressed
        if (digitalRead(REPEATBUTTON) == LOW) {
            Serial.println("Toggle Repeat");
            delay(200);
        }

        // reads shuffle button input and print to Serial if pressed
        if (digitalRead(SHUFFLEBUTTON) == LOW) {
            Serial.println("Toggle Shuffle");
            delay(200);
        }

        // reads next button input and print to Serial if pressed
        if (digitalRead(NEXTBUTTON) == LOW) {
            Serial.println("Next");
            delay(200);
        }

        // reads previous button input and print to Serial if pressed
        if (digitalRead(PREVBUTTON) == LOW) {
            Serial.println("Previous");
            delay(200);
        }
    }

    // if isPlaying is 1 turn on motor else turn off motor
    if (isPlaying) {
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