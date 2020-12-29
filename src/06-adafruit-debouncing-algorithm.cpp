/*
 * -------------------------------------------------------------------------
 * Atelier de programmation Robotic 974
 * © 2020 Stéphane Calderoni
 * -------------------------------------------------------------------------
 * Introduction à la programmation des cartes Arduino
 * Contrôle d'un chenillard à 8 LEDs par un bouton poussoir
 * -------------------------------------------------------------------------
 * Exemple d'utilisation de l'algorithme de debouncing d'Adafruit
 * 
 * --> https://learn.adafruit.com/make-it-switch/debouncing
 * 
 * Le principe consiste à attendre que le signal d'entrée se stabilise
 * au-delà d'une fenêtre temporelle prédéfinie.
 * -------------------------------------------------------------------------
 */

#include <Arduino.h>

/**
 * @brief Broche de commande de la LED.
 */
const uint8_t LED_PIN = 5;

/**
 * @brief Broche de lecture du signal d'entrée du bouton.
 */
const uint8_t BTN_PIN = 2;

/**
 * @brief Fenêtre temporelle de stabilisation du signal (exprimée en millisecondes).
 * 
 * @note Le signal d'entrée doit rester stable sur toute l'étendue de la fenêtre
 *       avant qu'on ne puisse en déduire le signal de sortie.
 * 
 *       Si vous observez encore des rebonds, il suffit d'étendre la fenêtre avec
 *       des valeurs supérieures.
 */
const uint8_t DEBOUNCE_DELAY_MS = 1;

/**
 * @brief État logique de la LED.
 */
bool led_state;

/**
 * @brief Niveau logique du signal de sortie (0 ou 1) du bouton.
 */
uint8_t output;

/**
 * @brief Dernière valeur logique connue du signal d'entrée du bouton.
 */
uint8_t last_input;

/**
 * @brief Origine temporelle absolue de la fenêtre de stabilisation (exprimée en millisecondes).
 */
uint32_t last_debounce_ms;

/**
 * @brief Démarrage du programme.
 */
void setup() {

    // Configuration de la broche de commande de la LED.
    pinMode(LED_PIN, OUTPUT);
    
    // Configuration de la broche de lecture du bouton.
    pinMode(BTN_PIN, INPUT);
  
}

/**
 * @brief Boucle de contrôle principale.
 */
void loop() {

    // Lecture du signal logique d'entrée sur le bouton.
    uint8_t input = digitalRead(BTN_PIN);

    // Si ce signal diffère de celui qui a été lu à la précédente itération,
    // c'est que le signal d'entrée du bouton n'est pas encore stabilisé.
    // Il faut donc décaler l'origine temporelle de la fenêtre de stabilisation
    // pour la poursuivre plus avant et obtenir un signal stabilisé.
    if (input != last_input) last_debounce_ms = millis();

    // On mémorise la dernière valeur du signal d'entrée pour la prochaine itération.
    last_input = input;

    // Si on est sorti de la fenêtre de stabilisation, c'est que le signal est enfin stabilisé.
    if (millis() - last_debounce_ms > DEBOUNCE_DELAY_MS) {

        // Le signal de sortie peut donc être déduit du signal d'entrée (output = input),
        // mais on s'intéresse ici qu'aux cas où l'on observe une bascule du signal de sortie...
        if (output != input) {

            output = input;

            // ... de manière à ne détecter qu'une seule fois (uniquement la première fois)
            // que le bouton a été enfoncé (output = 1), pour changer l'état de la LED.
            if (output) {
                // Si on ne prenait pas cette précaution en amont, la LED clignoterait sans arrêt ici.
                digitalWrite(LED_PIN, led_state = !led_state);
            }

        }

    }

}