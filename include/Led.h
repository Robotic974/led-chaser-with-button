#pragma once

#include <Arduino.h>

struct Led {

    uint8_t pin;
    bool    state;

    Led(const uint8_t output_pin) { pinMode(pin = output_pin, OUTPUT); }

    void light(const bool on) { digitalWrite(pin, state = on); }
    void toggle()             { light(!state); }

};