#pragma once

#include "Button.h"

struct KuhnButton : Button {
    
    const uint8_t DEBOUNCING_THRESHOLD = 4;

    uint8_t integrator;

    using Button::Button;

    void read() {

        input = digitalRead(pin);

             if (!input) { if (integrator) integrator--; }
        else if (integrator < DEBOUNCING_THRESHOLD) integrator++;

             if (!integrator) output = 0;
        else if (integrator == DEBOUNCING_THRESHOLD) output = 1;

        update();

    }

};