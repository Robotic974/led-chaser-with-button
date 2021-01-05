/*
 * -------------------------------------------------------------------------
 * Atelier de programmation Robotic 974
 * © 2020 Stéphane Calderoni
 * -------------------------------------------------------------------------
 * Introduction à la programmation des cartes Arduino
 * Contrôle d'un chenillard à 8 LEDs par un bouton poussoir
 * -------------------------------------------------------------------------
 * Définition d'un modèle orienté objet pour la lecture d'un bouton selon
 * l'algorithme de debouncing d'Adafruit
 * --> https://learn.adafruit.com/make-it-switch/debouncing
 * -------------------------------------------------------------------------
 * Fichier d'en-tête (header) de définition de la classe AdafruitButton
 * -------------------------------------------------------------------------
 */

/**
 * @note Spécifie que le compilateur n’intègre le fichier d’en-tête
 *       qu’une seule fois lors de la compilation des fichiers sources.
 */
#pragma once

#include "Button.h"
#include <Arduino.h>

/**
 * @brief Définition de la classe AdafruitButton.
 * 
 * @note Cette classe définit un modèle "concret" dérivé du modèle abstrait
 *       défini par la classe Button.
 * 
 *       Elle concrétise le modèle abstrait en définissant une implémentation
 *       de la méthode _debounce() selon l'algorithme d'Adafruit.
 * 
 *       Par conséquent, elle complète le modèle abstrait et devient par là-même
 *       un modèle concret qui pourra être instancié en tant que tel et engendrer
 *       des objets construits à son image. Ce modèle hérite de tout ce qui a été
 *       défini dans le modèle abstrait Button.
 */
class AdafruitButton : public Button {

    private:

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
         *       les instances au lieu d'être dupliquée dans chaque instance (et entraîner
         *       une perte inutile de mémoire).
         */
        static const uint8_t _DEBOUNCE_DELAY_MS = 1;

        /**
         * @brief Dernière valeur logique enregistrée du signal d'entrée du bouton.
         * 
         * @note L'algorithme d'Adafruit fonctionne par comparaison des valeurs successives
         *       du signal d'entrée provenant du bouton. Pour effectuer cette comparaison
         *       à partir du signal lu à l'itération (n), il faut avoir mémorisé la valeur
         *       qu'il avait à l'itération (n-1).
         */
        uint8_t _last_input;

        /**
         * @brief Origine temporelle absolue de la fenêtre de stabilisation (exprimée en millisecondes).
         * 
         * @note L'algorithme d'Adafruit cherche à observer une stabilisation du signal
         *       d'entrée sur une période prédéterminée, définie par la durée constante
         *       `_DEBOUNCE_DELAY_MS`. Par conséquent, pour pouvoir mesurer la durée
         *       écoulée depuis la dernière mesure stabilisée, il faut avoir mémorisé à
         *       quel moment cette lecture a été faite.
         */
        uint32_t _last_debounce_ms;

    protected:

        /**
         * @brief Déparasitage du signal électronique provenant du bouton.
         * 
         * @param input Niveau logique du signal d'entrée brut (lu directement).
         * 
         * @note Le signal d'entrée parasité par des effets rebonds potentiels
         *       sera directement lu par la fonction digitalRead() sur la broche
         *       de lecture du bouton. La méthode _debounce() se chargera donc
         *       d'éliminer ces parasites à l'aide de l'algorithme de debouncing
         *       d'Adafruit.
         * 
         *       Le mot clef "override" précise ici qu'il s'agit d'une redéfinition
         *       de la méthode _debounce() déclarée par le modèle parent Button.
         */
        void _debounce(const uint8_t input) override;

    public:

        /**
         * @brief Propage le constructeur défini par le modèle parent Button.
         */
        using Button::Button;

};