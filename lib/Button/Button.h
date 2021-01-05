/*
 * -------------------------------------------------------------------------
 * Atelier de programmation Robotic 974
 * © 2020 Stéphane Calderoni
 * -------------------------------------------------------------------------
 * Introduction à la programmation des cartes Arduino
 * Contrôle d'un chenillard à 8 LEDs par un bouton poussoir
 * -------------------------------------------------------------------------
 * Définition d'un modèle orienté objet abstrait pour la lecture d'un bouton
 * -------------------------------------------------------------------------
 * Fichier d'en-tête (header) de définition de la classe Button
 * -------------------------------------------------------------------------
 */

/**
 * @note Spécifie que le compilateur n’intègre le fichier d’en-tête
 *       qu’une seule fois lors de la compilation des fichiers sources.
 */
#pragma once

#include <Arduino.h>

/**
 * @brief Définition de la classe abstraite Button.
 * 
 * @note Cette classe définit un modèle générique qui va nous permettre
 *       de lire et interpréter les signaux électroniques provenant d'un
 *       bouton poussoir.
 * 
 *       Ce modèle est défini comme "abstrait", c'est-à-dire qu'on ne
 *       pourra pas l'instancier en tant que tel. En effet, il va servir
 *       à forger un modèle générique de base, commun à tous les boutons
 *       que l'on souhaitera implémenter, avec des méthodes de suppression
 *       des effets rebonds (debouncing) spécifiques.
 * 
 *       En d'autres termes, on ne définira ici aucune méthode concrète de
 *       debouncing. On se contentera de préciser que cette méthode devra
 *       être définie dans toutes les classes dérivées par héritage :
 * 
 *           virtual void _debounce(const uint8_t input) = 0;
 * 
 *       Le mot clef "virtual" précise que la méthode _debounce() pourra
 *       être redéfinie dans les classes dérivées.
 * 
 *       L'affectation "= 0" précise que la méthode _debounce() ne sera
 *       pas définie (implémentée) par la classe Button elle-même mais
 *       DEVRA l'être par ses classes dérivées. C'est ce qui confère
 *       à la classe Button son caractère abstrait.
 */
class Button {

    private:

        /**
         * @brief Broche de lecture du signal d'entrée provenant du bouton.
         */
        uint8_t _pin;

        /**
         * @brief Définition d'un ensemble de valeurs pour caractériser l'état du bouton.
         * 
         * @note Cet ensemble est défini à partir d'une énumération des états
         *       possibles du bouton avec des constantes de type `uint8_t` de
         *       la façon suivante :
         * 
         *       free     = 0
         *       pressed  = 1
         *       held     = 2
         *       released = 3
         */
        enum _State : uint8_t { free, pressed, held, released };

        /**
         * @brief État du bouton.
         * 
         * @note Cet attribut ne pourra donc prendre que les valeurs définies
         *       par l'énumération `_State` ci-dessus.
         */
        _State _state;

        /**
         * @brief Origine temporelle de l'état "held" (exprimée en millisecondes)
         * 
         * @note L'état "held" correspond à un état qui est prolongé dans le temps.
         *       Nous aurons donc besoin de mesurer la durée pendant laquelle le
         *       bouton aura été maintenu dans cet état. Par conséquent, nous devrons
         *       mémoriser à quel moment cet état a commencé.
         */
        uint32_t _held_start_ms;

        /**
         * @brief Mise à jour de l'état du bouton.
         * 
         * @note Dès lors que les signaux électroniques provenant du bouton auront
         *       été lus et nettoyés par la méthode _debounce(), il sera possible
         *       d'interpréter ces signaux pour déterminer dans quel état se trouve
         *       le bouton (free, pressed, held, released).
         * 
         *       Cette méthode est précisément chargée de cette interprétation.
         */
        void _update();

    protected:

        /**
         * @brief Niveau logique du signal de sortie provenant du bouton.
         * 
         * @note Il correspond à la valeur déparasitée du signal d'entrée
         *       déterminée par la méthode _debounce().
         */
        uint8_t _output;

        /**
         * @brief Déparasitage du signal électronique provenant du bouton.
         * 
         * @param input Niveau logique du signal d'entrée brut (lu directement).
         * 
         * @note Le signal d'entrée parasité par des effets rebonds potentiels
         *       sera directement lu par la fonction digitalRead() sur la broche
         *       de lecture du bouton. La méthode _debounce() se chargera donc
         *       d'éliminer ces parasites à l'aide de différents algorithmes
         *       spécifiques de debouncing qui seront précisés dans les
         *       classes dérivées de ce modèle générique.
         */
        virtual void _debounce(const uint8_t input) = 0;
    
    public:

        /**
         * @brief Déclaration du constructeur.
         * 
         * @param pin Broche de lecture du signal d'entrée provenant du bouton.
         * 
         * @note Le constructeur attend un argument qui permet de préciser
         *       quelle sera la broche de lecture du bouton.
         */
        Button(const uint8_t pin);

        /**
         * @brief Lecture de l'état du bouton.
         * 
         * @note Le signal électronique brut provenant du bouton et lu directement
         *       par la fonction digitalRead() sur la broche de lecture du bouton
         *       est déparasité par la méthode _debounce() pour fournir un signal
         *       logique propre de "sortie". Le niveau logique de sortie permet à
         *       son tour de déterminer dans quel état se trouve le bouton :
         * 
         *           free, pressed, held, ou released
         * 
         *       La méthode read() se charge d'orchestrer toute cette procédure de
         *       lecture et d'interprétation des signaux pour finalement déterminer
         *       l'état du bouton.
         */
        void read();

        /**
         * @brief Détermine si le bouton vient d'être enfoncé.
         * 
         * @return true  si le bouton vient d'être enfoncé,
         *         false sinon.
         * 
         * @note Cet état est fugace et correspond au moment précis où
         *       `_output` passe du niveau logique `LOW` à `HIGH`.
         */
        bool isPressed();

        /**
         * @brief Détermine si le bouton vient d'être relâché.
         * 
         * @return true  si le bouton vient d'être relâché,
         *         false sinon.
         * 
         * @note Cet état est fugace et correspond au moment précis où
         *       `_output` passe du niveau logique `HIGH` à `LOW`.
         */
        bool isReleased();
        
        /**
         * @brief Détermine si le bouton est maintenu enfoncé.
         * 
         * @return true  si le bouton est maintenu enfoncé,
         *         false sinon.
         * 
         * @note Cet état est prolongé tant que le bouton n'est pas relâché.
         */
        bool isHeld();
        
        /**
         * @brief Détermine si le bouton est maintenu enfoncé durant une période suffisante.
         * 
         * @param delay_ms Durée minimale (exprimée en millisecondes) pendant laquelle
         *                 le bouton doit être maintenu enfoncé.
         * 
         * @return true  si le bouton a été maintenu enfoncé pendant au moins `delay_ms` millisecondes,
         *         false sinon.
         */
        bool wasHeldFor(const uint16_t delay_ms);

};