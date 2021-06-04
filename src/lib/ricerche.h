/*
 * ricerche.h
 *
 *  Created on: 24 mag 2021
 *      Author: sasan
 */

#ifndef LIB_RICERCHE_H_
#define LIB_RICERCHE_H_

utente_t ricercautente(char*, char*);
int trova_posizione_record(FILE*,char*, char*);
risorse_t ricercarisorsa(char *);
statistiche_t ricercastatistica(char *);

#endif /* LIB_RICERCHE_H_ */
