/*
  Game.h
  
  Autor: Roland Völker
  eMail: roland_voelker@web.de
  Datum: 2016-06-05
  Version: 1
  
  Beschreibung: Enthält alle Funktionen zur Simulation der
                Simulationswelt des "Game of Life".
  
  (c) Alle Rechte vorbehalten.
*/


typedef unsigned int uint;
typedef unsigned char byte;


/*
  Repräsentiert die Grundeigenschaften der "Welt".
  - Anzahl der Reihen
  - Anzahl der Spalten
  - Array der Zellen
*/
typedef struct World {
  uint rows;
  uint cols;
  byte* cells;
} World;


/*
  Macht einen Schritt in der Simulation für die angegebene Welt.
*/
int step(World* w);


/*
  Simuliert eine einzige Zelle und gibt den Wert
  0 = tot oder
  1 = lebendig
  zurück.
*/
byte simulateCell(int index, World const* w);


/*
  "Zeichnet" die Zellen und eine Umrandung der Welt.
*/
void printWorld(World const* w);


/*
  Füllt die Welt zufällig mit n (= @amount) lebenden Zellen.
*/
void fillRand(World* w, int amount);

