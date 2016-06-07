/*
  Main.c
  
  Autor: Roland Völker
  Datum: 2016-06-07
  Version: 4
  
  Beschreibung: -.
  
  (c) Alle Rechte vorbehalten.
*/


#include "Game.h"
#include "WorldLoader.h"
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
  Erzeugt die Simulationswelt und füllt sie zufällig mit Zellen.
*/
World makeRandomWorld(int rows, int cols, int amount_cells);


/*
  Führt eine Endlosschleife aus, die man nur mit Strg-C unterbrechen kann. 
  Diese Endlosschleife erzeugt die Animation, die in der Konsole sichtbar ist.
  Die Länge der Frames ist auf 100 ms festgelegt.
*/
int execGame(World w);



int main(int len, char *args[]) {
  // Grundwerte für die Erzeugung der Welt
  // werden aus den Initialisierungswerten gelesen.
  int rows = 21;
  int cols = 35;
  int amount_cells = 100;
  
  World w;
  
  int i;
  for (i = 1; i < len; i++) {
    if (strcmp(args[i], "-l") == 0) {
      w = loadWorld(args[i+1]);
      return execGame(w);
    } else if (strcmp(args[i], "-r") == 0) {
      rows = atoi(args[++i]);
    } else if (strcmp(args[i], "-c") == 0) {
      cols = atoi(args[++i]);
    } else if (strcmp(args[i], "-a") == 0) {
      amount_cells = atoi(args[++i]);
    }
  }
  
  w = makeRandomWorld(rows, cols, amount_cells);
  return execGame(w);
}


int execGame(World w) {
  printWorld(&w);
  
  while (1) {
    sleepMillis(100);    
    step(&w);
    printWorld(&w);  
    printf("\x1B[2J"); // Escape-Sequenz (Löscht den Bildschirm)
  }
}


World makeRandomWorld(int rows, int cols, int amount_cells) {
  World w;
  w.rows = rows;
  w.cols = cols;
  w.cells = (byte*) malloc(w.rows*w.cols);
  if (w.cells == NULL) return w;
  
  fillRand(&w, amount_cells);
  
  return w;
}


void sleepMillis(int millis) {
  struct timespec ts = {millis / 1000, (millis % 1000) * 1000000};
  nanosleep(&ts, NULL);
}

