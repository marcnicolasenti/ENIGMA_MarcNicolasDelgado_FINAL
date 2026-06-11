#include <iostream>
#include <fstream>
#include <string>
#include "Rotor.h"

std::string nomFitxerRotor(int numeroRotor) {
    if (numeroRotor == 1) {
        return "Rotor1.txt";
    }
    else if (numeroRotor == 2) {
        return "Rotor2.txt";
    }

    return "Rotor3.txt";
}

bool validarPermutacio(std::string rotor) {
    if (rotor.length() != LLETRES_ALFABET) {
        return false;
    }

    // Comprovem que totes siguin majúscules i que no n'hi hagi cap de repetida.
    for (int i = 0; i < LLETRES_ALFABET; i++) {
        if (rotor[i] < 'A' || rotor[i] > 'Z') {
            return false;
        }

        for (int j = i + 1; j < LLETRES_ALFABET; j++) {
            if (rotor[i] == rotor[j]) {
                return false;
            }
        }
    }

    return true;
}

bool validarNotch(std::string liniaNotch) {
    return liniaNotch.length() == 1 && liniaNotch[0] >= 'A' && liniaNotch[0] <= 'Z';
}

bool crearRotorPerDefecte(std::string nomFitxer, int numeroRotor) {
    std::string rotor;
    char notch;

    if (numeroRotor == 1) {
        rotor = "EKMFLGDQVZNTOWYHXUSPAIBRCJ";
        notch = 'Q';
    }
    else if (numeroRotor == 2) {
        rotor = "AJDKSIRUXBLHWTMCQGZNPYFVOE";
        notch = 'E';
    }
    else {
        rotor = "BDFHJLCPRTXVZNYEIWGAKMUSQO";
        notch = 'V';
    }

    std::ofstream fitxer;
    fitxer.open(nomFitxer);

    if (!fitxer.is_open()) {
        std::cout << "ERROR No s'ha pogut crear " << nomFitxer << "." << std::endl;
        return false;
    }

    fitxer << rotor << std::endl;
    fitxer << notch << std::endl;

    if (fitxer.fail()) {
        std::cout << "No s'ha pogut escriure " << nomFitxer << "." << std::endl;
        fitxer.close();
        return false;
    }

    fitxer.close();
    return true;
}

bool carregarRotors(std::string rotors[], char notches[]) {
    for (int i = 0; i < TOTAL_ROTORS; i++) {
        std::string nomFitxer = nomFitxerRotor(i + 1);
        std::ifstream fitxer;
        fitxer.open(nomFitxer);

        // En cas de qye faltès un rotor, es crea automàticament amb una configuració vàlida.
        if (!fitxer.is_open()) {
            std::cout << "No s'ha trobat " << nomFitxer << ". Es creara automaticament." << std::endl;

            if (!crearRotorPerDefecte(nomFitxer, i + 1)) {
                return false;
            }

            fitxer.open(nomFitxer);
        }

        if (!fitxer.is_open()) {
            std::cout << "No s'ha pogut obrir " << nomFitxer << "." << std::endl;
            return false;
        }

        if (!std::getline(fitxer, rotors[i])) {
            std::cout << "ERROR " << nomFitxer << ": no s'ha pogut llegir la permutacio." << std::endl;
            fitxer.close();
            return false;
        }

        if (!validarPermutacio(rotors[i])) {
            std::cout << "ERROR " << nomFitxer << ": calen 26 lletres uniques entre A i Z." << std::endl;
            fitxer.close();
            return false;
        }

        std::string liniaNotch;

        // Si no hi ha segona línia o esta buida, el notch per defecte es Z.
        if (!std::getline(fitxer, liniaNotch) || liniaNotch.length() == 0) {
            notches[i] = 'Z';
        }
        else {
            if (!validarNotch(liniaNotch)) {
                std::cout << "ERROR " << nomFitxer << ": el notch ha de ser una sola lletra entre A i Z." << std::endl;
                fitxer.close();
                return false;
            }

            notches[i] = liniaNotch[0];
        }

        std::string liniaExtra;

        if (std::getline(fitxer, liniaExtra)) {
            std::cout << "ERROR " << nomFitxer << ": el fitxer nomes pot tenir dues linies." << std::endl;
            fitxer.close();
            return false;
        }

        if (fitxer.bad()) {
            std::cout << "No s'ha pogut llegir " << nomFitxer << "." << std::endl;
            fitxer.close();
            return false;
        }

        fitxer.close();
    }

    return true;
}

void avancarRotors(int posicions[], char notches[]) {
    // El primer rotor sempre avança una posició per cada lletra.
    posicions[0]++;

    if (posicions[0] == LLETRES_ALFABET) {
        posicions[0] = 0;
    }

    // Quan arriba al notch, també avança el rotor següent.
    if ('A' + posicions[0] == notches[0]) {
        posicions[1]++;

        if (posicions[1] == LLETRES_ALFABET) {
            posicions[1] = 0;
        }

        if ('A' + posicions[1] == notches[1]) {
            posicions[2]++;

            if (posicions[2] == LLETRES_ALFABET) {
                posicions[2] = 0;
            }
        }
    }
}

char passarRotor(char lletra, std::string rotor, int posicio) {
    int entrada = lletra - 'A';
    entrada = entrada + posicio;

    if (entrada >= LLETRES_ALFABET) {
        entrada = entrada - LLETRES_ALFABET;
    }

    int sortida = rotor[entrada] - 'A';
    sortida = sortida - posicio;

    if (sortida < 0) {
        sortida = sortida + LLETRES_ALFABET;
    }

    return 'A' + sortida;
}

char passarRotorInvers(char lletra, std::string rotor, int posicio) {
    int entrada = lletra - 'A';
    entrada = entrada + posicio;

    if (entrada >= LLETRES_ALFABET) {
        entrada = entrada - LLETRES_ALFABET;
    }

    char lletraBuscada = 'A' + entrada;
    int posicioTrobada = 0;

    // Busquem en quina posició es troba la lletra.
    for (int i = 0; i < LLETRES_ALFABET; i++) {
        if (rotor[i] == lletraBuscada) {
            posicioTrobada = i;
        }
    }

    posicioTrobada = posicioTrobada - posicio;

    if (posicioTrobada < 0) {
        posicioTrobada = posicioTrobada + LLETRES_ALFABET;
    }

    return 'A' + posicioTrobada;
}

void editarRotor(std::string rotors[], char notches[]) {
    std::string opcioText;
    int numeroRotor = 0;

    std::cout << "Quin rotor vols editar? (1-3): ";
    std::getline(std::cin, opcioText);

    if (opcioText == "1") {
        numeroRotor = 1;
    }
    else if (opcioText == "2") {
        numeroRotor = 2;
    }
    else if (opcioText == "3") {
        numeroRotor = 3;
    }
    else {
        std::cout << " Rotor no valid." << std::endl;
        return;
    }

    std::string novaPermutacio;
    std::cout << "Introdueix les 26 lletres del rotor sense espais:" << std::endl;
    std::getline(std::cin, novaPermutacio);

    if (!validarPermutacio(novaPermutacio)) {
        std::cout << "La permutacio ha de tenir 26 lletres uniques entre A i Z." << std::endl;
        return;
    }

    int posicioArray = numeroRotor - 1;
    std::string nomFitxer = nomFitxerRotor(numeroRotor);
    std::ofstream fitxer;
    fitxer.open(nomFitxer);

    if (!fitxer.is_open()) {
        std::cout << "No s'ha pogut escriure " << nomFitxer << "." << std::endl;
        return;
    }

    rotors[posicioArray] = novaPermutacio;
    fitxer << rotors[posicioArray] << std::endl;
    fitxer << notches[posicioArray] << std::endl;

    if (fitxer.fail()) {
        std::cout << "No s'ha pogut escriure " << nomFitxer << "." << std::endl;
        fitxer.close();
        return;
    }

    fitxer.close();

    std::cout << "OK " << nomFitxer << " actualitzat correctament." << std::endl;
    std::cout << "El notch es conserva: " << notches[posicioArray] << std::endl;
}
