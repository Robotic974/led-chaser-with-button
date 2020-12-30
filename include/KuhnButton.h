/*
 * -------------------------------------------------------------------------
 * Atelier de programmation Robotic 974
 * © 2020 Stéphane Calderoni
 * -------------------------------------------------------------------------
 * Introduction à la programmation des cartes Arduino
 * Contrôle d'un chenillard à 8 LEDs par un bouton poussoir
 * -------------------------------------------------------------------------
 * Définition d'un modèle orienté objet pour la lecture du bouton.
 * Ce modèle implémente l'algorithme de debouncing de Kenneth A. Kuhn.
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
struct KuhnButton : Button {
    
    /**
     * @brief Seuil maximal de l'intégrateur de l'algorithme.
     * 
     * @note Cette constante est déclarée `static` pour être partagée par toutes
     *       les instances au lieu d'être dupliquée dans chaque instance.
     */
    static const uint8_t DEBOUNCING_THRESHOLD = 4;

    /**
     * @brief Valeur instantanée de l'intégrateur.
     * 
     * @note L'intégrateur permet de cumuler les valeurs lues du niveau logique
     *       du signal d'entrée du bouton.
     * 
     *       Il est utilisé pour effectuer une hystérésis temporelle de sorte que
     *       le signal d'entrée doit être maintenu dans un état logique (0 ou 1)
     *       constant pour que la sortie passe à cet état.
     */
    uint8_t integrator;

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
     *       Elle est le siège de l'algorithme de debouncing de K. A. Kuhn,
     *       qui permet de déterminer le niveau logique du signal de sortie
     *       à partir de la lecture du niveau logique du signal d'entrée.
     */
    void read() {

        input = digitalRead(pin);

             if (!input) { if (integrator) integrator--; }
        else if (integrator < DEBOUNCING_THRESHOLD) integrator++;

             if (!integrator) output = 0;
        else if (integrator == DEBOUNCING_THRESHOLD) output = 1;

        // La méthode update() du modèle parent est enfin appelée pour
        // déterminer l'état effectif du bouton en fonction du niveau
        // logique de sortie.
        update();

    }

};