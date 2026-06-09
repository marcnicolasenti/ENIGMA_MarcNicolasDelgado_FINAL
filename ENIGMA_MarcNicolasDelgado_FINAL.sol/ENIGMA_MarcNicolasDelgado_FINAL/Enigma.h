#include <string>

std::string canviarText(std::string text, std::string original, std::string nouText);
std::string netejarMissatge(std::string missatge);
std::string separarEnGrupsDeCinc(std::string missatge);

void demanarPosicions(int posicions[]);
std::string xifrarMissatge(std::string missatge, std::string rotors[], char notches[], int posicions[]);
std::string desxifrarMissatge(std::string missatge, std::string rotors[], char notches[], int posicions[]);

bool escriureFitxer(std::string nomFitxer, std::string contingut);
bool llegirFitxer(std::string nomFitxer, std::string& contingut);

void opcioXifrar(std::string rotors[], char notches[]);
void opcioDesxifrar(std::string rotors[], char notches[]);
