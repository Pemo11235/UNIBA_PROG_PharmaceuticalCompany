#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct
{
	char codice [20];
	char nome [20];
	int num_conf;
	int mese;
	int anno;
} farmaco;

int Acquisizione_Num_Farmaci ();
void Acquisizione_Tabella(int , farmaco []);
void Gestione_Tot_Conf (int ,farmaco []);
void Gestione_Scadenze(int , farmaco []);
void Gestione_Conf_Rimaste(int , farmaco []);
void Gestione_Max_Conf();
void Ordinamento_Bubble ();



int main (void)
{
	farmaco Tabella [20];
	int num_farmaci, selezione, verifica,esci;
	char risposta;

	num_farmaci = 0;
	selezione = 0;
	verifica = 0;
	esci = 0;

	while (verifica == 0) {
		printf("| Gestione Farmacia |\nPrima di procedere sara' necessario acquisire i farmaci da gestire. Intendi procedere all'acquisizione?\n\t Si (S)\t No (N) ");
		fflush(stdin);
		risposta = getchar();
		if (risposta == 'S' || risposta == 's') {

			num_farmaci = Acquisizione_Num_Farmaci ();
			Acquisizione_Tabella(num_farmaci, Tabella);

			while (esci == 0) {
				printf("\nCome intendi proseguire? (Selezionare un numero fra 1 e 5) :\n\t");
				printf("1) Totale confezioni disponibili in magazzino,\n\t");
				printf("2) Totale confezioni non scadute in riferimento ad una data,\n\t");
				printf("3) Rimanenze farmaco,\n\t");
				printf("4) Farmaco con piu' confezioni,\n\t");
				printf("5) Lista farmaci per numero di confezioni,\n\t");
				printf("6) Chiudi il programma.\n\t");
				scanf("%d", &selezione);

				switch (selezione)
				{
					case 1 :
						Gestione_Tot_Conf(num_farmaci, Tabella);
						break;
					case 2 :
						Gestione_Scadenze(num_farmaci, Tabella);
						break;
					case 3 :
						Gestione_Conf_Rimaste(num_farmaci, Tabella);
						break;
					case 4 :
						Gestione_Max_Conf(num_farmaci, Tabella);
						break;
					case 5 :
						Ordinamento_Bubble (num_farmaci, Tabella);
						break;
					case 6 :
						esci++;
						verifica++;
						break;
					default :
						printf("\tInput non valido. Riavvio...\n\n");
						break;
				}
			}

		} else if (risposta == 'N' || risposta == 'n') {
			verifica++;
		}
		else {
			printf("Input non valido ! Riavvio ...\n\n");
		}
	}

	system("PAUSE");
	return 0;
}

int Acquisizione_Num_Farmaci ()
{
	int num_conf;
	int v;



	printf("\n\t");

	do {
		v = 0;
		printf("Inserire il numero dei farmaci che si intende acquisire:");
		printf(" \n \t Attenzione! Il numero massimo acquisibile e' di 20 farmaci. \n");
		scanf("%d", &num_conf);

		if (num_conf > 20)
		{
			printf("\tErrore! Numero non valido o superiore a 20 !\n\tPrego, Re-");
			fflush(stdin);
		}else {
			v++;
		}
	} while (v != 1);

	return num_conf;
}

void Acquisizione_Tabella(int num_f ,farmaco tab [])
{
	int i,v;
	i = 0;

	printf("\n\tAcquisizione tabella farmaci :");

	for ( i = 0; i < num_f; i++)
	{
		v = 0;

		printf("\n\t\tAcquisizione del farmaco %d:", i+1);
		printf("\n\t\t\tInserire codice alfanumerico: ");
		scanf("%s", tab[i].codice);
		printf("\t\t\tInserire nome: ");
		scanf("%s", tab[i].nome);
		printf("\t\t\tInserire numero confezioni disponibili: ");
		scanf("%d", &tab[i].num_conf);
		printf("\t\t\tInserire data di scadenza: \n");
		while (v == 0) {
			printf("\t\t\t\tMese (da 1 a 12): ");
			scanf("%d", &tab[i].mese);

			if ( (tab[i].mese <= 0) || (tab[i].mese > 12) ) {
				printf("\t\t\t\tErrore! Il mese dev'essere compreso fra 1 e 12\n");
				fflush(stdin);
				v = 0;
			}
			else {
				v++;
			}
		}

		v = 0;

		while (v == 0) {

			printf("\t\t\t\tAnno: ");
			scanf("%d", &tab[i].anno);

			if ( tab[i].anno > 0) {
				v++;
			}
			else {
				printf("\t\t\t\tErrore! L'anno dev'essere piu' grande di 0 !\n");
				fflush(stdin);
				v = 0;
			}
		}
	}
 }

void Gestione_Tot_Conf (int num_f, farmaco tab[])
{
	int i,tot_conf ;

	tot_conf = 0;
	i = 0;

	for (i = 0; i < num_f ; i ++) {
		tot_conf = tot_conf + tab[i].num_conf;
	}

	printf("\n\t Il numero delle confezioni totali e': %d\n", tot_conf);
}


void Gestione_Scadenze(int num_f , farmaco tab [])
{
	int Mese_U, Anno_U,conf_s, v, i;

	conf_s = 0;
	v = 0;
	i = 0;

	printf("\n\tInserire la data di scadenza di riferimento: \n");
	while (v == 0) {
		printf("\t\tMese (da 1 a 12): ");
		scanf("%d", &Mese_U);

		if ( (Mese_U <= 0) || (Mese_U > 12) ) {
			printf("\t\t\tErrore! Il mese dev'essere compreso fra 1 e 12\n");
			fflush(stdin);
			v = 0;
		}
		else {
			v++;
		}
	}

	v = 0;

	while (v == 0) {
		printf("\t\tAnno: ");
		scanf("%d", &Anno_U);
		if ( Anno_U > 0) {
			v++;
		}
		else {
			printf("\t\t\tErrore! L'anno dev'essere piu' grande di 0 !\n");
			v = 0;
		}

	}

	for (i = 0; i < num_f; i++) {
		if ( Anno_U < tab[i].anno) {
			conf_s = conf_s + tab[i].num_conf;
		} else if (Anno_U == tab[i].anno && Mese_U < tab[i].mese) {
			conf_s = conf_s + tab[i].num_conf;
		}
	}

	printf("\tIl numero totale delle confezioni non ancora scadute e': %d\n", conf_s);

}


void Gestione_Conf_Rimaste(int num_f,farmaco tab[])
{
	int Conf_U, i;
	char Cod_U [20];

	Conf_U = 0;
	i = 0;

	printf("\n\tInserire il codice del farmaco di cui si vuole conoscere il numero di confezioni disponibili: ");
	scanf("%s", Cod_U);

	for (i = 0; i < num_f; i++) {
		if ( ( strcmp (Cod_U,tab[i].codice) ) == 0 ) {
			Conf_U += tab[i].num_conf;
		}
		else if ( i == num_f-1 && Conf_U == 0)
		{
			printf("\n\tCodice errato o inesistente ! \n");
		}
	}

	printf("\n\tIl totale delle confezioni del farmaco richiesto e': %d\n", Conf_U);
}


void Gestione_Max_Conf(int num_f, farmaco tab[])
{
	int i, max ;
	char Nome_M [20];
	char Cod_M[20];
	i = 0;
	max = 0;

	for (i = 0; i < num_f; i++) {
		if (tab[i].num_conf > max) {
			max = tab[i].num_conf;
			strcpy(Nome_M,tab[i].nome);
			strcpy(Cod_M,tab[i].codice);
		}
	}

	printf("\n\tIl farmaco con piu' confezioni e'  ");
	printf("\n\t\tNome : %s", Nome_M );
	printf("\n\t\tCodice : %s\n", Cod_M);

}

void Ordinamento_Bubble (int num_f, farmaco tab[])
{
	int c1=0;
	int c2=0;
	int temp;

	for(c1 = 0; c1 < num_f; c1++) {
	   for(c2 = 0; c2 < num_f - c1 - 1; c2++) {
		   if(tab[c2].num_conf > tab[c2+1].num_conf) {
			   temp = tab[c2].num_conf;
			   tab[c2].num_conf = tab[c2+1].num_conf;
			   tab[c2+1].num_conf = temp;
		   }
	   }
	}
	c1 = 0;
	printf("\n\tTabella farmaci ordinata per confezioni:\n  ");

	for (c1 = 0; c1 < num_f; c1++) {
		printf("\n\t\t%s\t\t%s\t\t%d\t\t %d %d ,\n ", tab[c1].codice ,
			 tab[c1].nome , tab[c1].num_conf ,tab[c1].mese ,tab[c1].anno );
	}
}

