//
// PROGRAMMA: SIMULAZIONE GIOCO DELLE BIGLIE.
// Created by Dario Balzamo on 29/12/2022.
//

#include "service.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/*
 * Simulazione del gioco delle biglie: un giocatore in ogni istante lancia una biglia su un campo 50x50
 * in una delle direzioni scelte (Nord, sud, ovest, est).
 * L'obiettivo del gioco è lanciare la biglia fino ad arrivare nella buca per poter vincere; durante il suo
 * percorso, però, la pedina potrebbe incontrare degli ostacoli da gioco, quali trappole e buche casuali aumentando
 * la difficoltà del gioco.
 * Infine, Il gioco termina o quando la palla va nella buca principale o quando si superano 50 tiri.
 */

//  Definizione costante n_col
#define n_col 50

int main() {

    //  [--DICHIARAZIONE VARIABILI--]
    char campo[50][50];         // Dichiarazione array 2D (bidimensionale) per il campo da gioco.
    int biglia_x, biglia_y;     // Dichiarazione var. intere per le coordinate (x, y) dell'elemento biglia sul campo.
    int buca_x, buca_y;         // Dichiarazione var. intere per le coordinate (x, y) dell'elemento buca sul campo.
    int tiri = 0;               // Dichiarazione var. intera tiri al fine di contare il numero di lanci della biglia.
    int direzione;              // Dichiarazione var. utilizzata per memorizzare la direzione della biglia lanciata.
    int pos_x, pos_y;           /* Dichiarazione var. temporanee per memorizzare, dopo il cambio direzione,
                                   la posizione aggiornata della biglia ed è adibita per i controlli ostacoli. */

    srand(time(NULL)); //  Settaggio seed (seme) per la generazione di numeri pseudocasuali.

    //  REGOLAMENTO + MINI GUIDA AL GIOCO
    regolamento();
    card_da_gioco();
    printf("COME SI GIOCA ?\n");
    system("pause");
    printf("L'utente puo' muovere la biglia premendo i seguenti comandi:\n");
    comandi();
    system("pause");
    system("cls");

    //  CREAZIONE PARTITA
    crea_campo(&campo[0][0], n_col);
    genera_elementi_gioco(&campo[0][0], &biglia_x, &biglia_y, &buca_x, &buca_y);
    while(tiri < 50 )
    {
        pos_x = biglia_x;       // AGGIORNAMENTO MEMORIA
        pos_y = biglia_y;       // AGGIORNAMENTO MEMORIA
        tiri++;
        visualizza_campo(&campo[0][0], n_col);
        comandi();
        printf("\n[%d/%d] TIRI\n", tiri, 50);
        printf("MUOVI LA BIGLIA VERSO: ");
        scanf("%d", &direzione);
        move_biglia(direzione,&pos_x, &pos_y);
        check_biglia(&campo[0][0], pos_x, pos_y, &biglia_x, &biglia_y, tiri);
        rimessa_laterale(&campo[0][0], pos_x, pos_y, &biglia_x, &biglia_y);
        system("cls");
    }
    /* L'uscita dal While significa che la biglia non ha ancora fatto centro nella buca principale, di conseguenza
       l'utente ha effettuato un numero di lanci maggiore dal numero prestabilito dal gioco, ovvero 50 TIRI.    */
    printf("GAME-OVER.\nHAI ESAURITO I TIRI !\n");
    printf("[SCORE %d]\n", tiri);
    system("pause");
    system("cls");
    return 0;
}