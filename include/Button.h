#pragma once

#include <Arduino.h>

struct Button {

    uint8_t pin;
    uint8_t input;
    uint8_t output;

    enum State : uint8_t { free, pressed, held, released } state;

    uint32_t held_start_ms;

    Button(const uint8_t input_pin) { pinMode(pin = input_pin, INPUT); }

    virtual void read() = 0;

    void update() {
        
        switch (state) {
            case State::free:
                if (output) state = State::pressed;
                break;
            case State::pressed:
                if (output) {
                    state = State::held;
                    held_start_ms = millis();
                } else state = State::released;
                break;
            case State::held:
                if (!output) state = State::released;
                break;
            case State::released:
                state = State::free;
                break;
        }
        
    }

    bool isPressed()  { return state == State::pressed; }
    bool isReleased() { return state == State::released; }
    bool isHeld()     { return state == State::held; }
    
    bool wasHeldFor(const uint16_t ms) {
        return isHeld() && (millis() - held_start_ms >= ms);
    }

};