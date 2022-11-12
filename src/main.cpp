/*
main file for ESP32 microcontroller
will communicate with spotify controller file
using Serial communication
 */

#include <Arduino.h>
#include <SPI.h>

const int PLAYPAUSEBUTTON;
const int NEXTBUTTON;
const int PREVBUTTON;
const int VOLUMEKNOB;
const int REPEATBUTTON;
const int SHUFFLEBUTTON;

int volume;

void setup() {
    pinMode(PLAYPAUSEBUTTON, INPUT_PULLUP);
    pinMode(NEXTBUTTON, INPUT_PULLUP);
    pinMode(PREVBUTTON, INPUT_PULLUP);
    pinMode(VOLUMEKNOB, INPUT);

    Serial.begin(115200);
    while (!Serial) {
        ;
    }
}

void loop() {
    // reads volume knob input and broadcast change if exist
    if (volume) {
        int newvolume = map(analogRead(VOLUMEKNOB), 0, 4095, 0, 100);
        if (newvolume != volume) {
            volume = newvolume;
            Serial.print("Volume");
            Serial.println(volume);
        }
    } else {
        volume = map(analogRead(VOLUMEKNOB), 0, 4095, 0, 100);
        Serial.print("Volume ");
        Serial.println(volume);
    }

    // reads play/pause button input and print to Serial if pressed
    if (digitalRead(PLAYPAUSEBUTTON) == LOW) {
        Serial.println("Toggle Playback");
    }

    // reads repeat button input and print to Serial if pressed
    if (digitalRead(REPEATBUTTON) == LOW) {
        Serial.println("Toggle Repeat");
    }

    // reads shuffle button input and print to Serial if pressed
    if (digitalRead(SHUFFLEBUTTON) == LOW) {
        Serial.println("Toggle Shuffle");
    }

    // reads next button input and print to Serial if pressed
    if (digitalRead(NEXTBUTTON) == LOW) {
        Serial.println("Next");
    }

    // reads previous button input and print to Serial if pressed
    if (digitalRead(PREVBUTTON) == LOW) {
        Serial.println("Previous");
    }
}