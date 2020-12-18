/*
 * -------------------------------------------------------------------------
 * Atelier de programmation Robotic 974
 * © 2020 Stéphane Calderoni
 * -------------------------------------------------------------------------
 * Introduction à la programmation des cartes Arduino
 * Contrôle d'un chenillard à 8 LEDs par un bouton poussoir
 * -------------------------------------------------------------------------
 * Mise en évidence de l'effet rebond avec le compteur binaire
 * -------------------------------------------------------------------------
 */

#include <Arduino.h>

/**
 * @brief Nombre de LEDs.
 */
const uint8_t NUM_LEDS = 8;

/**
 * @brief Broches de commande des LEDs.
 */
const uint8_t LED_PIN[] = { 5, 6, 7, 8, 9, 10, 11, 12 };

/**
 * @brief Broche de lecture de l'état du bouton.
 */
const uint8_t BTN_PIN = 2;

/**
 * @brief Valeur courante du compteur.
 */
uint8_t counter = 0;

/**
 * @brief Dernier état connu du bouton.
 */
uint8_t last_btn_state = 0;

/**
 * @brief Affichage d'un entier sous sa forme binaire sur la rampe de LEDs.
 * 
 * @param n entier compris dans l'intervalle [0,255] (codé sur 8 bits).
 * 
 * @note La valeur de l'entier est ici décomposée en une séquence ordonnée
 *       de bits pour former un octet. Chaque LED permet ainsi d'afficher
 *       la valeur du bit correspondant :
 * 
 *       - si le bit d'indice i vaut 0, alors la LED d'indice i est éteinte
 *       - si le bit d'indice i vaut 1, alors la LED d'indice i est allumée
 */
void ledWrite(const uint8_t n) {

    for (uint8_t i=0; i<NUM_LEDS; i++) {
        digitalWrite(LED_PIN[i], (n >> i) & 0x1);
    }

}

/**
 * @brief Démarrage du programme.
 */
void setup() {

    // Configuration des broches de commande des LEDs.
    for (uint8_t i=0; i<NUM_LEDS; i++) {
        pinMode(LED_PIN[i], OUTPUT);
    }

    // Configuration de la broche de lecture du bouton.
    pinMode(BTN_PIN, INPUT);
    
}

/**
 * @brief Boucle de contrôle principale.
 * 
 * @note L'idée consiste ici à reproduire l'expérience de l'exercice
 *       précédent, mais à ne comptabiliser que les passages de `LOW`
 *       à `HIGH`. Autrement dit, on ne s'intéresse ici qu'aux moments
 *       où on enfonce le bouton.
 * 
 *       Vous verrez que malgré tout, les effets rebonds peuvent encore
 *       se manifester... même si on en comptabilise moins que précédemment.
 */
void loop() {

    // Lecture de l'état courant du bouton.
    uint8_t btn_state = digitalRead(BTN_PIN);

    // Si l'état courant est différent du dernier état connu,
    // c'est qu'il y'a eu un changement d'état, qui peut
    // éventuellement correspondre à un rebond indésirable.
    if (btn_state != last_btn_state) {

        // Si l'état qui vient d'être lu est `HIGH`...
        if (btn_state) {
            // Alors on incrémente le compteur et on affiche
            // sa valeur sur la rampe de LEDs.
            ledWrite(++counter);
            // Par conséquent, si vous voyez qu'après avoir appuyé
            // sur le bouton, le compteur affiché a varié de plus
            // d'une unité, c'est qu'on a capturé la manifestation
            // d'un ou plusieurs rebonds.
        }

        // L'état courant est enfin sauvegardé comme
        // le dernier état connu du bouton.
        last_btn_state = btn_state;

    }

}