/*
 * grafiche.c
 *
 *  Created on: 23 mag 2021
 *      Author: sasan
 */

#include "struct.h"

void visualizzaMenuPrincipale() {
	system("cls");

	printf("+-----------------------------------------------+\n");
	printf("|                Benvenuto nel sistema          |\n");
	printf("+-----------------------------------------------+\n\n");

	printf("+-----------------------------------------------+\n");
	printf("|                   MENU PRINCIPALE             |\n");
	printf("+---+-------------------+---+-------------------+\n");
	printf("| 1)| Registrati        | 3)| Esci              |\n");
	printf("| 2)| Accedi            |   |                   |\n");
	printf("+---+-------------------+---+-------------------+\n\n");
	printf("Scegli un'opzione --> ");
}

void visualizzaRegistrazioneUtente() {
	system("cls");

	printf("+-----------------------------------------------+\n");
	printf("|                  Registrazione                |\n");
	printf("+-----------------------------------------------+\n\n");
	printf("Sei nuovo qui?\n"
			" [1] - Si\n"
			" [2] - Indietro --> ");
}

void visualizzaAccesso() {
	system("cls");

	printf("+-----------------------------------------------+\n");
	printf("|                     Accesso                   |\n");
	printf("+-----------------------------------------------+\n\n");
	printf("Hai gia' un account?\n"
			" [1] - Si\n"
			" [2] - Indietro --> ");
}

void visualizzaMenuUtilizzatore() {
	system("cls");

	printf("+------------------------------------------------+\n");
	printf("|                  MENU UTILIZZATORE             |\n");
	printf("+---+--------------------+---+-------------------+\n");
	printf("| 1)| Ricerca risorse    | 4)| Cancella account  |\n");
	printf("| 2)| Valuta una risorsa | 5)| Esci              |\n");
	printf("| 3)| Modifica account   |   |                   |\n");
	printf("+---+--------------------+---+-------------------+\n\n");
	printf("Scegli un'opzione --> ");
}

void visualizzaMenuCreatore() {
	system("cls");

	printf("+------------------------------------------------+\n");
	printf("|                    MENU CREATORE               |\n");
	printf("+---+--------------------+---+-------------------+\n");
	printf("| 1)| Gestisci risorse   | 4)| Cancella Account  |\n");
	printf("| 2)| Vedi statistiche   | 5)| Esci              |\n");
	printf("| 3)| Modifica Account   |   |                   |\n");
	printf("+---+--------------------+---+-------------------+\n\n");
	printf("Scegli un'opzione --> ");
}

void visualizzaModificaAccount() {
	system("cls");

	printf("+------------------------------------------------+\n");
	printf("|                  Modifica account              |\n");
	printf("+---+--------------------+---+-------------------+\n");
	printf("| 1)| USERNAME           | 3)| PASSWORD          |\n");
	printf("| 2)| PROFESSIONE        | 4)| INDIETRO          |\n");
	printf("+---+--------------------+---+-------------------+\n\n");
	printf("Scegli un'opzione --> ");
}

void visualizzaCancellaAccount() {
	system("cls");

	printf("+-----------------------------------------------+\n");
	printf("|                Cancella account               |\n");
	printf("+-----------------------------------------------+\n\n");

	printf("Sei sicuro di voler cancellare il tuo account?\n"
			"Una volta cancellato non si puo' più recuperare \n"
			" [1] - Cancella\n"
			" [2] - Indietro \n ");
}

void visualizzaCercaRisorsa() {
	system("cls");

	printf("+------------------------------------------------+\n");
	printf("|                  Ricerca Risorsa               |\n");
	printf("+---+--------------------+---+-------------------+\n");
	printf("| 1)| Titolo             | 3)| Parola chiave     |\n");
	printf("| 2)| Tipo               | 4)| Indietro          |\n");
	printf("+---+--------------------+---+-------------------+\n\n");
	printf("Scegli un'opzione --> ");
}

void visualizzaValutaRisorsa() {
	system("cls");

	printf("+-----------------------------------------------+\n");
	printf("|             Valutazione Risorsa               |\n");
	printf("+-----------------------------------------------+\n\n");
	printf("Vuoi valutare una risorsa?\n"
			" [1] - SI\n"
			" [2] - NO --> ");
}

void visualizzaGestioneRisorsa() {
	system("cls");

	printf("+------------------------------------------------+\n");
	printf("|                  Gestione Risorsa              |\n");
	printf("+---+--------------------+---+-------------------+\n");
	printf("| 1)| Aggiungi risorsa   | 4)| Cancella risorsa  |\n");
	printf("| 2)| Visualizza risorsa | 5)| Indietro          |\n");
	printf("| 3)| Modifica risorsa   |   |                   |\n");
	printf("+---+--------------------+---+-------------------+\n\n");
	printf("Scegli un'opzione --> ");
}

void visualizzaAggiungiRisorsa() {
	system("cls");

	printf("+-----------------------------------------------+\n");
	printf("|               Aggiiungi Risorsa               |\n");
	printf("+-----------------------------------------------+\n\n");
}

void visualizzaRisorse(FILE *risorse, utente_t creatore, risorse_t ris) {
	int trovato = 0;

	system("cls");

	printf("+-----------------------------------------------+\n");
	printf("|               Visualizza risorse              |\n");
	printf("+-----------------------------------------------+\n\n");

	rewind(risorse);
	while (fread(&ris, sizeof(risorse_t), 1, risorse) == 1) {
		if (strcmp(ris.creatore.username, creatore.username) == 0) {
			printf("\nTITOLO --> %s\n"
					"NOME -------> %s\n"
					"TIPO ------> %s\n"
					"PAROLA CHIAVE --> %s\n\n", ris.titolo, ris.nome_file,ris.tipo, ris.parola_chiave);
			trovato = 1;
		}
	}

	if(trovato == 0) {
		printf("*** NON E' STATO POSSIBILE TROVARE NESSUNA RISORSA INSERITA DA %s ***\n", creatore.username);
	}

	system("pause");
}

void visualizzaModificaRisorsa() {
	system("cls");

	printf("+------------------------------------------------+\n");
	printf("|                  Modifica Risorsa              |\n");
	printf("+---+--------------------+---+-------------------+\n");
	printf("| 1)| TITOLO             | 3)| PAROLA CHIAVE     |\n");
	printf("| 2)| TIPOLOGIA          | 4)| INDIETRO          |\n");
	printf("+---+--------------------+---+-------------------+\n\n");
	printf("Scegli un'opzione --> ");
}

void visualizzaCancellaRisorsa() {
	system("cls");

	printf("+-----------------------------------------------+\n");
	printf("|               Cancellazione risorsa           |\n");
	printf("+-----------------------------------------------+\n\n");

	printf("Sei sicuro di voler cancellare la risorsa?\n"
			"Una volta cancellato non si puo' piu' recuperare \n"
			" [1] - Cancella\n"
			" [2] - Indietro --> ");
}
