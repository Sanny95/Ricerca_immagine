/*
 * specifiche.h
 *
 *  Created on: 23 mag 2021
 *      Author: sasan
 */

#ifndef LIB_SPEC_SPECIFICHE_H_
#define LIB_SPEC_SPECIFICHE_H_

//FILE
int apriFile();
void creaFile();
void chiudiFile();

//UTILIZZATORE/CREATORE
void registrazioneUtente();
void accedi();
void menuUtente(utente_t);
void modifica_account(utente_t);
void cancella_account(utente_t);

void cercaRisorsa(utente_t, FILE*, risorse_t);
void valutaRisorsa(utente_t);
void vediStatistiche(utente_t);

//RISORSE
void gestioneRisorse(FILE*, utente_t, risorse_t);
void aggiungiRisorsa(FILE*, utente_t);
void visualizzaRisorse(FILE*, utente_t, risorse_t);
void modifica_risorsa(utente_t, risorse_t);
void cancellazioneRisorsa(utente_t, risorse_t);

#endif /* LIB_SPEC_SPECIFICHE_H_ */
