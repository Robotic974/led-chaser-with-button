/*
 * -------------------------------------------------------------------------------
 * Atelier de programmation Robotic 974
 * © 2020 Stéphane Calderoni
 * -------------------------------------------------------------------------------
 * Introduction à la programmation des cartes Arduino
 * Contrôle d'un chenillard à 8 LEDs par un bouton poussoir
 * -------------------------------------------------------------------------------
 * Fichier de définition (implémentation) des méthodes de la classe AdafruitButton
 * -------------------------------------------------------------------------------
 */

/**
 * @note Incorpore le fichier d'en-tête qui déclare les attributs et les
 *       méthodes de la classe AdafruitButton avant de les définir.
 */
#include "AdafruitButton.h"

void AdafruitButton::_debounce(const uint8_t input) {

    if (input != _last_input) {

        _last_debounce_ms = millis();

    } else if (millis() - _last_debounce_ms > _DEBOUNCE_DELAY_MS) {
        
        _output = input;
        
    }

    _last_input = input;

}