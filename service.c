//
//  IMPLEMENTAZIONI FUNCTION UTILIZZATE DAL PROGRAMMA
//  Created by Dario Balzamo on 29/12/2022.
//

// DIRETTIVE DEL PRECOMPILATORE
#include "service.h"
#include <stdio.h>
#include <stdlib.h>

// DEFINIZIONE COSTANTE length
#define length 50


/* La void function regolamento() è utilizzata dal programma per spiegare all'utente il regolamento e come si gioca
   al gioco delle biglie. */
void regolamento()
{
    printf("\t\t\t\tGIOCO DELLE BIGLIE\n");
    printf("-------------------------------------------------------------------------------------------------------\n");
    printf("\t\t\t\tREGOLAMENTO\n");
    printf("\t\t------------------------------------------------\n\n");
    printf(" Un player ha una sua biglia 'B' e in ogni istante puo' lanciarla in una delle 4 direzioni:\n"
           "-[1] NORD;\n"
           "-[2] EST;\n"
           "-[3] SUD;\n"
           "-[4] OVEST.\n"
           " La direzione puo' cambiare casualmente direzione (in una delle quattro) con una\n"
           " probabilita' del 20 per cento.\n"
           " Nel campo da gioco esiste una sola buca 'O', scelta in modo casuale all'inizio del gioco,\n"
           " che permette di terminare il gioco ed e' nota al giocatore.\n"
           " La biglia che va fuori va rimessa in una posizione casuale sul bordo da dove e' uscita.\n"
           " Il gioco termina o quando la palla va nella buca principale o quando si superano 50 tiri.\n");
}

/* La void function comandi() ha la finalità di mostrare all'utente i comandi adibiti allo spostamento della biglia
   sul campo da gioco, scegliendo una delle quattro direzioni date (NORD,EST,SUD,OVEST).  */
void comandi()
{
    printf("\t* * * * * * * * * * * * * *\n");
    printf("\t*           NORD          *\n");
    printf("\t*           [1]           *\n");
    printf("\t*   O                     *\n");
    printf("\t*   V                 E   *\n");
    printf("\t*   E [4]         [2] S   *\n");
    printf("\t*   S                 T   *\n");
    printf("\t*   T                     *\n");
    printf("\t*           [3]           *\n");
    printf("\t*           SUD           *\n");
    printf("\t* * * * * * * * * * * * * *\n");
}

/*  La void function illustra le varie carte,posizionate in modo puramente casuale sulla mappa da gioco,
    che una biglia può incontrare durante il game.  */
void card_da_gioco()
{
    printf(" Il giocatore puo' incontrare diverse difficolta' durante il percorso, "
           " tali ostacoli sono detti cards.\n"
           " Le carte nascoste sulla mappa da gioco sono le seguenti:\n\n");

    printf("\t* * * * * *");
    printf("\tCard c: e' una carta 'BUCA CASUALE'. 30 buche nascoste al giocatore fanno andare la biglia in\n");
    printf("\t*         *");
    printf("\tun'altra posizione scelta casualmente.\n");
    printf("\t*         *\n");
    printf("\t*   CARD  *\n");
    printf("\t*    c    *\n");
    printf("\t*         *\n");
    printf("\t* * * * * *\n\n");

    printf("\t* * * * * *");
    printf("\tCard p: e' una carta 'TRAPPOLA PERDENTE'. 10 buche nascoste fanno terminare il gioco senza\n");
    printf("\t*         *");
    printf("\tarrivare alla fine del gioco\n");
    printf("\t*         *\n");
    printf("\t*   CARD  *\n");
    printf("\t*    p    *\n");
    printf("\t*         *\n");
    printf("\t* * * * * *\n\n");
}

/* La void function crea_campo() ha come:
   - dato d'input: un parametro puntatore array 2D campo, inizialmente vuoto, e il suo numero
   di colonne (per la mappa di memorizzazione);
   - dato di output: lo stesso array campo ma inizializzato.
   Tale function opera in place, costruendo così il campo da gioco.
   Si supponga:
   il carattere ' ' come prato del campo;
   il carattere '*' come bordi del campo.
   Si otterrà la matrice 50x50 recintata dai bordi  */
void crea_campo(char *campo, int n_col)
{
    int i, j;
    for (i = 0; i < length; i++)
    {
        for (j = 0; j < length; j++)
        {
            *(campo+n_col*i+j) = ' ';
            *(campo+n_col*0+j) = '*';
            *(campo+n_col*49+j) = '*';
        }
        *(campo+n_col*i+0) = '*';
        *(campo+n_col*i+49) = '*';
    }
}

/* La void function visualizza_campo() ha come
   - dato d'input: un parametro puntatore array 2D campo e il suo size di colonne per la mappa di memorizzazione;
   - dato di output: la visualizzazione dell'array 2D campo
   la function mostra la griglia di gioco con i suoi elementi principali (biglia e buca), nascondendo
   gli ostacoli, quali trappole perdenti 'p' e buche casuali 'c'. */
void visualizza_campo(char *campo, int n_col)
{
    int i, j;
    for (i = 0; i < length; i++)
    {
        for (j = 0; j < length; j++)
        {
            if( *(campo+n_col*i+j) == 'p' || *(campo+n_col*i+j) == 'c')
                printf("  ");
            else
                printf("%2c", *(campo+n_col*i+j) );
        }
        printf("\n");
    }
}

/* La void function genera_elementi_gioco() ha come:
   - dato d'input: un array 2D campo;;
   - dato di output: biglia_x, biglia_y, buca_x, buca_y, utilizzati per inizializzare gli elementi
   biglia e buca nell'array campo.
   La function genera le posizioni x e y degli elementi in modo pseudocasuale, successivamente inizializza l'array
   campo con i seguenti elementi:
   - biglia --> B
   - buca   --> O
   - buche casuali --> c
   - trappole --> p
 */
void genera_elementi_gioco(char campo[][50], int *biglia_x, int *biglia_y, int *buca_x, int *buca_y)
{
    int i, x, y;            // Dichiarazioni var. locali, intere scalari.
                            // N.B le variabili x e y sono utilizzate esclusivamente per inizializzare gli ostacoli.

    //  Inizializzazione delle 30 buche casuali.
    for(i = 0; i < 30; i++)
    {
        x = 1+rand()%48;
        y = 1+rand()%48;
        campo[x][y] = 'c';
    }

        // N.B !!
    /*  L’algoritmo usa la function rand() in stdlib per generare numeri casuali:
        si ricorda che la chiamata x = 1 + rand() % 48; genera un numero casuale intero (distribuzione
        uniforme) nell’insieme (1,2,3,4,...48).
        (x--> indice riga || y--> indice colonna).
        L'insieme è [1,48] e non [0,49] perché:
        la riga x = 0 e x = 49 identifica i margini superiore e inferiore del campo.
        Invece, la colonna y = 0 e y = 49, identifica i bordi laterali dx e sx del campo.  */

    //  Inizializzazione delle 10 buche che fanno terminare il game.
    for(i = 0; i < 10; i++)
    {
        x = 1+rand()%48;
        y = 1+rand()%48;
        if(campo[x][y] != 'c')
            campo[x][y] = 'p';
    }

    /*  Inizializzazione della buca principale sul campo. Tale buca consente di vincere il game. */
    *buca_x = 1+rand()%48;
    *buca_y = 1+rand()%48;
    if(campo[*buca_x][*buca_y] != 'c' && campo[*buca_x][*buca_y] != 'p')
        campo[*buca_x][*buca_y]='O';

    /*  Inizializzazione della biglia sul campo. La posizione iniziale del giocatore è casuale
        ma non può corrispondere con quella della buca.  */
    *biglia_x = 1+rand()%48;
    *biglia_y = 1+rand()%48;
    if(campo[*biglia_x][*biglia_y] != '0' && campo[*biglia_x][*biglia_y] != 'c' && campo[*biglia_x][*biglia_y] != 'p' )
        campo[*biglia_x][*biglia_y] = 'B';
}


/* La function cambio_direzione_rand, aumenta ulteriormente la difficoltà del gioco.
   Tale function consente di cambiare casualmente la direzione, scelta dall'utente,
   (in una delle quattro) con una probabilità del 20 %.
   La function restituisce come output uno dei seguenti valori:
   - valore relativo alla direzione, 1, 2, 3, 4:  effettua il cambio direzione;
   - valore -1: non si effettua alcun cambio direzione.
   */
int cambio_direzione_rand()
{
    int cambio_direzione;

    /* N.B !
     * 20% è la probabilità che possa cambiare direzione, il restante 80% viene selta la direzione
     * desiderata dall'utente.
     */
    cambio_direzione = 1+rand()%100;  //  Generazione di un numero casuale nell'insieme (1,2,3,4,..,100)

    /*  Se il numero generato è nell'insieme (1,2,3,4,..,19,20), il programma cambia direzione.
     *  LEGGE DI MOVIMENTO UNIFORME:
     *  - 5% NORD
     *  - 5% EST
     *  - 5% SUD
     *  - 5% OVEST  */

    if(cambio_direzione >= 1 && cambio_direzione <= 5) //  NORD: numero generato compreso tra 1-5
        return 1;
    else if(cambio_direzione >= 6 && cambio_direzione <= 10) //  EST: numero generato compreso tra 6-10
        return 2;
    else if(cambio_direzione >= 11 && cambio_direzione <= 15) //  SUD: numero generato compreso tra 11-15
        return 3;
    else if(cambio_direzione >= 16 && cambio_direzione <= 20) //  OVEST: numero generato compreso tra 15-20
        return 4;
    //  La function restituise il valore convenzionale -1 se il numero generato (cambio_direzione) è maggiore di 20
    return -1;
}


/* La void function move_biglia() ha lo scopo di muovere la biglia sul campo da gioco.
   Per muovere la biglia, la function ha bisogno:
   dati d'input: direzione, dato scalare intero scelto dall'utente.
   dati di inout: pos_x, pos_y: memorizza lo spostamento della biglia. */
void move_biglia(int direzione, int *pos_x, int *pos_y)
{
    int cambio_direzione;

    /* Il predicato dell'if è verificato se la function cambio_direzione_rand  restituisce un valore
    diverso da -1; ciò significa che è avvenuto il cambio di direzione, aggiornando la variabile locale direzione.*/
    if((cambio_direzione = cambio_direzione_rand()) != -1)
    {
        direzione = cambio_direzione;

        printf("\tATTENZIONE! CAMBIO DIREZIONE\n");
        system("pause");
    }

   switch (direzione)
   {
        case 1: //  SPOSTO LA BIGLIA VERSO NORD
            (*pos_x)--;
            break;
       case 2: //  SPOSTO LA BIGLIA VERSO EST
            (*pos_y)++;
            break;
        case 3: //  SPOSTO LA BIGLIA VERSO SUD
            (*pos_x)++;
            break;
        case 4: //  SPOSTO LA BIGLIA VERSO OVEST
            (*pos_y)--;
            break;
   }
}


/* La void function check_biglia() effettua un controllo sulla nuova posizione della biglia, memorizzata
   temporaneamente in pos_x e pos_y.
   La function riceve in input i seguenti parametri:
   - pos_x e pos_y, nei quali è memorizzata la posizione della pedina spostata.
   - tiri, utilizzato per visualizzare il num. di lanci della biglia.
   - biglia_x e biglia_y, sono dati di inout, difatti sono puntatori. */
void check_biglia(char campo[][50], int pos_x, int pos_y, int *biglia_x, int *biglia_y, int tiri)
{
    switch (campo[pos_x][pos_y])
    {
        case 'O': // Se in tale casella si trova la buca principale, il programma termina con successo.
            printf("CONGRATULAZIONI, HAI VINTOOOO :)\n[SCORE: %d ]\n",tiri);
            system("pause");
            exit(0); // EXIT
        case ' ': // Se tale casella è vuota, la biglia si sposta in tale posizione.
            campo[*biglia_x][*biglia_y] = ' '; // inizializzazione del prato nella posizione precedente della biglia.
            *biglia_x = pos_x;  // memoria aggiornata: Salva la nuova posizione dell biglia sul campo.
            *biglia_y = pos_y;
            campo[*biglia_x][*biglia_y] = 'B'; //inizializzazione della pedina nella nuova posizione.
            break;
        case 'p': // Se in tale casella è presente una trappola p, il programma termina: GAME OVER
            printf("GAME-OVER :(\nSEI ENTRATO IN UNA TRAPPOLA !\n");
            printf("[SCORE: %d ]\n",50); // 50 è il punteggio assegnato quando il gioco termina inaspettatamente.
            system("pause");
            exit(0); // EXIT
        case 'c': // Se in tale casella è presente una buca casuale c, il programma genera una nuova posizione per la biglia.
            printf("OPS... !! SEI IN UNA NUOVA POSIZIONE !\n");
            campo[*biglia_x][*biglia_y] = ' ';
            *biglia_x = 1+rand()%48;
            *biglia_y = 1+rand()%48;
            campo[*biglia_x][*biglia_y] = 'B';
            system("pause");
            break;
    }
}

/* Spostando la biglia sul campo, può capitare che essa possa uscire fuori dal campo.
   La void function rimessa_laterale() controlla se la pedina va fuori.
   La procedura rimessa_laterale ha:
   - dati d'input: pos_x e pos_y, sono le posizioni dovute dallo spostamento della biglia.
   - dati di output: *biglia_x o *biglia_y, aggiornamento posizione biglia sul campo.
   Se va fuori viene rimessa in una posizione casuale sul bordo da dove è uscita,
   assegnando a biglia_x o biglia_y (dati di output) un nuovo valore compreso nell'insieme (1,2,3,..,48).
   Ad esempio, se la biglia si sposta e occupa una casella di campo identificata da pos_x = 3 e pos_y = 0,
   significa che la biglia è uscita dal bordo laterale sx.
   Analogamente, se la pedina occupa una casella identificata da pos_x = 49 e pos_y = 20,
   significa che la biglia è uscita dal margine inferiore. */
void rimessa_laterale(char campo[][50], int pos_x, int pos_y, int *biglia_x, int *biglia_y)
{
    if(pos_y == 0 || pos_y == 49)
    {
        printf("BIGLIA FUORI DAL CAMPO, RIMESSA LATERALE IN UNA POSIZIONE CASUALE.\n");
        campo[*biglia_x][*biglia_y] = ' ';
        *biglia_x = 1 + rand() % 48;
        campo[*biglia_x][*biglia_y] = 'B';

        system("pause");
    }
    if(pos_x == 0 || pos_x == 49)
    {
        printf("BIGLIA FUORI DAL CAMPO, RIMESSA LATERALE IN UNA POSIZIONE CASUALE.\n");
        campo[*biglia_x][*biglia_y] = ' ';
        *biglia_y = 1 + rand() % 48;
        campo[*biglia_x][*biglia_y] = 'B';

        system("pause");
    }
}