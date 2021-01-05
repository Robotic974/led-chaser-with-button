/*
 * ---------------------------------------------------------------------------
 * Atelier de programmation Robotic 974
 * © 2020 Stéphane Calderoni
 * ---------------------------------------------------------------------------
 * Introduction à la programmation des cartes Arduino
 * Contrôle d'un chenillard à 8 LEDs par un bouton poussoir
 * ---------------------------------------------------------------------------
 * Fichier de définition (implémentation) des méthodes de la classe KuhnButton
 * ---------------------------------------------------------------------------
 */

/**
 * @note Incorpore le fichier d'en-tête qui déclare les attributs et les
 *       méthodes de la classe KuhnButton avant de les définir.
 */
#include "KuhnButton.h"

void KuhnButton::_debounce(const uint8_t input) {

     if (!input) {

          if (_integrator) {
               
               _integrator--;

          }

     } else if (_integrator < _DEBOUNCING_THRESHOLD) {

          _integrator++;

     }

     if (!_integrator) {
          
          _output = 0;

     } else if (_integrator == _DEBOUNCING_THRESHOLD) {
          
          _output = 1;

     }

}