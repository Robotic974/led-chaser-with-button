/*
 * -------------------------------------------------------------------------
 * Atelier de programmation Robotic 974
 * © 2020 Stéphane Calderoni
 * -------------------------------------------------------------------------
 * Introduction à la programmation des cartes Arduino
 * Contrôle d'un chenillard à 8 LEDs par un bouton poussoir
 * -------------------------------------------------------------------------
 * Définition d'un modèle orienté objet pour la lecture d'un bouton selon
 * l'algorithme de debouncing de Kennet A. Kuhn :
 * --> https://www.kennethkuhn.com/electronics/debounce.c
 * -------------------------------------------------------------------------
 * Fichier d'en-tête (header) de définition de la classe KuhnButton
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
 * @brief Définition de la classe KuhnButton.
 * 
 * @note Cette classe définit un modèle "concret" dérivé du modèle abstrait
 *       défini par la classe Button.
 * 
 *       Elle concrétise le modèle abstrait en définissant une implémentation
 *       de la méthode _debounce() selon l'algorithme de Kennet A. Kuhn.
 * 
 *       Par conséquent, elle complète le modèle abstrait et devient par là-même
 *       un modèle concret qui pourra être instancié en tant que tel et engendrer
 *       des objets construits à son image. Ce modèle hérite de tout ce qui a été
 *       défini dans le modèle abstrait Button.
 */
class KuhnButton : public Button {

    private:

        /**
         * @brief Seuil maximal de l'intégrateur de l'algorithme.
         * 
         * @note Dès que l'intégrateur atteint ce seuil, le signal d'entrée est
         *       considéré comme stable et le niveau logique du signal de sortie
         *       peut alors passer à l'état `HIGH`.
         * 
         *       Si vous observez encore des rebonds, il suffit d'augmenter la
         *       valeur du seuil.
         * 
         *       Cette constante est déclarée `static` pour être partagée par toutes
         *       les instances de la classe au lieu d'être dupliquée dans chaque
         *       instance (entraînant une occupation inutile de la mémoire).
         */
        static const uint8_t _DEBOUNCING_THRESHOLD = 16;

        /**
         * @brief Valeur instantanée de l'intégrateur de l'algorithme.
         * 
         * @note L'intégrateur permet de cumuler les observations du niveau logique
         *       du signal d'entrée :
         * 
         *           +1 quand le signal est à `HIGH` (1)
         *           -1 quand le signal est à `LOW`  (0)
         * 
         *       Il est utilisé pour effectuer une hystérésis temporelle de sorte que
         *       le signal d'entrée doit être maintenu dans un état logique (0 ou 1)
         *       constant pour que la sortie passe à cet état par effet de seuil.
         */
        uint8_t _integrator;

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
         *       de Kennet A. Kuhn.
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