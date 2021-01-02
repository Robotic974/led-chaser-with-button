/*
 * -------------------------------------------------------------------------
 * Atelier de programmation Robotic 974
 * © 2020 Stéphane Calderoni
 * -------------------------------------------------------------------------
 * Introduction à la programmation des cartes Arduino
 * Contrôle d'un chenillard à 8 LEDs par un bouton poussoir
 * -------------------------------------------------------------------------
 * Balayage bidirectionnel du chenillard à LEDs contrôlé par un bouton.
 * -------------------------------------------------------------------------
 */

#include <Arduino.h>
#include "Led.h"
#include "AdafruitButton.h"

/**
 * @brief Nombre de LEDs.
 */
const uint8_t NUM_LEDS = 8;

/**
 * @brief Instanciation de la rampe de LEDs.
 * 
 * @note Chaque LED est implémentée par un objet construit à partir d'un
 *       modèle unique décrit par la structure `Led`.
 * 
 *       Les LEDs sont respectivement reliées aux broches de commande
 *       D5, D6, D7, D8, D9, D10, D11 et D12.
 */
Led led[] = { Led(5), Led(6), Led(7), Led(8), Led(9), Led(10), Led(11), Led(12) };

/**
 * @brief Instanciation du bouton poussoir.
 * 
 * @note Le bouton est implémenté par un objet construit à partir de l'un
 *       des modèles suivants, au choix :
 * 
 *           - soit avec le modèle KuhnButton,
 *           - soit avec le modèle AdafruitButton.
 * 
 *       Le bouton est relié à la broche de lecture D2 de la carte Arduino.
 */
AdafruitButton button(2);

/**
 * @brief Indice de la LED active sur le chenillard.
 */
uint8_t index = 0;

/**
 * @brief Sens de progression du balayage.
 * 
 * @note Effectuer un balayage bidirectionnel du chenillard revient à allumer puis éteindre
 *       chaque LED, tour à tour, en effectuant des allers-retours sur toute la longeur
 *       du chenillard, donc en suivant une progression par décalage d'une LED à la fois,
 *       dans un sens puis dans l'autre.
 *
 *       +1 indique une progression dans le sens croissant des indices du tableau `led`.
 *       -1 indique une progression dans le sens décroissant.
 */
int8_t direction = 1;

/**
 * @brief Démarrage du programme principal.
 */
void setup() {

    // On allume la première LED du chenillard (`index` est initialisé à 0).
    led[index].light(true);

}

/**
 * @brief Boucle de contrôle principale.
 */
void loop() {

    // Lecture de l'état du bouton.
    button.read();

    // À chaque fois qu'on vient d'enfoncer le bouton...
    if (button.isPressed()) {

        // On vérifie les cas où l'on a atteint les extrémités du chenillard,
        // auquel cas il faut inverser la direction du balayage.
        if ((!index && direction < 0) || (index + 1 == NUM_LEDS && direction > 0)) direction *= -1;

        // On éteint la LED active.
        led[index].light(false);

        // Puis on détermine l'indice de la prochaine LED à activer en fonction de la
        // direction du balayage, et on l'allume.
        led[index += direction].light(true);

    }

}