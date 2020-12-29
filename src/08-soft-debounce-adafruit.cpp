/*
 * -------------------------------------------------------------------------
 * Atelier de programmation Robotic 974
 * © 2020 Stéphane Calderoni
 * -------------------------------------------------------------------------
 * Introduction à la programmation des cartes Arduino
 * Contrôle d'un chenillard à 8 LEDs par un bouton poussoir
 * -------------------------------------------------------------------------
 * Enrichissement de l'algorithme de debouncing d'Adafruit
 * définissant 4 états distincts pour caractériser le bouton :
 *   - isPressed()
 *   - isReleased()
 *   - isHeld()
 *   - wasHeldFor(const uint16_t ms)
 * -------------------------------------------------------------------------
 */

#include <Arduino.h>
#include "Led.h"
#include "AdafruitButton.h"

Led led1(5), led2(6), led3(7), led4(8);
AdafruitButton button(2);

void setup() {}

void loop() {

    button.read();

    if (button.isPressed())  led1.toggle();
    if (button.isReleased()) led2.toggle();
    led3.light(button.isHeld());
    led4.light(button.wasHeldFor(1000));

}