/*
 * -------------------------------------------------------------------------
 * Atelier de programmation Robotic 974
 * © 2020 Stéphane Calderoni
 * -------------------------------------------------------------------------
 * Introduction à la programmation des cartes Arduino
 * Contrôle d'un chenillard à 8 LEDs par un bouton poussoir
 * -------------------------------------------------------------------------
 * Définition d'un modèle orienté objet générique pour la lecture du bouton.
 * -------------------------------------------------------------------------
 */

/**
 * @note Spécifie que le compilateur n’intègre le fichier d’en-tête
 *       qu’une seule fois lors de la compilation d'un fichier source.
 */
#pragma once

#include <Arduino.h>

/**
 * @brief Définition du modèle d'implémentation d'un bouton.
 * 
 * @note Ce modèle est défini comme "abstrait" par la déclaration suivante :
 * 
 *           virtual void read() = 0;
 * 
 *       Elle déclare en effet une méthode read() qui ne sera définie que par
 *       les modèles descendants, et qui auront obligation de la définir pour
 *       pouvoir engendrer des objets.
 * 
 *       De ce fait, le modèle décrit ici est considéré comme abstrait et
 *       ne pourra en aucun cas être instancié directement. Seuls les modèles
 *       descendants qui concrétiseront la méthode read() pourront être instanciés
 *       et engendrer un objet à leur image.
 */
struct Button {

    /**
     * @brief Broche de lecture du bouton.
     */
    uint8_t pin;

    /**
     * @brief Niveau logique du signal d'entrée (0 ou 1) du bouton.
     */
    uint8_t input;

    /**
     * @brief Niveau logique du signal de sortie (0 ou 1) du bouton.
     * 
     * @note Le signal de sortie sera déduit du signal d'entrée par un
     *       algorithme spécifique qui sera décrit par l'implémentation
     *       de la méthode abstraite read() dans les modèles descendants.
     */
    uint8_t output;

    /**
     * @brief État du bouton.
     * 
     * @note Les valeurs que peut prendre la variable `state` sont restreintes
     *       à un ensemble de valeurs prédéfinies qui est décrit par une énumération.
     * 
     *       Cette énumération définit les états possibles du bouton par un
     *       ensemble de constantes de type uint8_t de la façon suivante :
     * 
     *           free     = 0
     *           pressed  = 1
     *           held     = 2
     *           released = 3
     */
    enum State : uint8_t { free, pressed, held, released } state;

    /**
     * @brief Origine temporelle de l'état "held" (exprimée en millisecondes).
     */
    uint32_t held_start_ms;

    /**
     * @brief Définition du constructeur.
     * 
     * @param input_pin Broche de lecture du bouton.
     */
    Button(const uint8_t input_pin) {

        pinMode(pin = input_pin, INPUT);

    }

    /**
     * @brief Lecture du signal logique d'entrée du bouton.
     * 
     * @note Cette méthode est déclarée comme abstraite et devra être définie
     *       par les modèles descendants.
     * 
     *       L'implémentation qui sera faite par les descendants devra préciser
     *       de quelle manière le niveau logique du signal de sortie est déduit
     *       du niveau logique du signal d'entrée.
     */
    virtual void read() = 0;

    /**
     * @brief Mise à jour de l'état du bouton.
     * 
     * @note Dès lors que le niveau logique du signal de sortie est déterminé,
     *       on peut en déduire l'état exposé par le bouton au travers des
     *       méthodes suivantes (qui seront définies par la suite) :
     * 
     *           isPressed()
     *           isReleased()
     *           isHeld()
     *           wasHeldFor(const uint16_t ms)
     */
    void update() {
        
        switch (state) {

            case State::free:
                if (output) state = State::pressed;
                break;

            case State::pressed:
                if (output) {
                    state = State::held;
                    held_start_ms = millis();
                } else state = State::released;
                break;

            case State::held:
                if (!output) state = State::released;
                break;

            case State::released:
                state = State::free;
                break;

        }
        
    }

    /**
     * @brief Détermine si le bouton vient d'être enfoncé.
     * 
     * @return `true`  si le bouton vient d'être enfoncé.
     *         `false` sinon.
     * 
     * @note Cet état est fugace et correspond au moment précis où
     *       `output` passe du niveau logique `LOW` à `HIGH`.
     */
    bool isPressed() {

        return state == State::pressed;

    }

    /**
     * @brief Détermine si le bouton vient d'être relâché.
     * 
     * @return `true`  si le bouton vient d'être relâché.
     *         `false` sinon.
     * 
     * @note Cet état est fugace et correspond au moment précis où
     *       `output` passe du niveau logique `HIGH` à `LOW`.
     */
    bool isReleased() {

        return state == State::released;

    }

    /**
     * @brief Détermine si le bouton est maintenu enfoncé.
     * 
     * @return `true`  si le bouton est maintenu enfoncé.
     *         `false` sinon.
     * 
     * @note Cet état est prolongé tant que le bouton n'est pas relâché.
     */
    bool isHeld() {

        return state == State::held;

    }
    
    /**
     * @brief Détermine si le bouton est maintenu enfoncé durant une période suffisante.
     * 
     * @param duration_ms Durée minimale (exprimée en millisecondes) pendant laquelle
     *                    le bouton doit être maintenu enfoncé.
     * 
     * @return `true`  si le bouton a été maintenu enfoncé pendant au moins `duration_ms` millisecondes.
     *         `false` sinon.
     */
    bool wasHeldFor(const uint16_t duration_ms) {

        return isHeld() && (millis() - held_start_ms >= duration_ms);

    }

};