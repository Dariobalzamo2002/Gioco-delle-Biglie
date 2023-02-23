//
// Created by Dario Balzamo on 29/12/2022.
//
#ifndef GIOCO_DELLE_BIGLIE_SERVICE_H
#define GIOCO_DELLE_BIGLIE_SERVICE_H

// PROTOTIPI FUNCTION UTILIZZATE DAL PROGRAMMA

void regolamento();
void comandi();
void card_da_gioco();
void crea_campo(char *, int);
void visualizza_campo(char *, int);
void genera_elementi_gioco(char [][50], int *, int *, int *, int *);
void move_biglia(int, int *, int *);
int cambio_direzione_rand();
void check_biglia(char [][50], int, int, int *, int *, int);
void rimessa_laterale(char [][50], int, int, int *, int *);

#endif //GIOCO_DELLE_BIGLIE_SERVICE_H
