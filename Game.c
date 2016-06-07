/*
  Game.c
  
  Autor: Roland Völker
  Datum: 2016-06-05
  Version: 1
  
  (c) Alle Rechte vorbehalten.
*/


#include "Game.h"
#include <stdlib.h>
#include <stdio.h>



int step(World* w) {
  // Anlegen einer temporären Welt
  byte* tempCells = (byte*) malloc(w->rows*w->cols*sizeof(byte));
  if (tempCells == NULL) return 1;
  
  uint i;
  uint len = w->rows*w->cols;
  for (i = 0; i < len; i++) {
    tempCells[i] = simulateCell(i, w);
  }
  
  /*
    -- "Echte" Welt überschreiben --    
    Dabei werden nicht die Werte ausgetauscht,
    sondern einfach die Startadresse, was wesentlich
    Zeitsparender ist.
  */
  byte* oldAddress = w->cells;
  w->cells = tempCells;  
  free(oldAddress); 
  
  return 0;
}



byte simulateCell(int index, World const* w) {
  // Berechne unter den 8 Nachbarn die Anzahl der lebenden,
  // da sich alle Regeln darauf reduzieren lassen.
  int sum = 0;
  int row = index / w->cols;
  int i, j;
  for (i = -1; i < 2; i++) {
    for (j = -1; j < 2; j++) {
      if (i == 0 && j == 0)
        continue;
      
      int r = (row + i + w->rows) % w->rows;
      int c = (index + j + w->cols) % w->cols;
      sum += w->cells[r*w->cols + c];
    }
  }
  
  // Hier die eigentlichen Regeln des "Game of Life"
  // in kurzer Schreibweise.
  if (w->cells[index]) {
    if (sum == 2 || sum == 3) return 1;
    else return 0;
  } else {
    if (sum == 3) return 1;
    else return 0;
  }
}



void printWorld(World const* w) {
  uint r, c;
  
  // Umrandung oben
  printf("--");
  for (c = 0; c < w->cols; c++) {
    printf("--");
  }
  printf("-\n");
  
  for (r = 0; r < w->rows; r++) {
    printf("| ");
    for (c = 0; c < w->cols; c++) {
      // Tote Zelle wird durch Leerzeichen repräsentiert,
      // lebende Zelle durch eine Raute ("#")
      char block = (w->cells[r*w->cols + c] == 0) ? 32 : '#';
      printf("%c ", block);
    }
    
    printf("|\n");
  }  
  
  // Umrandung unten (gleiche wie oben)
  printf("--");
  for (c = 0; c < w->cols; c++) {
    printf("--");
  }
  printf("-\n");
  
  // Puffer wird geleert, um bei Animation sofort ein
  // Bild ausgeben zu können.
  fflush(stdout);
}



void fillRand(World* w, int amount) {
  srand((unsigned int) time(NULL));
  uint len = w->rows*w->cols;
  
  uint i;
  for (i = 0; i < amount; i++) {
    w->cells[rand() % len] = 1;
  }
}

