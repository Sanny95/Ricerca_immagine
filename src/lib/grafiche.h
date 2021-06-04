/*
 * grafiche.h
 *
 *  Created on: 23 mag 2021
 *      Author: sasan
 */

#ifndef LIB_GRAFICHE_H_
#define LIB_GRAFICHE_H_

void visualizzaMenuPrincipale();
void visualizzaRegistrazioneUtente();
void visualizzaAccesso();

void visualizzaMenuUtilizzatore();
void visualizzaMenuCreatore();
void visualizzaModificaAccount();
void visualizzaCancellaAccount();

void visualizzaCercaRisorsa();
void visualizzaValutaRisorsa();

void visualizzaGestioneRisorsa();
void visualizzaAggiungiRisorsa();
void visualizzaRisorse(FILE*, utente_t, risorse_t);
void visualizzaModificaRisorsa();
void visualizzaCancellaRisorsa();


#endif /* LIB_GRAFICHE_H_ */
