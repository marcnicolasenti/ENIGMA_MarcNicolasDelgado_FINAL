# Simulació bàsica de la màquina ENIGMA

Aquest projecte esta fet per Marc Nicolás
El programa permet xifrar i desxifrar missatges utilitzant tres rotors guardats en fitxers de text.

## Fitxers del projecte

- main.cpp: conté el menú principal.
- Enigma.cpp i Enigma.h: contenen la part de xifrar, desxifrar i tractar els missatges.
- Rotor.cpp i Rotor.h: contenen la part relacionada amb els rotors.
- Rotor1.txt, Rotor2.txt i Rotor3.txt: guarden la configuració dels tres rotors.

Cada fitxer de rotor té una combinació de 26 lletres majúscules sense repetir i, a la línia següent, la seva lletra notch.
Si falta la línia del notch, el programa el que fa es utilitzar la lletra `Z` per defecte.

## Com funciona

Quan s'executa el programa t'apareix un menú amb quatre opcions:

1. Xifrar un missatge.
2. Desxifrar un missatge.
3. Editar els rotors.
4. Sortir del programa.

Per xifrar o desxifrar, el programa demana les tres posicions inicials dels rotors. Perquè el desxifrat funcioni correctament s'han d'introduir les mateixes posicions que es van utilitzar en el xifrat

El text original es guarda a Missatge.txt. El missatge xifrat es guarda a Xifrat.txt en grups de cinc lletres, i el missatge desxifrat es guarda a desxifrat.txt.

L'opció d'editar rotors et permet canviar les 26 lletres del rotor que hagis seleccionat. El programa comprova que siguin lletres majúscules i que no n'hi hagi cap de repetida. El notch que ja tenia el rotor es mante.

