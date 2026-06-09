#include <string>

#define TOTAL_ROTORS 3
#define LLETRES_ALFABET 26

bool validarPermutacio(std::string rotor);
bool validarNotch(std::string liniaNotch);
bool crearRotorPerDefecte(std::string nomFitxer, int numeroRotor);
bool carregarRotors(std::string rotors[], char notches[]);

void avancarRotors(int posicions[], char notches[]);
char passarRotor(char lletra, std::string rotor, int posicio);
char passarRotorInvers(char lletra, std::string rotor, int posicio);

void editarRotor(std::string rotors[], char notches[]);
