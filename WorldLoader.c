/*
  WorldLoader.c
  
  Autor: Roland Völker
  Datum: 2016-06-07
  Version: 4
  
  (c) Alle Rechte vorbehalten.
*/


#include "WorldLoader.h"
#include <string.h>
#include <stdlib.h>


//TODO: assert-Meldungen!


int copy(byte **cells_ptr, byte buffer[BUFFER_SIZE],
         int *cells_len, int buffer_len) {
  // Kopiert die Adresse des Speichers, mit der erstmal
  // weitergearbeitet wird
  byte *cells = *cells_ptr;
  
  if (cells == NULL) // => malloc
    if ((cells = (byte*) malloc(buffer_len)) == NULL) return 1;
  else // => realloc
    if ((cells = (byte*) realloc(cells, buffer_len)) == NULL) return 1;  
  
  int index;
  for (index = 0; index < buffer_len; index++)
    cells[*cells_len + index] = buffer[index];
  
  *cells_len += buffer_len;
  *cells_ptr = cells;
  
  return 0;
}



World loadWorld(char *fileName) {  
  FILE *stream;
  World w = {0, 0, NULL}; // WICHTIG: Startwert NULL
  
  if ((stream = fopen(fileName, "r")) == NULL) 
    return w;
  
  char b = fgetc(stream); // aktuelles Zeichen
  byte buffer[BUFFER_SIZE];
  
  int cells_len = 0; // Anzahl der in w.cells befindlichen Werte
  int rows = 0; // Anzahl bisher gelesener Reihen
  int index = 0; // Index in w.cells (NICHT in stream, also ohne '\n')
  
  while (!feof(stream)) {
    if (b != '\n')
      // "char-Zahl" wird als int-Wert gespeichert.
      buffer[index++] = (b == '0') ? 0 : 1;
    else 
      rows++;
    
    if (index == BUFFER_SIZE) {
      if (!copy(&w.cells, buffer, &cells_len, BUFFER_SIZE))
        return w;
        
      index = 0;
    }
      
    b = fgetc(stream);
  }
  
  // Alle Reste im buffer werden nun auch kopiert
  copy(&w.cells, buffer, &cells_len, index);
  
  w.rows = rows;
  w.cols = cells_len / rows;
  return w; 
}

