/*
 * -------------------------------------------------------------------------
 * Atelier de programmation Robotic 974
 * © 2020 Stéphane Calderoni
 * -------------------------------------------------------------------------
 * Introduction à la programmation des cartes Arduino
 * Contrôle d'un chenillard à 8 LEDs par un bouton poussoir
 * -------------------------------------------------------------------------
 * Bouton enfoncé : la LED s'allume | Bouton relâché : la LED s'éteint
 * -------------------------------------------------------------------------
 */

#include <Arduino.h>

/**
 * @brief Définition de la broche de commande de la LED.
 */
const uint8_t LED_PIN = 5;

/**
 * @brief Définition de la broche de lecture de l'état du bouton.
 */
const uint8_t BTN_PIN = 2;

/**
 * @brief Démarrage du programme.
 */
void setup() {

    // Initialisation des broches de la carte Arduino.
    pinMode(LED_PIN, OUTPUT);
    pinMode(BTN_PIN, INPUT);
    
}

/**
 * @brief Boucle de contrôle principale.
 */
void loop() {

    // Lecture de l'état logique du bouton :
    //   uint8_t btn_state = digitalRead(BTN_PIN);
    // 
    // `btn_state` prend donc la valeur `HIGH` ou `LOW`.
    // 
    // Il ne reste plus qu'à répercuter cet état sur la LED :
    //   digitalWrite(LED_PIN, btn_state);
    // 
    // Ce qui, en définitive, se simplifie par :

    digitalWrite(LED_PIN, digitalRead(BTN_PIN));

}