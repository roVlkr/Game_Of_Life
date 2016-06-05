/*
  Main.c
  
  Autor: Roland Völker
  eMail: roland_voelker@web.de
  Datum: 2016-06-05
  Version: 1
  
  Beschreibung: -.
  
  (c) Alle Rechte vorbehalten.
*/


#include "Game.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>


/*
  Nutzt die Funktion "nanosleep" aus time.h um die Ausführung des Programms
  um @millis Millisekunden zu unterbrechen.
*/
void sleepMillis(int millis);

/*
  Erzeugt die Simulationswelt, füllt sie zufällig mit Zellen
  und führt eine Endlosschleife aus, die man nur mit Strg-C 
  unterbrechen kann. Diese Endlosschleife erzeugt die Animation,
  die in der Konsole sichtbar ist.
  Die Länge der Frames ist auf 100 ms festgelegt.
*/
int execGame(int rows, int cols, int amount_cells);



int main(int len, char* args[]) {
  // Grundwerte für die Erzeugung der Welt
  // werden aus den Initialisierungswerten gelesen.
  int rows = 21;
  int cols = 35;
  int amount_cells = 100;
  
  int i;
  for (i = 1; i < len; i++) {
    if (strcmp(args[i], "-r") == 0) {
      rows = atoi(args[++i]);
    } else if (strcmp(args[i], "-c") == 0) {
      cols = atoi(args[++i]);
    } else if (strcmp(args[i], "-a") == 0) {
      amount_cells = atoi(args[++i]);
    }
  }

  if (execGame(rows, cols, amount_cells) == 1)
    return 1;
  
  return 0;
}



int execGame(int rows, int cols, int amount_cells) {
  World w;
  w.rows = rows;
  w.cols = cols;
  w.cells = (byte*) malloc(w.rows*w.cols*sizeof(byte));
  if (w.cells == NULL) return 1;
  
  fillRand(&w, amount_cells);
  
  printWorld(&w);
  while (1) {
    sleepMillis(100);
    step(&w);
    printWorld(&w);   
  }
  
  free(w.cells);
}



void sleepMillis(int millis) {
  struct timespec ts = {millis / 1000, (millis % 1000) * 1000000};
  nanosleep(&ts, NULL);
}

