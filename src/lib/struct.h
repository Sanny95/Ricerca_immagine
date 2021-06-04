/*
 * struct.h
 *
 *  Created on: 23 mag 2021
 *      Author: sasan
 */

#ifndef LIB_STRUCT_H_
#define LIB_STRUCT_H_

#include "librerie.h"

//campi per l'utilizzatore/creatore
typedef struct {

	char username[USERNAME];
	char professione[MAX_STRINGA];
	char pass[PASSWORD_LENGHT];
	char tipo_ut[MAX_STRINGA]; //tipologia di utente (Creatore o Utilizzatore)


} utente_t;

//campi per le risorse
typedef struct {

	char titolo[MAX_STRINGA];
	char nome_file[MAX_STRINGA]; //per nome file si intende il formato delle risorse. EX: .png, .svg, .jpeg
	char tipo[MAX_STRINGA]; //tipologia di immagine
	char parola_chiave[MAX_STRINGA]; //parola chiave
	utente_t creatore; //sottostruttura

} risorse_t;

//campi per statistiche
typedef struct {

	utente_t utilizzatore;
	risorse_t nome_file;
	int valutazione;

} statistiche_t;

FILE *utenti, *risorse, *statistiche;

#endif /* LIB_STRUCT_H_ */
