#include <iostream>
#include <fstream>
#include <string>
#include "Enigma.h"
#include "Rotor.h"

std::string canviarText(std::string text, std::string original, std::string nouText) {
    int posicio = text.find(original);

    while (posicio != -1) {
        text.replace(posicio, original.length(), nouText);
        posicio = text.find(original);
    }

    return text;
}

std::string netejarMissatge(std::string missatge) { // Substituim els accents abans de descartar els caràcters que no siguin A-Z.

    missatge = canviarText(missatge, "à", "a");
    missatge = canviarText(missatge, "á", "a");
    missatge = canviarText(missatge, "À", "A");
    missatge = canviarText(missatge, "Á", "A");
    missatge = canviarText(missatge, "è", "e");
    missatge = canviarText(missatge, "é", "e");
    missatge = canviarText(missatge, "È", "E");
    missatge = canviarText(missatge, "É", "E");
    missatge = canviarText(missatge, "í", "i");
    missatge = canviarText(missatge, "Í", "I");
    missatge = canviarText(missatge, "ï", "i");
    missatge = canviarText(missatge, "Ï", "I");
    missatge = canviarText(missatge, "ò", "o");
    missatge = canviarText(missatge, "ó", "o");
    missatge = canviarText(missatge, "Ò", "O");
    missatge = canviarText(missatge, "Ó", "O");
    missatge = canviarText(missatge, "ú", "u");
    missatge = canviarText(missatge, "Ú", "U");
    missatge = canviarText(missatge, "ü", "u");
    missatge = canviarText(missatge, "Ü", "U");
    missatge = canviarText(missatge, "ç", "c");
    missatge = canviarText(missatge, "Ç", "C");
    missatge = canviarText(missatge, "ñ", "n");
    missatge = canviarText(missatge, "Ñ", "N");
    missatge = canviarText(missatge, "ß", "ss");

    std::string missatgeNet = "";

    for (int i = 0; i < (int)missatge.length(); i++) {
        char lletra = missatge[i];

        if (lletra >= 'a' && lletra <= 'z') {
            lletra = lletra - 32;
        }

        if (lletra >= 'A' && lletra <= 'Z') {
            missatgeNet += lletra;
        }
    }

    return missatgeNet;
}

std::string separarEnGrupsDeCinc(std::string missatge) {
    std::string resultat = "";

    for (int i = 0; i < (int)missatge.length(); i++) {
        if (i > 0 && i % 5 == 0) {
            resultat += ' ';
        }

        resultat += missatge[i];
    }

    return resultat;
}

void demanarPosicions(int posicions[]) {
    std::string entrada;

    std::cout << "Introdueix les posicions inicials dels tres rotors." << std::endl;

    for (int i = 0; i < TOTAL_ROTORS; i++) {
        bool correcte = false;

        do {
            std::cout << "Rotor " << i + 1 << " (A-Z): ";
            std::getline(std::cin, entrada);

            if (entrada.length() == 1) {
                char lletra = entrada[0];

                if (lletra >= 'a' && lletra <= 'z') {
                    lletra = lletra - 32;
                }

                if (lletra >= 'A' && lletra <= 'Z') {
                    posicions[i] = lletra - 'A';
                    correcte = true;
                }
            }

            if (!correcte) {
                std::cout << "Introdueix nomes una lletra entre A i Z." << std::endl;
            }
        } while (!correcte);
    }
}



std::string xifrarMissatge(std::string missatge, std::string rotors[], char notches[], int posicions[]) {  // En aquesta part de xifratge m'he ajudat de la IA.
    std::string resultat = "";

    for (int i = 0; i < (int)missatge.length(); i++) {
        avancarRotors(posicions, notches);

        char lletra = missatge[i];
        lletra = passarRotor(lletra, rotors[0], posicions[0]);
        lletra = passarRotor(lletra, rotors[1], posicions[1]);
        lletra = passarRotor(lletra, rotors[2], posicions[2]);

        resultat += lletra;
    }

    return resultat;
}

std::string desxifrarMissatge(std::string missatge, std::string rotors[], char notches[], int posicions[]) {
    std::string resultat = "";

    for (int i = 0; i < (int)missatge.length(); i++) {
        avancarRotors(posicions, notches);

        char lletra = missatge[i];
        lletra = passarRotorInvers(lletra, rotors[2], posicions[2]);
        lletra = passarRotorInvers(lletra, rotors[1], posicions[1]);
        lletra = passarRotorInvers(lletra, rotors[0], posicions[0]);

        resultat += lletra;
    }

    return resultat;
}

bool escriureFitxer(std::string nomFitxer, std::string contingut) {
    std::ofstream fitxer;
    fitxer.open(nomFitxer);

    if (!fitxer.is_open()) {
        std::cout << "No s'ha pogut escriure el fitxer " << nomFitxer << "." << std::endl;
        return false;
    }

    fitxer << contingut;

    if (fitxer.fail()) {
        std::cout << "Ha fallat la escriptura del fitxer " << nomFitxer << "." << std::endl;
        fitxer.close();
        return false;
    }

    fitxer.close();
    return true;
}

bool llegirFitxer(std::string nomFitxer, std::string& contingut) {
    std::ifstream fitxer;
    fitxer.open(nomFitxer);

    if (!fitxer.is_open()) {
        std::cout << "No s'ha pogut obrir el fitxer " << nomFitxer << "." << std::endl;
        return false;
    }

    contingut = "";
    std::string linia;

    while (std::getline(fitxer, linia)) {
        contingut += linia;
    }

    if (fitxer.bad()) {
        std::cout << "Ha fallat la lectura del fitxer " << nomFitxer << "." << std::endl;
        fitxer.close();
        return false;
    }

    fitxer.close();
    return true;
}

void opcioXifrar(std::string rotors[], char notches[]) {
    int posicions[TOTAL_ROTORS];
    demanarPosicions(posicions);

    std::string missatge;
    std::cout << "Introdueix el missatge que vols xifrar:" << std::endl;
    std::getline(std::cin, missatge);

    if (!escriureFitxer("Missatge.txt", missatge)) {
        return;
    }

    std::string missatgeNet = netejarMissatge(missatge);
    std::string missatgeXifrat = xifrarMissatge(missatgeNet, rotors, notches, posicions);
    std::string missatgeAgrupat = separarEnGrupsDeCinc(missatgeXifrat);

    if (escriureFitxer("Xifrat.txt", missatgeAgrupat)) {
        int grups = (missatgeXifrat.length() + 4) / 5;
        std::cout << "Missatge xifrat a Xifrat.txt (" << missatgeXifrat.length() << " lletres, " << grups << " grups de 5)." << std::endl;
    }
}

void opcioDesxifrar(std::string rotors[], char notches[]) {
    int posicions[TOTAL_ROTORS];
    demanarPosicions(posicions);

    std::string missatgeXifrat;

    if (!llegirFitxer("Xifrat.txt", missatgeXifrat)) {
        return;
    }

    missatgeXifrat = netejarMissatge(missatgeXifrat);
    std::string missatgeDesxifrat = desxifrarMissatge(missatgeXifrat, rotors, notches, posicions);

    if (escriureFitxer("desxifrat.txt", missatgeDesxifrat)) {
        std::cout << "[OK] Missatge desxifrat a desxifrat.txt (" << missatgeDesxifrat.length() << " lletres)." << std::endl;
    }
}
