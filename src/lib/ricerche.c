/*
 * ricerche.c
 *
 *  Created on: 24 mag 2021
 *      Author: sasan
 */

#include "librerie.h"
#include "struct.h"

//effettuo una ricerca  dell'utente all'interno del file
utente_t ricercautente(char username[], char psw[]) {
	utente_t user, tmp = { "", "", "", "" };

	rewind(utenti);
	while (fread(&user, sizeof(utente_t), 1, utenti) == 1) {
		if ((strcmp(user.username, username) == 0)
				&& (strcmp(user.pass, psw) == 0)) {
			tmp = user;
		}
	}

	return tmp;
}

//trovo posizione all'interno del file
int trova_posizione_record(FILE *file, char nome[], char username[]) {
	utente_t tmp_utente;
	risorse_t tmp_ris;
	statistiche_t tmp_stat;
	int pos = 0;

//leggo paramentro per il confronto del nome utente.
	if (file == utenti) {
		rewind(utenti);
		while (fread(&tmp_utente, sizeof(tmp_utente), 1, utenti) == 1) {


			pos = pos + 1;
//confornto del nome utente. Se il nome utente coinciede con il nome presente nel file, viene interotta la ricerca
			if (strcmp(tmp_utente.username, nome) == 0) {
				break;
			}
		}

//confronto nel file le risorse
	} else if (file == risorse) {
		rewind(risorse);
		while (fread(&tmp_ris, sizeof(tmp_ris), 1, risorse) == 1) {
			pos = pos + 1;

			if (strcmp(tmp_ris.titolo, nome) == 0) {
				break;
			}
		}
//confronto nel file le statistiche
	} else if (file == statistiche) {

		rewind(statistiche);
		while (fread(&tmp_stat, sizeof(tmp_stat), 1, statistiche) == 1) {
			pos = pos + 1;

			if ((strcmp(tmp_stat.nome_file.titolo, nome) == 0)
					&& ((strcmp(tmp_stat.utilizzatore.username, username) == 0)
							|| (strcmp(tmp_stat.nome_file.creatore.username,
									username) == 0))) {
				break;
			}
		}
	}

	return pos;
}

risorse_t ricercarisorsa(char titolo[]) {
	risorse_t ris, tmp = { "", "", "", "", { "", "", "", "" } };

	rewind(risorse);
	while (fread(&ris, sizeof(risorse_t), 1, risorse) == 1) {
		if (strcmp(ris.titolo, titolo) == 0) {
			tmp = ris;
		}
	}

	return tmp;
}

statistiche_t ricercastatistica(char titolo[]) {
	statistiche_t stat, tmp = { { "", "", "", "" }, { "", "", "", "", { "", "","", "" } }, 0 };

	rewind(statistiche);
	while (fread(&stat, sizeof(statistiche_t), 1, statistiche) == 1) {
		if (strcmp(stat.nome_file.titolo, titolo) == 0) {
			tmp = stat;
		}
	}

	return tmp;
}
