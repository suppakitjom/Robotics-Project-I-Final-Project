#include <Arduino.h>
#include <SPI.h>

void setup() {
    Serial.begin(115200);
    while (!Serial) {
        ;
    }
}

void loop() {
    Serial.println("ALBUM CHARLIE");
    delay(10000);
    Serial.println("TRACK NEVER GONNA GIVE YOU UP");
    delay(10000);
}