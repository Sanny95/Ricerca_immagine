/*
 * acquisizione.c
 *
 *  Created on: 23 mag 2021
 *      Author: sasan
 */


#include "struct.h"

int acquisizioneInt() {
	int i = 0;

	while(scanf("%d", &i) != 1) {
		printf("Provare nuovamente --> ");

		while(getchar() != '\n');
	}

	return i;
}
//controllo di stringa
int acquisizioneSTR(int dim, char str[]) {
	int esito = 0;

	gets(str);
	if(strlen(str) > dim) {
		esito = 1;
	}

	return esito;
}

char *controllo_psw(char *psw) {
	psw = calloc(PASSWORD_LENGHT, sizeof(char));
	int flag = 0;
	int flag_up = 0;
	int flag_num = 0;
	int i;

	fflush(stdin);
   	printf("Inserisci una PASSWORD (max 4 caratteri)\n "
            "la password DEVE contenere almeno \n "
            "un numero ed una lettera maiuscola --> ");

	do{
		flag = 0;//inizializzo a zero

		if(acquisizioneSTR(PASSWORD_LENGHT-1, psw) == 0){ //se la lunghezza non supera i 4 caratteri, allora effettuo i controlli

			flag = 1; //la condizione è vera

			//inizializzo i flag ad ogni iterazione
			flag_up = 0;
			flag_num = 0;

			for(i = 0; i < PASSWORD_LENGHT; i++){
				flag_num += isdigit(psw[i]); //controlla ogni carattere se contiene un numero, in tal caso la funzione restituirà 1
				flag_up += isupper(psw[i]); //controlla ogni carattere se esiste la maiuscola, in tal caso la funzione restituirà 1

				//blocca il ciclo nel caso in cui sono stati trovati il carr. maiuscolo e il numero
				if((flag_num == 1)&&(flag_up == 1)){
					i = PASSWORD_LENGHT;
				}
			}

			if((flag_num == 1)&&(flag_up == 1)){
				puts("\n*** PASSWORD CORRETTA! ***\n");

			}else if(flag_num == 0){

				flag = 0;
				puts("\nNON CONTIENE UN NUMERO!. Riprovare\n");

			}else if(flag_up == 0){

				flag = 0;
				puts("\n NON CONTIENE UN CARATTERE MINUSCOLO!.Riprovare\n");

			}

		} else { //altrimenti stampo un messaggio di errore
			flag = 0;
			printf("\n PASSWORD TROPPO LUNGA, RIPROVARE --> ");
		}


	}while(flag == 0);

	return psw;
}


