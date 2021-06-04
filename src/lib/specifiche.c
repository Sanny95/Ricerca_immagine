/*
 * specifiche.c
 *
 *  Created on: 23 mag 2021
 *      Author: sasan
 */

#include "struct.h"
#include "librerie.h"
#include "grafiche.h"
#include "acquisizione.h"
#include "ricerche.h"
#include "specifiche.h"

int apriFile() {
	int esito;

	utenti = fopen("Utenti.dat", "rb+");
	risorse = fopen("Risorse.dat", "rb+");
	statistiche = fopen("Statistiche.dat", "rb+");

	if (utenti == NULL || risorse == NULL || statistiche == NULL) {
		esito = 0;
	} else {
		esito = 1;
	}

	return esito;
}

void creaFile() {
	if (utenti == NULL)
		utenti = fopen("Utenti.dat", "wb+");

	if (risorse == NULL)
		risorse = fopen("Risorse.dat", "wb+");

	if(statistiche == NULL)
		statistiche = fopen("Statistiche.dat", "wb+");
}

void chiudiFile() {

	fclose(utenti);
	fclose(risorse);
	fclose(statistiche);
}

//registrazione utente
void registrazioneUtente() {
    utente_t utente = {"", "", "", ""}; // iniziallizzazione dell'utente per username, professione, tipo_ut e psw
	int scelta = 0;
	int scelta_prof = 0;
	int scelta_tipo = 0;
	char *password = NULL;

	do {
		visualizzaRegistrazioneUtente(); //grafica del menù di registrazione
		scelta = acquisizioneInt();

		if (scelta == 1) {

			fflush(stdin);
			printf("\nInserisci il tuo USERNAME --> ");
			while (acquisizioneSTR(USERNAME, utente.username) == 1) {
				printf("\n LO USERNAME INSERITO E' TROPPO LUNGO. RIPROVA --> ");
			}
//effetuo controllo password
			password = controllo_psw(password);
			strcpy(utente.pass, password);

			do {
				printf("\nScegli la tua professione \n");
				printf(" [1] - Architetto \n");
				printf(" [2] - Web designer \n");
				printf(" [3] - Grafico --> ");
				scelta_prof = acquisizioneInt();

				if (scelta_prof == 1) {
					strcpy(utente.professione, "architetto");
					break;
				} else if (scelta_prof == 2) {
					strcpy(utente.professione, "web designer");
					break;
				} else if (scelta_prof == 3) {
					strcpy(utente.professione, "grafico");
					break;
				} else {
					printf("\nOPZIONE NON VALIDA!\n");
					system("pause");
				}
			} while ((scelta_prof != 1) || (scelta_prof != 2) || (scelta_prof != 3));

			do {
				printf("\nChe utente sei?\n"
						" [1] - utilizzatore\n"
						" [2] - creatore --> ");
				scelta_tipo = acquisizioneInt();

				if (scelta_tipo == 1) {
					strcpy(utente.tipo_ut, "Utilizzatore");
				} else if (scelta_tipo == 2) {
					strcpy(utente.tipo_ut, "Creatore");
				} else {
					printf("\nOpzione non valida!\n");
					system("pause");
				}
			} while (!((scelta_tipo == 1) || (scelta_tipo == 2)));

//visualizzo dati di accesso
			printf("\n*** ACCOUNT CREATO CORRETTAMENTE ***\n"
					"I tuoi dati per l'accesso sono:\n"
					" Username --------> %s\n"
					" Password --> %s\n\n", utente.username, utente.pass);

			fseek(utenti, 0, SEEK_END);
			fwrite(&utente, sizeof(utente), 1, utenti);

			system("pause");

		} else if (scelta == 2) {
			break;
		} else {
			printf("\n Opzione non valida\n");
			system("pause");
		}

	} while (!((scelta == 1) || (scelta == 2)));
}

//accesso dell'utent
void  accedi() {
	utente_t utente;
	int scelta = 0, riprova = 0;

	char psw[PASSWORD_LENGHT];
	char username[USERNAME];

	do {
		visualizzaAccesso(); //grafica menù di accesso
		scelta = acquisizioneInt();

		if (scelta == 1) {
			fflush(stdin);
			printf("\nInserisci il tuo USERNAME --> ");
			while (acquisizioneSTR(USERNAME, username) == 1) {
				printf("\n LO USERNAME INSERITO E' TROPPO LUNGO. RIPROVA --> ");
			}

			fflush(stdin);
			printf("Inserisci la tua PASSWORD --> ");
			while (acquisizioneSTR(PASSWORD_LENGHT, psw) == 1) {
				printf("\n LA PASSWORD INSERITA E' TROPPO LUNGA. RIPROVA --> ");
			}

			utente = ricercautente(username, psw);

			if (strcmp(utente.username, "") == 0) {
				puts("\n********* USERNAME O PASSWORD ERRATI *********");

				do {
					printf("\n Vuoi riprovare? ");
					printf("\n 1) si \n 2) no --> ");
					riprova = acquisizioneInt();

					if (riprova == 1) {
						accedi();
					} else if (riprova == 2) {
						break;
					} else {
						printf("\n\n*** OPZIONE NON VALIDA ***");
					}

				} while (!((riprova == 1) || (riprova == 2)));
			} else {
				printf("\n********* BENVENUTO/A %s *********\n",
						utente.username);
				system("pause");
				menuUtente(utente);
				break;
			}
		} else if (scelta == 2) {
			break;
		} else {
			printf("\n Opzione non valida\n");
			system("pause");
		}
	} while (!((scelta == 1) || (scelta == 2)));


}

//menu utente
void menuUtente(utente_t utente) {

	int scelta = 0;
	risorse_t ris = {"", "", "", "", {"", "", "", ""}};

	if (strcmp(utente.tipo_ut, "Utilizzatore") == 0) {
		do {
			visualizzaMenuUtilizzatore(); //grafica menù utilizzatore
			scelta = acquisizioneInt();

			if (scelta == 1) {
				cercaRisorsa(utente, statistiche, ris);
			} else if (scelta == 2) {
				valutaRisorsa(utente);
			} else if (scelta == 3) {
				modifica_account(utente);
			} else if (scelta == 4) {
				cancella_account(utente);
				exit(0);
			} else if (scelta == 5) {
				exit(0);
			} else {
				printf("\nOPZIONE NON VALIDA\n");
				system("pause");
			}
		} while (scelta != 5);

	} else {
		do {
			visualizzaMenuCreatore();
			scelta = acquisizioneInt();

			if (scelta == 1) {
				gestioneRisorse(risorse, utente, ris);
			} else if (scelta == 2) {
				vediStatistiche(utente);
			} else if (scelta == 3) {
				modifica_account(utente);
			} else if (scelta == 4) {
				cancella_account(utente);
				exit(0);
			} else if (scelta == 5) {
				exit(0);
			} else {
				printf("\nOPZIONE NON VALIDA\n");
				system("pause");
			}
		} while (scelta != 5);
	}
}

//modifica account utente
void modifica_account(utente_t utente) {
	int scelta = 0, posizione = 0, scelta_prof = 0;
	char *psw = NULL;

	posizione = trova_posizione_record(utenti, utente.username, "");

	do {
		//Grafica menù di modifica
		visualizzaModificaAccount();
		scelta = acquisizioneInt();

		switch (scelta) {


		case 1:
			fseek(utenti, (posizione - 1) * sizeof(utente), SEEK_SET);
			fread(&utente, sizeof(utente), 1, utenti);

			puts("\n*** HAI SCELTO DI MODIFICARE IL TUO USERNAME ***");
			printf("Questo e' il tuo vecchio username --> %s", utente.username);

			fflush(stdin);
			printf("\nInserisci il tuo *** nuovo *** USERNAME --> ");
			while (acquisizioneSTR(USERNAME, utente.username) == 1) {
				printf("\n LO USERNAME INSERITO E' TROPPO LUNGO. RIPROVA --> ");
			}

			fseek(utenti, (posizione - 1) * sizeof(utente), SEEK_SET);
			fwrite(&utente, sizeof(utente), 1, utenti);

			printf("\n*** MODIFICA EFFETTUATA CON SUCCESSO ***\n");
			system("pause");
			break;

		case 2:
			fseek(utenti, (posizione - 1) * sizeof(utente), SEEK_SET);
			fread(&utente, sizeof(utente), 1, utenti);

			puts("\n*** HAI SCELTO DI MODIFICARE LA TUA PROFESSIONE ***");
			printf(" Questa e' la tua vecchia professione--> %s ",
					utente.professione);

			fflush(stdin);
			printf("\n Inserisci una *** nuova *** PROFESSIONE\n");

			do {
				printf(" [1] - Architetto \n");
				printf(" [2] - Web designer \n");
				printf(" [3] - Grafico --> ");
				scelta_prof = acquisizioneInt();

				switch (scelta_prof) {

				case 1:
					strcpy(utente.professione, "architetto");
					break;
				case 2:
					strcpy(utente.professione, "web designer");
					break;
				case 3:
					strcpy(utente.professione, "grafico");
					break;
				}
			} while (!((scelta == 1) || (scelta == 2) || (scelta == 3)));

			fseek(utenti, (posizione - 1) * sizeof(utente), SEEK_SET);
			fwrite(&utente, sizeof(utente), 1, utenti);

			printf("\n*** MODIFICA EFFETTUATA CON SUCCESSO ***\n");
			system("pause");
			break;

		case 3:
			fseek(utenti, (posizione - 1) * sizeof(utente), SEEK_SET);
			fread(&utente, sizeof(utente), 1, utenti);

			puts("\n*** HAI SCELTO DI MODIFICARE LA TUA PASSWORD ***");
			printf(" Questa e' la tua vecchia password --> %s \n", utente.pass);

			psw = controllo_psw(psw);
			strcpy(utente.pass, psw);

			fseek(utenti, (posizione - 1) * sizeof(utente), SEEK_SET);
			fwrite(&utente, sizeof(utente), 1, utenti);

			printf("\n*** MODIFICA EFFETTUATA CON SUCCESSO ***\n");
			system("pause");
			break;
		case 4:
			break;
		default:
			printf("\nOPZIONE NON VALIDA\n");
			system("pause");
		}
	} while (scelta != 4);
}

//cancellazione profilo utente
void cancella_account(utente_t utente) {
	int scelta = 0;
	char password[PASSWORD_LENGHT], username[USERNAME];
	risorse_t ris = { "", "", "", "", { "", "", "", "" }};
	statistiche_t statistica = {{"", "", "", ""}, {"", "", "", "", {"", "", "", ""}}, 0};

	//creazione di file temporanei
	FILE *tmp_user, *tmp_ris, *tmp_stat;

	do {
		//grafica cancellazione account
		visualizzaCancellaAccount();
		scelta = acquisizioneInt();

		if (scelta == 1) {
			do {
				system("cls");
				printf("*** PER CONFERMARE LA TUA SCELTA DEVI... ***\n");

				fflush(stdin);
				printf("\nInserire il tuo USERNAME --> ");
				while (acquisizioneSTR(USERNAME, username) == 1) {
					printf("\n LO USERNAME INSERITO E' TROPPO LUNGO. RIPROVA --> ");
				}

				fflush(stdin);
				printf("Inserire la tua password --> ");
				while(acquisizioneSTR(PASSWORD_LENGHT, password) == 1) {
					printf("\n LA PASSWORD INSERITA E' TROPPO LUNGA. RIPROVA --> ");
				}

				//ricerca dell'utente
				utente = ricercautente(username, password);

				if(strcmp(utente.username, "") == 0) {
					puts("\n********* USERNAME O PASSWORD ERRATI *********");
					system("pause");
				}

			// conforno tra due  strighe
			} while(strcmp(utente.username, "") == 0);

			tmp_user = fopen("tmp_user.dat", "wb+");
			tmp_ris = fopen("tmp_ris.dat", "wb+");
			tmp_stat = fopen("tmp_stat.dat", "wb+");

			rewind(risorse);
			while(fread(&ris, sizeof(risorse_t), 1, risorse) == 1) {
				if(strcmp(username, ris.creatore.username) != 0) {
					fwrite(&ris, sizeof(risorse_t), 1, tmp_ris);
				}
			}

			if(strcmp(utente.tipo_ut, "Creatore") == 0) {
				rewind(statistiche);
				while(fread(&statistica, sizeof(statistiche_t), 1, statistiche) == 1) {
					if(strcmp(username, statistica.nome_file.creatore.username) != 0) {
						fwrite(&statistica, sizeof(statistiche_t), 1, tmp_stat);
					}
				}
			} else if(strcmp(utente.tipo_ut, "Utilizzatore") == 0){
				rewind(statistiche);
				while(fread(&statistica, sizeof(statistiche_t), 1, statistiche) == 1) {
					if(strcmp(username, statistica.utilizzatore.username) != 0) {
						fwrite(&statistica, sizeof(statistiche_t), 1, tmp_stat);
					}
				}
			}

			rewind(utenti);
			while(fread(&utente, sizeof(utente_t), 1, utenti) == 1) {
				if(strcmp(utente.pass, password) == 0) {
					printf("\n*** CANCELLAZIONE EFFETTUATA CON SUCCESSO ***\n");
					system("pause");
				} else  {
					fwrite(&utente, sizeof(utente_t), 1, tmp_user);
				}
			}


			fclose(tmp_ris);
			fclose(risorse);
			fclose(tmp_user);
			fclose(utenti);
			fclose(tmp_stat);
			fclose(statistiche);

			remove("Statistiche.dat");
			remove("Utenti.dat");
			remove("Risorse.dat");

			rename("tmp_stat.dat", "Statistiche.dat");
			rename("tmp_ris.dat", "Risorse.dat");
			rename("tmp_user.dat", "Utenti.dat");

		} else if (scelta == 2) {
			break;
		} else {
			printf("\nOPZIONE NON VALIDA\n");
			system("pause");
		}
	} while (!((scelta == 1) || (scelta == 2)));
}

//ricerca delle risorse + download
void cercaRisorsa(utente_t utente, FILE *stat, risorse_t ris) {
    statistiche_t statistica = {{"", "", "", ""}, {"", "", "", "", {"", "", "", ""}}, 0};
	char ricerca[MAX_STRINGA] = {""};
	int scelta = 0, trovato = 0, scarica = 0;

	do {
        //grafica ricerca risorsa
		visualizzaCercaRisorsa();
		scelta = acquisizioneInt();

//ricerca della risorsa per titolo
		if(scelta == 1) {
			printf("\n\n***** CERCA PER TITOLO *****");
			printf("\nTitolo da cercare --> ");

			fflush(stdin);
			while (acquisizioneSTR(MAX_STRINGA, ricerca) == 1) {
				printf("\n IL TITOLO  INSERITO E' TROPPO LUNGO. RIPROVA --> ");
			}

			printf("+----------------+----------------+------------+-------------+\n");
			printf("|%-15s |%-15s |%-11s |%-10s|", "Titolo", "Nome", "Tipo", "Parola chiave");
			printf("\n+----------------+----------------+------------+-------------+");

			rewind(risorse);

//La funzione feof ritorna 0 se non è stata raggiunta la fine del file, altrimenti restituisce un valore logico.
			while(!feof(risorse) && fread(&ris, sizeof(risorse_t), 1, risorse) == 1){

//La funzione strncmp() limita il confronto fra le due stringhe  piu'  n caratteri.
				if(strncmp(ricerca, ris.titolo, (strlen(ricerca))) == 0) {

					printf("\n|%-15s |%-15s |%-11s |%-13s|", ris.titolo, ris.nome_file, ris.tipo, ris.parola_chiave);
					printf("\n+----------------+----------------+------------+-------------+");
					trovato = 1;
				}
			}

			if(trovato == 0) {
				printf("\n\nCI DISPIACE, MA LA RICERCA NON HA PRODOTTO ALCUN RISULTATO\n");
			} else {
				printf("\nVuoi scaricare una delle risorse?\n"
						" [1] - SI\n"
						" [2] - NO --> ");

//download delle risorse per titolo
				scarica = acquisizioneInt();

				if(scarica == 1) {
					do {
						fflush(stdin);
						printf("\nInserisci il TITOLO della risorsa da scaricare  --> ");
						while (acquisizioneSTR(MAX_STRINGA, ricerca) == 1) {
							printf("\n IL TITOLO  INSERITO E' TROPPO LUNGO. RIPROVA --> ");
						}

						ris = ricercarisorsa(ricerca);

						if(strcmp(ris.titolo, "") == 0) {
							printf("*** NON ESISTE NESSUNA RISORSA CON QUESTO TITOLO ***\n");
						}
					} while(strcmp(ris.titolo, "") == 0);

					statistica.utilizzatore = utente;
					statistica.nome_file = ris;

					fseek(statistiche, 0, SEEK_END);
					fwrite(&statistica, sizeof(statistica), 1, statistiche);

					printf("*** DOWNLOAD EFFETTUATO CON SUCCESSO ***\n");

				} else if(scarica == 2) {
					break;
				} else {
					printf("\nOPZIONE NON VALIDA\n");
					system("pause");
				}
			}

			puts("");
			system("pause");

//ricerca tipologia di risorsa
		} else if(scelta == 2) {
			printf("\n\n***** CERCA PER TIPO *****");
			printf("\nScegli tra Vettoriale, Grafica, Fotografica.\n");
			printf("\n Scrivere il Tipo da cercare --> ");

			fflush(stdin);
			while (acquisizioneSTR(MAX_STRINGA, ricerca) == 1) {
				printf("\n IL TIPO  INSERITO E' TROPPO LUNGO. RIPROVA --> ");
			}
//toupper conversione dei caratteri da minuscoi a maiuscoli
			ricerca[0] = toupper(ricerca[0]);

			printf("+----------------+----------------+------------+-------------+\n");
			printf("|%-15s |%-15s |%-11s |%-10s|", "Titolo", "Nome", "Tipo", "Parola chiave");
			printf("\n+----------------+----------------+------------+-------------+");

			rewind(risorse);
			while(fread(&ris, sizeof(risorse_t), 1, risorse) == 1){
				if(strncmp(ricerca, ris.tipo, (strlen(ricerca))) == 0) {
					printf("\n|%-15s |%-15s |%-11s |%-13s|", ris.titolo, ris.nome_file, ris.tipo, ris.parola_chiave);
					printf("\n+----------------+----------------+------------+-------------+");
					trovato = 1;
				}
			}

			if(trovato == 0) {
				printf("\n\nCI DISPIACE, MA LA RICERCA NON HA PRODOTTO ALCUN RISULTATO\n");

//Download delle risorse per tipologia
			} else {
				printf("\nVuoi scaricare una delle risorse?\n"
						" [1] - SI\n"
						" [2] - NO --> ");
				scarica = acquisizioneInt();

				if(scarica == 1) {
					do {
						fflush(stdin);
						printf("\nInserisci il TITOLO della risorsa da scaricare  --> ");
						while (acquisizioneSTR(MAX_STRINGA, ricerca) == 1) {
							printf("\n IL TITOLO  INSERITO E' TROPPO LUNGO. RIPROVA --> ");
						}

						ris = ricercarisorsa(ricerca);

						if(strcmp(ris.titolo, "") == 0) {
							printf("*** NON ESISTE NESSUNA RISORSA CON QUESTO TITOLO ***\n");
						}
					} while(strcmp(ris.titolo, "") == 0);


					statistica.utilizzatore = utente;
					statistica.nome_file = ris;

					fseek(statistiche, 0, SEEK_END);
					fwrite(&statistica, sizeof(statistica), 1, statistiche);

					printf("*** DOWNLOAD EFFETTUATO CON SUCCESSO ***\n");

				} else if(scarica == 2) {
					break;
				} else {
					printf("\nOPZIONE NON VALIDA\n");
					system("pause");
				}
			}

			puts("");
			system("pause");

//ricerca della risorsa per parola chiave
		} else if(scelta == 3) {
			printf("\n\n***** CERCA PER PAROLA CHIAVE *****");
			printf("\nParola chiave da cercare --> ");

			fflush(stdin);
			while (acquisizioneSTR(MAX_STRINGA, ricerca) == 1) {
				printf("\n IL TIPO  INSERITO E' TROPPO LUNGO. RIPROVA --> ");
			}

			printf("+----------------+----------------+------------+-------------+\n");
			printf("|%-15s |%-15s |%-11s |%-10s|", "Titolo", "Nome", "Tipo", "Parola chiave");
			printf("\n+----------------+----------------+------------+-------------+");

			rewind(risorse);
			while(fread(&ris, sizeof(risorse_t), 1, risorse) == 1){
				if(strncmp(ricerca, ris.parola_chiave, (strlen(ricerca))) == 0) {
					printf("\n|%-15s |%-15s |%-11s |%-13s|", ris.titolo, ris.nome_file, ris.tipo, ris.parola_chiave);
					printf("\n+----------------+----------------+------------+-------------+");
					trovato = 1;
				}
			}

			if(trovato == 0) {
				printf("\n\nCI DISPIACE, MA LA RICERCA NON HA PRODOTTO ALCUN RISULTATO\n");
			} else {
//Download delle risorse per parola chiave
				printf("\nVuoi scaricare una delle risorse?\n"
						" [1] - SI\n"
						" [2] - NO --> ");


				scarica = acquisizioneInt();

				if(scarica == 1) {
					do {
						fflush(stdin);
						printf("\nInserisci il TITOLO della risorsa da scaricare  --> ");
						while (acquisizioneSTR(MAX_STRINGA, ricerca) == 1) {
							printf("\n IL TITOLO  INSERITO E' TROPPO LUNGO. RIPROVA --> ");
						}

						ris = ricercarisorsa(ricerca);

						if(strcmp(ris.titolo, "") == 0) {
							printf("*** NON ESISTE NESSUNA RISORSA CON QUESTO TITOLO ***\n");
						}
					} while(strcmp(ris.titolo, "") == 0);

					statistica.utilizzatore = utente;
					statistica.nome_file = ris;

					fseek(statistiche, 0, SEEK_END);
					fwrite(&statistica, sizeof(statistica), 1, statistiche);

					printf("*** DOWNLOAD EFFETTUATO CON SUCCESSO ***\n");

				} else if(scarica == 2) {
					break;
				} else {
					printf("\nOPZIONE NON VALIDA\n");
					system("pause");
				}
			}
			puts("");
			system("pause");
		} else if(scelta == 4) {
			break;
		} else {
			printf("\nOPZIONE NON VALIDA\n");
			system("pause");
		}
	} while(scelta != 4);

}

//valutazione delle risorse
void valutaRisorsa(utente_t utente) {

  statistiche_t stat = {{"", "", "", ""}, {"", "", "", "", {"", "", "", ""}}, 0};
	int scelta = 0, trovato = 0, pos = 0;
	char titolo[MAX_STRINGA] = {""};


	rewind(statistiche);
	while (fread(&stat, sizeof(statistiche_t), 1, statistiche) == 1) {
		if(strcmp(utente.username, stat.utilizzatore.username) == 0) {
			trovato = 1;

			do{
				visualizzaValutaRisorsa();
				scelta = acquisizioneInt();

				if(scelta == 1) {

					printf("\nQueste sono le risorse che hai scaricato:\n");

					rewind(statistiche);

					 while (fread(&stat, sizeof(statistiche_t), 1, statistiche) == 1) {
						if (!feof(statistiche)) {
							if (strcmp(utente.username,
									stat.utilizzatore.username) == 0) {
								printf("TITOLO --> %s\t VALUTAZIONE --> ",
										stat.nome_file.titolo);

								if (stat.valutazione == 0) {
									printf("NON ANCORA VALUTATO\n\n");
								} else {
									printf("%d\n\n", stat.valutazione);
								}
							}
						}
					}


					do {

						fflush(stdin);
						printf("\nInserisci il TITOLO della risorsa da valutare --> ");
						while (acquisizioneSTR(MAX_STRINGA, titolo) == 1) {
							printf("\n IL TITOLO  INSERITO E' TROPPO LUNGO. RIPROVA --> ");

						}
						stat = ricercastatistica(titolo);

						if(strcmp(stat.nome_file.titolo, "") == 0) {
							printf("*** NON HAI SCARICATO NESSUNA RISORSA CON QUESTO TITOLO ***\n");
						}
					} while((strcmp(stat.nome_file.titolo, "") == 0));

					pos = trova_posizione_record(statistiche, titolo, utente.username);

					printf("Inserisci una valutazione tra %d e %d --> ", MIN_VAL, MAX_VAL);


					do {
						stat.valutazione = acquisizioneInt();

						if((stat.valutazione < MIN_VAL) || (stat.valutazione > MAX_VAL)) {
							printf("*** LA VALUTAZIONE INSERITA SUPERA I PARAMETRI MASSIMI/MINIMI ***\n");
							printf("RIPROVA --> ");
						}
					} while((stat.valutazione < MIN_VAL) || (stat.valutazione > MAX_VAL));

					fseek(statistiche, (pos-1) * sizeof(statistiche_t), SEEK_SET);
					fwrite(&stat, sizeof(stat), 1, statistiche);
					fflush(statistiche);

					printf("\n*** VALUTAZIONE INSERITA CORRETTAMENTE ***\n");
					system("pause");

				} else if(scelta == 2) {
					break;
				} else {
					printf("\nOPZIONE NON VALIDA\n");
					system("pause");
				}
			} while(!((scelta == 1) || (scelta == 2)));
		}
	}

	if(trovato == 0) {
		printf("*** NON HAI ANCORA SCARICATO NESSUNA RISORSA ***\n");
		system("pause");
	}
}

//visualizzazione statistiche
void vediStatistiche(utente_t creatore) {
	int trovato = 0, n_vet = 0, n_graf = 0, n_foto = 0, n_down = 0;
	char titolo[MAX_STRINGA];
	risorse_t ris = { "", "", "", "", { "", "", "", "" }};
	statistiche_t stat = {{"", "", "", ""}, {"", "", "", "", {"", "", "", ""}}, 0};

	rewind(risorse);
	while (fread(&ris, sizeof(risorse_t), 1, risorse) == 1) {
		if(strcmp(creatore.username, ris.creatore.username) == 0) {
			trovato = 1;

			system("cls");

			printf("+-----------------------------------------------+\n");
			printf("|              Visualizza Statistiche           |\n");
			printf("+-----------------------------------------------+\n\n");


			rewind(risorse);
			while (fread(&ris, sizeof(risorse_t), 1, risorse) == 1) {
				if(strcmp(creatore.username, ris.creatore.username) == 0) {
					if(strcmp(ris.tipo, "Vettoriale") == 0) {
						n_vet = n_vet + 1;
					} else if(strcmp(ris.tipo, "Grafica") == 0) {
						n_graf = n_graf + 1;
					} else if(strcmp(ris.tipo, "Fotografica") == 0) {
						n_foto = n_foto + 1;
					}
				}
			}

			printf("Hai inserito complessivamente\n"
					" %d immagini di tipo vettoriale\n"
					" %d immagini di tipo grafico\n"
					" %d immagini di tipo fotografico\n\n", n_vet, n_graf, n_foto);

			printf("*** PER VEDERE IL NUMERO DI DOWNLOAD E LE VALUTAZIONI \n"
					"INSERISCI IL NOME DI UNA DELLE RISORSE ELENCATE DI SEGUITO ***\n\n");
			rewind(risorse);
			while(fread(&ris, sizeof(risorse_t), 1, risorse) == 1){
				if(strcmp(creatore.username, ris.creatore.username) == 0) {
					printf("\n| TITOLO | %-15s |"
							"\n| TIPO   | %-15s |", ris.titolo, ris.tipo);
					printf("\n+--------+-----------------+");

				}
			}

			do {
				fflush(stdin);
				printf("\nInserisci il TITOLO della risorsa da visualizzare  --> ");
				while (acquisizioneSTR(MAX_STRINGA, titolo) == 1) {
					printf("\n IL TITOLO  INSERITO E' TROPPO LUNGO. RIPROVA --> ");
				}

				ris = ricercarisorsa(titolo);

				if(strcmp(ris.titolo, "") == 0) {
					printf("*** NON HAI INSERITO NESSUNA RISORSA CON QUESTO TITOLO ***\n");
				}
			} while(strcmp(ris.titolo, "") == 0);

			rewind(statistiche);
			while (fread(&stat, sizeof(statistiche_t), 1, statistiche) == 1) {
				if((strcmp(creatore.username, stat.nome_file.creatore.username) == 0) &&
						(strcmp(ris.titolo, stat.nome_file.titolo) == 0)) {
					n_down = n_down + 1;
				}
			}

			if(n_down == 0) {
				printf("*** LA RISORSA NON E' ANCORA STATA SCARICATA DA NESSUNO ***");
			} else {
				printf("\n\nLa risorsa chiamata *** %s *** ha ottenuto %d download.\n"
						"Le valutazioni sono:\n", titolo, n_down);

				rewind(statistiche);
				while (fread(&stat, sizeof(statistiche_t), 1, statistiche) == 1) {
					if(strcmp(creatore.username, stat.nome_file.creatore.username) == 0) {
						if(strcmp(ris.titolo, stat.nome_file.titolo) == 0) {
							if(stat.valutazione != 0) {
								printf("Utente %s ha valutato con %d.\n", stat.utilizzatore.username, stat.valutazione);
							}
						}
					}
				}
			}
		}
	}

	if(trovato == 0) {
		printf("*** NON E' STATO POSSIBILE TROVARE NESSUNA RISORSA INSERITA DA %s ***\n", creatore.username);
	}
	puts("");
	system("pause");
}

//gestione delle risorse
void gestioneRisorse(FILE *risorse, utente_t creatore, risorse_t ris) {
	int scelta = 0;

	do {
		visualizzaGestioneRisorsa();
		scelta = acquisizioneInt();

		if (scelta == 1) {
			aggiungiRisorsa(risorse, creatore);
		} else if (scelta == 2) {
			visualizzaRisorse(risorse, creatore, ris);
		} else if (scelta == 3) {
			modifica_risorsa(creatore, ris);
		} else if (scelta == 4) {
			cancellazioneRisorsa(creatore, ris);
		} else if (scelta == 5) {
			break;
		} else {
			printf("\nOPZIONE NON VALIDA\n");
			system("pause");
		}
	} while (scelta != 5);
}

//inserimento delle risorse
void aggiungiRisorsa(FILE *risorse, utente_t creatore) {
	risorse_t ris = { "", "", "", "", { "", "", "", "" }};
	int scelta = 0, scelta_tipologia = 0;

	risorse = fopen("Risorse.dat", "r+b");

	do {
		visualizzaAggiungiRisorsa();

		fflush(stdin);
		printf("\nInserisci il TITOLO della risorsa  --> ");
		while (acquisizioneSTR(MAX_STRINGA, ris.titolo) == 1) {
			printf("\n IL TITOLO  INSERITO E' TROPPO LUNGO. RIPROVA --> ");
		}

//La funzione strcpy() copia la stringa
		strcpy(ris.nome_file, ris.titolo);

		do {
			printf("\nScegli la TIPOLOGIA della risorsa \n");
			printf(" [1] - Vettoriale \n");
			printf(" [2] - Grafica \n");
			printf(" [3] - Fotografica--> ");
			scelta_tipologia = acquisizioneInt();

			if (scelta_tipologia == 1) {
				strcpy(ris.tipo, "Vettoriale");
				strcat(ris.nome_file, ".svg"); //effettuo,con la  strcat(),una concatenazione di stringa
				break;
			} else if (scelta_tipologia == 2) {
				strcpy(ris.tipo, "Grafica");
				strcat(ris.nome_file, ".png"); //concatenazione di stringa
				break;
			} else if (scelta_tipologia == 3) {
				strcpy(ris.tipo, "Fotografica");
				strcat(ris.nome_file, ".jpg"); //concatenazione di stringa
				break;
			} else {
				printf("\nOPZIONE NON VALIDA!\n");
				system("pause");
			}
		} while ((scelta_tipologia != 1) || (scelta_tipologia != 2) || (scelta_tipologia != 3));

		fflush(stdin);
		printf("\nInserisci la PAROLA CHIAVE della risorsa  --> ");
		while (acquisizioneSTR(MAX_STRINGA, ris.parola_chiave) == 1) {
			printf("\n LA PAROLA CHIAVE INSERITA E' TROPPO LUNGO. RIPROVA --> ");
		}

		ris.creatore = creatore;

		printf("\n*** RISORSA CREATA CORRETTAMENTE ***\n");

		fseek(risorse, 0, SEEK_END);
		fwrite(&ris, sizeof(ris), 1, risorse);

		printf("Vuoi inserire un'altra risorsa?\n"
				" [1] - Si\n"
				" [2] - No --> ");
		scelta = acquisizioneInt();

	} while (scelta == 1);

	fclose(risorse);
}

//modifica delle risorse
void modifica_risorsa(utente_t creatore, risorse_t ris) {
	int scelta = 0, trovato = 0, pos = 0, scelta_tipologia = 0;
	char titolo[MAX_STRINGA];

	rewind(risorse);
	while (fread(&ris, sizeof(risorse_t), 1, risorse) == 1) {
		if(strcmp(creatore.username, ris.creatore.username) == 0) {
			trovato = 1;

			system("cls");

			printf("+-----------------------------------------------+\n");
			printf("|                Modifica risorse               |\n");
			printf("+-----------------------------------------------+\n\n");

			rewind(risorse);
			while (fread(&ris, sizeof(risorse_t), 1, risorse) == 1) {
				if(strcmp(creatore.username, ris.creatore.username) == 0) {
					printf("\nTITOLO --> %s\n", ris.titolo);
				}
			}

			do {
				fflush(stdin);
				printf("\nInserisci il TITOLO della risorsa da modificare  --> ");
				while (acquisizioneSTR(MAX_STRINGA, titolo) == 1) {
					printf("\n IL TITOLO  INSERITO E' TROPPO LUNGO. RIPROVA --> ");
				}

				ris = ricercarisorsa(titolo);

				if(strcmp(ris.titolo, "") == 0) {
					printf("*** NON HAI INSERITO NESSUNA RISORSA CON QUESTO TITOLO ***\n");
				}
			} while(strcmp(ris.titolo, "") == 0);

			pos = trova_posizione_record(risorse, titolo, "");

			do {
				visualizzaModificaRisorsa();
				scelta = acquisizioneInt();

				if(scelta == 1) {
					fseek(risorse, (pos - 1) * sizeof(ris), SEEK_SET);
					fread(&ris, sizeof(ris), 1, risorse);

					puts("\n*** HAI SCELTO DI MODIFICARE IL TITOLO ***");
					printf("Questo e' il vecchio titolo --> %s", ris.titolo);

					fflush(stdin);
					printf("\nInserisci il *** nuovo *** titolo --> ");
					while (acquisizioneSTR(MAX_STRINGA, ris.titolo) == 1) {
						printf("\n IL TITOLO  INSERITO E' TROPPO LUNGO. RIPROVA --> ");
					}

					if(strcmp(ris.tipo, "Vettoriale") == 0) {
						strcpy(ris.nome_file, ris.titolo);
						strcat(ris.nome_file, ".svg");

					} else if(strcmp(ris.tipo, "Grafica") == 0) {
						strcpy(ris.nome_file, ris.titolo);
						strcat(ris.nome_file, ".png");

					} else if(strcmp(ris.tipo, "Fotografica") == 0) {
						strcpy(ris.nome_file, ris.titolo);
						strcat(ris.nome_file, ".jpg");
					}

					fseek(risorse, (pos - 1) * sizeof(ris), SEEK_SET);
					fwrite(&ris, sizeof(ris), 1, risorse);

					printf("\n*** MODIFICA EFFETTUATA CON SUCCESSO ***\n");
					system("pause");
					break;

				} else if(scelta == 2) {
					fseek(risorse, (pos - 1) * sizeof(ris), SEEK_SET);
					fread(&ris, sizeof(ris), 1, risorse);

					puts("\n*** HAI SCELTO DI MODIFICARE LA TIPOLOGIA***");
					printf("Questo e' la vecchia tipologia --> %s", ris.tipo);

					do {
						printf("\nScegli la TIPOLOGIA della risorsa \n");
						printf(" [1] - Vettoriale \n");
						printf(" [2] - Grafica \n");
						printf(" [3] - Fotografica--> ");
						scelta_tipologia = acquisizioneInt();

						if (scelta_tipologia == 1) {
							strcpy(ris.tipo, "Vettoriale");
							strcpy(strstr(ris.nome_file,"."), ".svg"); //implemento strstr per restituisce un puntatore alla prima occorrenza
							break;
						} else if (scelta_tipologia == 2) {
							strcpy(ris.tipo, "Grafica");
							strcpy(strstr(ris.nome_file,"."), ".png");
							break;
						} else if (scelta_tipologia == 3) {
							strcpy(ris.tipo, "Fotografica");
							strcpy(strstr(ris.nome_file,"."), ".jpg");
							break;
						} else {
							printf("\nOPZIONE NON VALIDA!\n");
							system("pause");
						}
					} while ((scelta_tipologia != 1) || (scelta_tipologia != 2) || (scelta_tipologia != 3));


					fseek(risorse, (pos - 1) * sizeof(ris), SEEK_SET);
					fwrite(&ris, sizeof(ris), 1,risorse );

					printf("\n*** MODIFICA EFFETTUATA CON SUCCESSO ***\n");
					system("pause");
					break;

				} else if(scelta == 3) {
					fseek(risorse, (pos - 1) * sizeof(ris), SEEK_SET);
					fread(&ris, sizeof(ris), 1, risorse);

					puts("\n*** HAI SCELTO DI MODIFICARE LA PAROLA CHIAVE***");
					printf("Questo e' la vecchia parola chiave  --> %s", ris.parola_chiave);

					fflush(stdin);
					printf("\nInserisci il PAROLA CHIAVE della risorsa  --> ");
					while (acquisizioneSTR(MAX_STRINGA, ris.parola_chiave) == 1) {
						printf("\n LA PAROLA CHIAVE  INSERITA E' TROPPO LUNGA. RIPROVA --> ");
					}

					fseek(risorse, (pos - 1) * sizeof(ris), SEEK_SET);
					fwrite(&ris, sizeof(ris), 1, risorse);

					printf("\n*** MODIFICA EFFETTUATA CON SUCCESSO ***\n");
					system("pause");
					break;

				} else if(scelta == 4) {
					break;
				} else {
					printf("\nOPZIONE NON VALIDA\n");
					system("pause");
				}
			} while(scelta != 4);
			break;
		}

	}

	if(trovato == 0) {
		printf("*** NON E' STATO POSSIBILE TROVARE NESSUNA RISORSA INSERITA DA %s ***\n", creatore.username);
		system("pause");
	}
}

//cancellazione delle risorse
void cancellazioneRisorsa(utente_t creatore, risorse_t ris){
	int scelta = 0, trovato = 0;
	char titolo[MAX_STRINGA];
	FILE *tmp;

	rewind(risorse);
	while (fread(&ris, sizeof(risorse_t), 1, risorse) == 1) {
		if(strcmp(creatore.username, ris.creatore.username) == 0) {
			trovato = 1;
			do {
				visualizzaCancellaRisorsa();
				scelta = acquisizioneInt();

				if (scelta == 1) {
					rewind(risorse);
					while (fread(&ris, sizeof(risorse_t), 1, risorse) == 1) {
						if(strcmp(creatore.username, ris.creatore.username) == 0) {
							printf("\nTITOLO --> %s\n", ris.titolo);
						}
					}

					do {
						fflush(stdin);
						printf("\nInserisci il TITOLO della risorsa da cancellare  --> ");
						while (acquisizioneSTR(MAX_STRINGA, titolo) == 1) {
							printf("\n IL TITOLO  INSERITO E' TROPPO LUNGO. RIPROVA --> ");
						}

						ris = ricercarisorsa(titolo);

						if(strcmp(ris.titolo, "") == 0) {
							printf("*** NON HAI INSERITO NESSUNA RISORSA CON QUESTO TITOLO ***\n");
						}
					} while(strcmp(ris.titolo, "") == 0);

					tmp = fopen("tmp.dat", "wb+");

					rewind(risorse);
					while(fread(&ris, sizeof(risorse_t), 1, risorse) == 1) {
						if((strcmp(ris.titolo, titolo) == 0) && (strcmp(ris.creatore.username, creatore.username) == 0)) {
							printf("\n*** CANCELLAZIONE EFFETTUATA CON SUCCESSO ***\n");
							system("pause");
					    } else  {
					    	fwrite(&ris, sizeof(risorse_t), 1, tmp);
					    }
					}

				    fclose(risorse);
				    fclose(tmp);

				    remove("Risorse.dat");
				    rename("tmp.dat","Risorse.dat"); //rinominazione del file temporaneo

					risorse = fopen("Risorse.dat", "rb+");

				} else if (scelta == 2) {
					break;
				} else {
					printf("\nOPZIONE NON VALIDA\n");
					system("pause");
				}

			} while (!((scelta == 1) || (scelta == 2)));
		}
	}

	if(trovato == 0) {
		printf("*** NON E' STATO POSSIBILE TROVARE NESSUNA RISORSA INSERITA DA %s ***\n", creatore.username);
		system("pause");
	}
}
