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
 * Fichier d'en-tête (header) de définition de la classe LED
 * -------------------------------------------------------------------------
 */

/**
 * @note Spécifie que le compilateur n’intègre le fichier d’en-tête
 *       qu’une seule fois lors de la compilation des fichiers sources.
 */
#pragma once

#include <Arduino.h>

/**
 * @brief Définition de la classe LED.
 * 
 * @note Cette classe définit un modèle générique qui va nous permettre
 *       de commander chacune des LEDs du chenillard.
 */
class Led {

    private:

        /**
         * @brief Broche de commande de la LED.
         */
        uint8_t _pin;

        /**
         * @brief État logique de la LED.
         * 
         * @note false: éteinte.
         *       true:  allumée.
         */
        bool _state;
    
    public:

        /**
         * @brief Déclaration du constructeur.
         * 
         * @param pin Broche de commande de la LED.
         * 
         * @note Le constructeur attend un argument qui permet de préciser
         *       quelle sera la broche de commande de la LED.
         */
        Led(const uint8_t pin);

        /**
         * @brief Allume ou éteint la LED.
         * 
         * @param state Nouvel état logique à appliquer sur la LED.
         * 
         * @note Cette méthode attend un argument qui permet de préciser
         *       quel état on veut appliquer sur la LED.
         * 
         *       false: éteint la LED.
         *       true:  allume la LED.
         */
        void light(const bool state);

        /**
         * @brief Inverse l'état de la LED.
         * 
         * @note Éteint la LED si elle était allumée.
         *       Allume la LED si elle était éteinte.
         */
        void toggle();

};