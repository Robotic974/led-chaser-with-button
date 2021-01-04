/*
 * ---------------------------------------------------------------------------
 * Atelier de programmation Robotic 974
 * © 2020 Stéphane Calderoni
 * ---------------------------------------------------------------------------
 * Introduction à la programmation des cartes Arduino
 * Contrôle d'un chenillard à 8 LEDs par un bouton poussoir
 * ---------------------------------------------------------------------------
 * Commande de 4 LEDs par un bouton à l'aide de l'algorithme de Kennet A. Kuhn
 * ---------------------------------------------------------------------------
 */

#include <Arduino.h>
#include <Led.h>
#include <KuhnButton.h>

/**
 * @brief Définition des LEDs.
 * 
 * @note On instancie 4 LEDs à partir du modèle défini par la classe Led.
 *       Chaque LED est respectivement associée aux broches de commandes
 *       D5, D6, D7 et D8 de la carte Arduino.
 */
Led led1(5), led2(6), led3(7), led4(8);

/**
 * @brief Définition du bouton.
 * 
 * @note On instancie un bouton à partir du modèle défini par la classe KuhnButton
 *       qui met en oeuvre l'algorithme de debouncing de Kenneth A. Kuhn.
 *       Le bouton est associé à la broche de lecture D2 de la carte Arduino.
 */
KuhnButton button(2);

/**
 * @brief Démarrage du programme principal.
 * 
 * @note Il n'y'a rien de spécial à effectuer ici...
 */
void setup() {}

/**
 * @brief Boucle de contrôle principale.
 */
void loop() {

    // Lecture de l'état du bouton.
    button.read();

    // La LED n°1 change d'état dès que le bouton est enfoncé.
    if (button.isPressed())  led1.toggle();

    // La LED n°2 change d'état dès que le bouton est relâché.
    if (button.isReleased()) led2.toggle();

    // La LED n°3 s'allume si le bouton est maintenu enfoncé, et s'éteint sinon.
    led3.light(button.isHeld());

    // La LED n°4 s'allume si le bouton est maintenu enfoncé pendant au moins 1 seconde, et s'éteint sinon.
    led4.light(button.wasHeldFor(1000));

}