#include <Arduino.h>

const uint8_t LED_PIN = 5;
const uint8_t BTN_PIN = 2;

void setup() {

    pinMode(LED_PIN, OUTPUT);
    pinMode(BTN_PIN, INPUT);
    
}

void loop() {

    digitalWrite(LED_PIN, digitalRead(BTN_PIN));

}