#pragma once

#include "Button.h"

struct AdafruitButton : Button {

    const uint8_t DEBOUNCE_DELAY_MS = 1;

    uint8_t  last_input;
    uint32_t last_debounce_ms;

    using Button::Button;

    void read() {

        input = digitalRead(pin);

             if (input != last_input) last_debounce_ms = millis();
        else if (millis() - last_debounce_ms > DEBOUNCE_DELAY_MS) output = input;

        last_input = input;

        update();

    }

};