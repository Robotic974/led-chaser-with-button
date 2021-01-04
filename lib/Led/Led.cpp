/*
 * -------------------------------------------------------------------------
 * Atelier de programmation Robotic 974
 * © 2020 Stéphane Calderoni
 * -------------------------------------------------------------------------
 * Introduction à la programmation des cartes Arduino
 * Contrôle d'un chenillard à 8 LEDs par un bouton poussoir
 * -------------------------------------------------------------------------
 * Fichier de définition (implémentation) des méthodes de la classe LED
 * -------------------------------------------------------------------------
 */

/**
 * @note Incorpore le fichier d'en-tête qui déclare les attributs et les
 *       méthodes de la classe Led avant de les définir.
 */
#include "Led.h"

Led::Led(const uint8_t pin) {
    pinMode(_pin = pin, OUTPUT);
}

void Led::light(const bool state) {
    digitalWrite(_pin, _state = state);
}

void Led::toggle() {
    light(!_state);
}