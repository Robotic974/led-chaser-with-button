/*
 * -------------------------------------------------------------------------
 * Atelier de programmation Robotic 974
 * © 2020 Stéphane Calderoni
 * -------------------------------------------------------------------------
 * Introduction à la programmation des cartes Arduino
 * Contrôle d'un chenillard à 8 LEDs par un bouton poussoir
 * -------------------------------------------------------------------------
 * Définition d'un modèle orienté objet pour la lecture du bouton.
 * Ce modèle implémente l'algorithme de debouncing d'Adafruit.
 * -------------------------------------------------------------------------
 */

/**
 * @note Spécifie que le compilateur n’intègre le fichier d’en-tête
 *       qu’une seule fois lors de la compilation d'un fichier source.
 */
#pragma once

#include <Arduino.h>
#include "Button.h"

/**
 * @brief Définition du modèle d'implémentation d'un bouton.
 * 
 * @note Ce modèle "hérite" du modèle `Button` (et par conséquent, de toutes
 *       ses propriétés). Il permet de concrétiser le modèle abstrait parent
 *       en définissant une implémentation de la méthode read().
 */
struct AdafruitButton : Button {

    /**
     * @brief Fenêtre temporelle de stabilisation du signal (exprimée en millisecondes).
     * 
     * @note Le signal d'entrée doit rester stable sur toute l'étendue de la fenêtre
     *       avant qu'on ne puisse en déduire le signal de sortie.
     * 
     *       Si vous observez encore des rebonds, il suffit d'étendre la fenêtre avec
     *       des valeurs supérieures.
     * 
     *       Cette constante est déclarée `static` pour être partagée par toutes
     *       les instances au lieu d'être dupliquée dans chaque instance.
     */
    static const uint8_t DEBOUNCE_DELAY_MS = 1;

    /**
     * @brief Dernière valeur logique connue du signal d'entrée du bouton.
     */
    uint8_t last_input;

    /**
     * @brief Origine temporelle absolue de la fenêtre de stabilisation (exprimée en millisecondes).
     */
    uint32_t last_debounce_ms;

    /**
     * @brief Propage le constructeur défini par le modèle parent.
     */
    using Button::Button;

    /**
     * @brief Lecture du signal logique d'entrée du bouton.
     * 
     * @note La méthode abstraite read() déclarée dans le modèle parent
     *       est ici concrétisée par sa définition.
     * 
     *       Elle est le siège de l'algorithme de debouncing d'Adafruit,
     *       qui permet de déterminer le niveau logique du signal de sortie
     *       à partir de la lecture du niveau logique du signal d'entrée.
     */
    void read() {

        input = digitalRead(pin);

             if (input != last_input) last_debounce_ms = millis();
        else if (millis() - last_debounce_ms > DEBOUNCE_DELAY_MS) output = input;

        // On mémorise la dernière valeur du signal d'entrée pour la prochaine lecture.
        last_input = input;

        // La méthode update() du modèle parent est enfin appelée pour
        // déterminer l'état effectif du bouton en fonction du niveau
        // logique de sortie.
        update();

    }

};