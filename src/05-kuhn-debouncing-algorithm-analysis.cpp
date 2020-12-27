/*
 * -------------------------------------------------------------------------
 * Atelier de programmation Robotic 974
 * © 2020 Stéphane Calderoni
 * -------------------------------------------------------------------------
 * Introduction à la programmation des cartes Arduino
 * Contrôle d'un chenillard à 8 LEDs par un bouton poussoir
 * -------------------------------------------------------------------------
 * Analyse et illustration de l'algorithme de debouncing de Kenneth A. Kuhn
 * 
 * --> https://www.kennethkuhn.com/electronics/debounce.c
 * 
 * Un intégrateur est utilisé pour effectuer une hystérésis temporelle de
 * sorte que le signal d'entrée doit être maintenu dans un état logique
 * (0 ou 1) constant pour que la sortie passe à cet état.
 * -------------------------------------------------------------------------
 */

#include <Arduino.h>

/**
 * @brief Broche de lecture de l'état du bouton.
 */
const uint8_t BTN_PIN = 2;

/**
 * @brief Seuil maximal de l'intégrateur.
 * 
 * @note Vous pouvez jouer sur sa valeur pour ajuster la fenêtre d'échantillonnage
 *       au comportement effectif de votre bouton poussoir.
 */
const uint8_t DEBOUNCING_THRESHOLD = 8;

/**
 * @brief Nombre d'échantillons maximal pouvant être enregistrés.
 * 
 * @note Cette valeur est fixée empiriquement sur la base des observations
 *       que j'ai effectuées sur différentes fenêtres d'échantillonnage.
 */
const uint8_t MAX_SAMPLES = 4 * DEBOUNCING_THRESHOLD;

// -----------------------------------------------------------------------------
// Enregistrement des données (échantillonnage)
// -----------------------------------------------------------------------------

/**
 * @brief Structure d'un échantillon.
 */
struct Sample {
    uint8_t  input;        // Signal d'entrée.
    uint8_t  integrator;   // Valeur instantanée de l'intégrateur.
    uint8_t  output;       // Signal de sortie.
    uint32_t timestamp_us; // Date de l'enregistrement (exprimée en microsecondes).
};

/**
 * @brief Enregistreur de données.
 */
struct DataLogger {

    // Collection d'échantillons.
    Sample samples[MAX_SAMPLES];

    uint8_t records;         // Nombre d'échantillons enregistrés.
    uint8_t input;           // Valeur instantanée du signal d'entrée.
    uint8_t integrator;      // Valeur instantanée de l'intégrateur.
    uint8_t output;          // Valeur instantanée du signal de sortie.
    
    uint8_t last_integrator; // Dernière valeur connue de l'intégrateur.

    /**
     * @brief Lecture de l'état du bouton (signal d'entrée).
     */
    void read() {

        // Lecture de la broche du bouton
        input = digitalRead(BTN_PIN);

        // Algorithme hystérétique de Kenneth A. Kuhn

             if (!input) { if (integrator) integrator--; }
        else if (integrator < DEBOUNCING_THRESHOLD) integrator++;

             if (!integrator) output = 0;
        else if (integrator == DEBOUNCING_THRESHOLD) output = 1;

    }

    /**
     * @brief Sauvegarde opportuniste d'un échantillon.
     * 
     * @param time_us Date de capture de l'échantillon (exprimée en microsecondes).
     */
    void save(const uint32_t time_us) {

        // On n'enregistre un échantillon que lorsque la valeur instantanée
        // de l'intégrateur a changé. En effet, les cas où l'intégrateur demeure
        // constant sont les suivants :
        //   - soit il est nul, autrement dit le bouton est considéré comme au repos,
        //   - soit il a atteint sa valeur maximale, auquel cas le signal s'est stabilisé.
        if (integrator != last_integrator) {

            // On sélectionne l'échantillon qui va recevoir les données à enregistrer.
            Sample * const sample = &samples[records];

            // Et on sauvegarde les données collectées par l'algorithme de Kenneth A. Kuhn.
            sample->input        = input;
            sample->integrator   = integrator;
            sample->output       = output;
            sample->timestamp_us = time_us;

            // Normalement, il suffirait d'incrémenter simplement le nombre d'enregistrements.
            // records++;

            // Mais on préfère jouer la prudence pour éviter un débordement...
            ++records %= MAX_SAMPLES;

            // Et on n'oublie pas de sauvegarder la dernière valeur connue de l'intégrateur.
            last_integrator = integrator;

        }

    }

    /**
     * @brief Implémentation d'une fonction de remplacement de Serial.printf() qui n'est pas
     *        fournie par le framework Arduino pour les cartes Uno et Nano.
     * 
     * @param format Chaîne de caractères décrivant le format d'affichage.
     * @param ...    Liste des données à afficher.
     * 
     * @note Vous pouvez vous affranchir de chercher à comprendre comment elle est implémentée
     *       dans la mesure où vous n'avez pas encore acquis les connaissances suffisantes en
     *       langage C++ pour cela...
     * 
     * @see https://playground.arduino.cc/Main/Printf/
     */
    void printf(const __FlashStringHelper *format, ...) {

        char    buffer[32];
        va_list args;

        va_start (args, format);
        vsnprintf_P(buffer, sizeof(buffer), (const char *)format, args);
        va_end(args);
        
        Serial.print(buffer);

    }

    /**
     * @brief Restitution des données enregistrées.
     * 
     * @note Rien de bien compliqué ici, si ce n'est (à la rigueur) le formatage
     *       de l'affichage pour faciliter la lecture des données...
     * 
     *       Cette fonction affiche simplement les données enregistrée au cours de
     *       l'échantillonnage dans une table formatée ainsi :
     * 
     *                  _______________________ rang de l'échantillon
     *                 /         ______________ durée écoulée depuis l'échantillon précédent (en µs)
     *                /         /   ___________ signal d'entrée
     *               /         /   /    _______ intégrateur et sens de variation
     *              /         /   /    /     __ signal de sortie
     *             /         /   /    /     /
     *           ---+---------+---+------+---
     *            # |      µs | i |  ∑   | o
     *           ---+---------+---+------+---
     *            1 |       0 | 1 |  1 + | 0
     *            2 |       8 | 1 |  2 + | 0
     *            3 |      12 | 1 |  3 + | 0
     *            4 |       8 | 1 |  4 + | 0
     *            5 |       8 | 1 |  5 + | 0
     *            6 |      12 | 1 |  6 + | 0
     *            7 |       8 | 1 |  7 + | 0
     *           ---+---------+---+------+---             (DEBOUNCING_THRESHOLD = 8)
     *            8 |       8 | 1 |  8 + | 1  <-- L'intégrateur atteint ici le seuil maximal,
     *           ---+---------+---+------+---     donc le signal de sortie passe à 1.
     *            9 |      48 | 0 |  7 - | 1  -+
     *           10 |       8 | 0 |  6 - | 1   |  Puis on observe la manifestation d'un rebond,
     *           11 |       8 | 0 |  5 - | 1   |  le signal d'entrée repasse à 0, puis revient à 1,
     *           12 |      12 | 1 |  6 + | 1   |  donc l'intégrateur décroît puis croît à nouveau.
     *           13 |       8 | 1 |  7 + | 1   |
     *           ---+---------+---+------+---  |
     *           14 |       8 | 1 |  8 + | 1  -+
     *           ---+---------+---+------+---
     *           15 |    4700 | 0 |  7 - | 1  -+  On voit que le bouton est maintenu enfoncé
     *           16 |       8 | 0 |  6 - | 1   |  pendant près de 5 millisecondes.
     *           17 |      12 | 0 |  5 - | 1   |
     *           18 |       8 | 0 |  4 - | 1   |  Puis l'intégrateur descend en chute libre
     *           19 |       8 | 0 |  3 - | 1   |  car le bouton est relâché par l'utilisateur...
     *           20 |      12 | 0 |  2 - | 1   |
     *           21 |       8 | 0 |  1 - | 1  -+
     *           ---+---------+---+------+---
     *                            |  0 - | 0  <-- pour finalement retomber à zéro (plancher)
     *                                            et le signal de sortie repasse alors à 0.
     */
    void dump() {

        uint32_t last_us = samples[0].timestamp_us;

        Serial.print(F("\n\n"));
        Serial.print(F("---+---------+---+------+---\n"));
        Serial.print(F(" # |      µs | i |  ∑   | o\n"));
        Serial.print(F("---+---------+---+------+---\n"));

        for (uint8_t i=0; i<records; i++) {

            Sample * const sample = &samples[i];
            bool           is_max = sample->integrator == DEBOUNCING_THRESHOLD;

            if (is_max) Serial.println(F("---+---------+---+------+---"));

            printf(F("%2u | %7lu | %u | %2u %c | %u\n"),
                i+1,
                sample->timestamp_us - last_us,
                sample->input,
                sample->integrator,
                sample->input ? '+' : '-',
                sample->output);

            if (is_max) Serial.println(F("---+---------+---+------+---"));

            last_us = sample->timestamp_us;

        }
        
        Serial.print(F("---+---------+---+------+---\n"));

        // Réinitialisation des données de l'enregistreur.
        records         = 0;
        last_integrator = 0;

    }

};

DataLogger logger; 

// -----------------------------------------------------------------------------
// Squelette du programme principal
// -----------------------------------------------------------------------------

/**
 * @brief Démarrage du programme.
 */
void setup() {

    // Configuration de la broche de lecture du bouton.
    pinMode(BTN_PIN, INPUT);
    
    // Initialisation du moniteur série.
    Serial.begin(9600);
    while (!Serial);
    Serial.println(F("\n\nDebouncing with Kenneth A. Kuhn's algorithm"));
    Serial.println(F("https://www.kennethkuhn.com/electronics/debounce.c"));

}

/**
 * @brief Boucle de contrôle principale.
 */
void loop() {

    // Lecture de l'état courant du bouton.
    logger.read();

    // Si l'intégrateur n'est pas nul, c'est que le bouton a été sollicité.
    // Il convient donc de démarrer la fenêtre d'échantillonnage et de
    // poursuivre les enregistrements jusqu'à ce que l'intégrateur retombe
    // à une valeur nulle, indiquant que le bouton est de nouveau au repos.
    // 
    // Dans ce cas, on contrôle si des enregistrements ont été effectués et,
    // le cas échéant, on restitue les données d'échantillonnage avant de
    // lancer la prochaine collecte.

         if (logger.integrator) logger.save(micros());
    else if (logger.records) logger.dump();

}