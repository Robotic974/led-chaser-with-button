/*
 * -------------------------------------------------------------------------
 * Atelier de programmation Robotic 974
 * © 2020 Stéphane Calderoni
 * -------------------------------------------------------------------------
 * Introduction à la programmation des cartes Arduino
 * Contrôle d'un chenillard à 8 LEDs par un bouton poussoir
 * -------------------------------------------------------------------------
 * Fichier de définition (implémentation) des méthodes de la classe Button
 * -------------------------------------------------------------------------
 */

/**
 * @note Incorpore le fichier d'en-tête qui déclare les attributs et les
 *       méthodes de la classe Button avant de les définir.
 */
#include "Button.h"

Button::Button(const uint8_t pin) {
    pinMode(_pin = pin, INPUT);
}

void Button::_update() {

    switch (_state) {
        case _State::free:
            if (_output) _state = _State::pressed;
            break;
        case _State::pressed:
            if (_output) {
                _state = _State::held;
                _held_start_ms = millis();
            } else _state = _State::released;
            break;
        case _State::held:
            if (!_output) _state = _State::released;
            break;
        case _State::released:
            _state = _State::free;
            break;
    }

}

void Button::read() {
    _debounce(digitalRead(_pin));
    _update();
}

bool Button::isPressed() {
    return _state == _State::pressed;
}

bool Button::isReleased() {
    return _state == _State::released;
}

bool Button::isHeld() {
    return _state == _State::held;
}

bool Button::wasHeldFor(const uint16_t delay_ms) {
    return isHeld() && (millis() - _held_start_ms >= delay_ms);
}