/*
 * -------------------------------------------------------------------------
 * Atelier de programmation Robotic 974
 * © 2020 Stéphane Calderoni
 * -------------------------------------------------------------------------
 * Introduction à la programmation des cartes Arduino
 * Contrôle d'un chenillard à 8 LEDs par un bouton poussoir
 * -------------------------------------------------------------------------
 * Définition d'un modèle orienté objet pour la commande des LEDs
 * -------------------------------------------------------------------------
 */

/**
 * @note Spécifie que le compilateur n’intègre le fichier d’en-tête
 *       qu’une seule fois lors de la compilation d'un fichier source.
 */
#pragma once

#include <Arduino.h>

/**
 * @brief Définition du modèle d'implémentation d'une LED.
 */
struct Led {

    /**
     * @brief Broche de commande de la LED.
     */
    uint8_t pin;

    /**
     * @brief État logique de la LED.
     * 
     * @note true: allumée | false: éteinte
     */
    bool state;

    /**
     * @brief Définition du constructeur.
     * 
     * @param output_pin Broche de commande la LED.
     */
    Led(const uint8_t output_pin) {

        pinMode(pin = output_pin, OUTPUT);

    }

    /**
     * @brief Fixe un nouvel état de la LED.
     * 
     * @param on Nouvel état de la LED (true: allumée | false: éteinte).
     */
    void light(const bool on) {

        digitalWrite(pin, state = on);

    }

    /**
     * @brief Inverse l'état de la LED.
     * 
     * @note Éteint la LED si elle était allumée (true).
     *       Allume la LED si elle était éteinte (false).
     */
    void toggle() {

        light(!state);

    }

};