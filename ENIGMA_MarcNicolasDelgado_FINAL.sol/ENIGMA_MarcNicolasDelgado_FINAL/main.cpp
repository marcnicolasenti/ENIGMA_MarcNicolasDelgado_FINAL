#include <iostream>
#include <string>
#include "Enigma.h"
#include "Rotor.h"

int main() {
    std::string rotors[TOTAL_ROTORS];
    char notches[TOTAL_ROTORS];

    // Carreguem els tres rotors abans de ensenyar el menú.
    if (!carregarRotors(rotors, notches)) {
        std::cout << "Revisa els fitxers dels rotors abans de continuar." << std::endl;
        return 1;
    }

    std::string opcio;

    do {
        std::cout << std::endl;
        std::cout << "ENIGMA:" << std::endl;
        std::cout << "1. Xifrar missatge" << std::endl;
        std::cout << "2. Desxifrar missatge" << std::endl;
        std::cout << "3. Editar rotors" << std::endl;
        std::cout << "4. Sortir" << std::endl;
        std::cout << "Selecciona una opcio: ";
        std::getline(std::cin, opcio);

        if (opcio == "1") {
            opcioXifrar(rotors, notches);
        }
        else if (opcio == "2") {
            opcioDesxifrar(rotors, notches);
        }
        else if (opcio == "3") {
            editarRotor(rotors, notches);
        }
        else if (opcio == "4") {
            std::cout << "Programa finalitzat." << std::endl;
        }
        else {
            std::cout << "Opcio no valida." << std::endl;
        }
    } while (opcio != "4");

    return 0;
}
