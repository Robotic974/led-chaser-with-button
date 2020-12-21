/*
 * -------------------------------------------------------------------------
 * Atelier de programmation Robotic 974
 * © 2020 Stéphane Calderoni
 * -------------------------------------------------------------------------
 * Introduction à la programmation des cartes Arduino
 * Contrôle d'un chenillard à 8 LEDs par un bouton poussoir
 * -------------------------------------------------------------------------
 * Mise en évidence de l'effet rebond par un décompte différencié des
 * transitions logiques observées sur la broche de lecture du bouton
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
 * Fenêtre de comptage exprimée en millisecondes.
 */
const uint16_t COUNT_DELAY_MS = 200;

/**
 * @brief Nombre de passages à l'état `HIGH`
 */
uint8_t up = 0;

/**
 * @brief Nombre de passages à l'état `LOW`
 */
uint8_t down = 0;

/**
 * @brief Dernier état connu du bouton.
 */
uint8_t last_btn_state = 0;

/**
 * @brief Date du dernier décompte enregistré.
 */
uint32_t last_count_ms = 0;

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
 * @brief Affichage du décompte des transitions logiques enregistrées.
 * 
 * @note Si au cours de la fenêtre de comptage, on a dénombré :
 *         + 3 passages de `LOW` à `HIGH` (up)
 *         + 2 passages de `HIGH` à `LOW` (down)
 * 
 *       Alors la rampe de LEDs affichera :
 * 
 *           up
 *        +-----+
 *         ● ● ● ○ ○ ○ ● ●
 *                    +---+
 *                     down
 */
void showCount() {

    // Activation des bits "allumés" à gauche.
    uint8_t n = 255 - ((1 << (8 - up)) - 1);

    // Activation des bits "allumés" à droite.
    n |= (1 << down) - 1;

    // Affichage du nombre binaire obtenu par composition.
    ledWrite(n);

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
 * @note L'idée consiste ici à dénombrer les changement d'états logiques
 *       lus sur la broche du bouton poussoir. On décompte séparément :
 *         - les passages de `LOW` à `HIGH (avec le compteur `up`)
 *         - les passages de `HIGH` à `LOW (avec le compteur `down`)
 */
void loop() {

    // Lecture de l'état courant du bouton.
    uint8_t btn_state = digitalRead(BTN_PIN);

    // Si l'état courant est différent du dernier état connu,
    // c'est qu'il y'a eu un changement d'état, qui peut
    // éventuellement correspondre à un rebond indésirable.
    if (btn_state != last_btn_state) {

        // Décompte des transitions logiques.
        up   +=  btn_state;
        down += !btn_state;

        // L'état courant est enfin sauvegardé comme
        // le dernier état connu du bouton.
        last_btn_state = btn_state;

    }

    // Si une quelconque transition logique a été enregistrée
    // depuis le début de la fenêtre de comptage...
    if (up | down) {

        uint32_t now = millis();

        // Et qu'on est sorti de la fenêtre de comptage...
        if (now - last_count_ms > COUNT_DELAY_MS) {

            // Alors on affiche le décompte global.
            showCount();

            // On réinitialise les compteurs.
            up   = 0;
            down = 0;

            // Puis on enregistre la date du dernier décompte.
            last_count_ms = now;

        }

    } else {
        
        // Si aucune transition logique n'a été enregistrée,
        // alors on réinitialise l'origine temporelle de la
        // fenêtre de comptage.
        last_count_ms = millis();

    }

}