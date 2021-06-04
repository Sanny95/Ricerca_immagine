/*
 ============================================================================
 Name        : Repository_immagini_esame.c
 Author      : ilenia sasanelli e Raffaella Ricciardi
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include "lib\librerie.h"
#include "lib\struct.h"
#include "lib\grafiche.h"
#include "lib\specifiche.h"
#include "lib\acquisizione.h"

//apertura e creazione dei file
 int main() {

setbuf(stdout, NULL);

    int scelta = 0;

    if(apriFile() == 1) {
        do {
            visualizzaMenuPrincipale();
            scelta = acquisizioneInt();

            if(scelta == 1) {
                registrazioneUtente();
            } else if(scelta == 2) {
                 accedi();
            } else if(scelta == 3) {
                exit(0);
            } else {
                printf("\nOPZIONE NON VALIDA!\n");
                system("pause");
            }
        } while (scelta != 3);

        chiudiFile();
    } else {
        do {
            printf("*** FILE NON TROVATO/I ***\n");
            printf("VUOI PERMETTERE AL PROGRAMMA DI CREARE I FILE NECESSARI?\n "
            		"[1] - SI\n "
            		"[2] - NO --> ");
             scelta = acquisizioneInt();

            if(scelta == 1) {
                printf("CREAZIONE DEI FILE IN CORSO. . .\n");
                creaFile();
                chiudiFile();
                system("pause");
                main();
            } else if(scelta == 2) {
                break;
            } else {
                printf("\nOPZIONE NON VALIDA!\n");
                system("pause");
            }
        } while((scelta != 1) || (scelta != 2));
    }

    return EXIT_SUCCESS;
}
