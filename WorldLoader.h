/*
  WorldLoader.h
  
  Autor: Roland Völker
  Datum: 2016-06-07
  Version: 3
  
  Beschreibung: Enthält die Funktionen für das Feature, die Welt
                in eine Datei zu schreiben und aus einer Datei
                zu lesen. Dabei sind die Dateien im CSV-Format.
  
  (c) Alle Rechte vorbehalten.
*/


#include "Game.h"
#include <stdio.h>

#ifndef WORLDLOADER_H_
#define WORLDLOADER_H_

#define BUFFER_SIZE 128


/*
  Hilfsfunktion zum Kopieren des Buffers mit der Länge @len
  in das @cells-Array der entsprechenden World-Struktur.
  
  Kann den Wert 0 zurückgeben, falls ein Speicherfehler
  aufgetaucht ist.
*/
int copy(byte **cells_ptr, byte buffer[BUFFER_SIZE], 
         int *cells_len, int buffer_len);


/*
  Liest die Daten (bestehen aus 1en und 0en) aus der angegebenen Datei.
  Diese Datei darf außer '\n' keine Trennzeichen haben. Außerdem darf
  es keine überflüssigen Zeilenumbrüche geben, da diese als Reihen gewertet
  werden.
  
  Die Funktion gibt nach dem Einlesen eine World-Struktur (siehe Game.h) zurück.
*/
World loadWorld(char *fileName);

#endif

