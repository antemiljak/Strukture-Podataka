#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>




struct osoba;

typedef struct osoba* position;

struct osoba {

	char ime[50];
	char prezime[50];
	int godiste;
	position next;
};

void upis(position p) {

	position temp;

	temp = (position)malloc(sizeof(struct osoba));

	printf("Unesi podatke:\n");

	scanf("%s %s %d", temp->ime, temp->prezime, &temp->godiste);
	temp->next = p->next;
	p->next = temp;
}

void ispis(position p) {

	if (p == NULL) {
		printf("\nLista ne sadrzi clanove.\n");
	}
	else {
		printf("\nU listi se nalaze podaci:\n");
		while (p != NULL) {
			printf("%s %s %d\n\n", p->ime, p->prezime, p->godiste);
			p = p->next;
		}
	}
}

position pronadizadnji(position p) {

	while (p->next != NULL) {
		p = p->next;
	}
	return p;
}

position pronadiprethodni(position p) {

	char prez[50];
	if (p->next == NULL) {
		p = NULL;
	}
	else {
		printf("Upisi prezime osobe koju trazis:\n");
		scanf("%s", prez);
		while (strcmp(p->next->prezime, prez) != 0 && p->next->next != NULL) {
			p = p->next;
		}
		if (strcmp(p->next->prezime, prez) != 0) {
			p = NULL;
		}
	}
	return p;
}

position pronadiprezime(position p) {

	char pr[50];

	printf("Unesi prezime:\n");
	scanf(" %s", pr);

	while (p != NULL && strcmp(p->prezime, pr) != 0) {
		p = p->next;
	}
	return p;
}

void izbrisielement(position p) {

	position prije;

	prije = pronadiprethodni(p);

	if (prije != NULL) {
		p = prije->next;
		prije->next = p->next;
		printf("Osoba %s %s (%d.) je izbrisana.\n", p->ime, p->prezime, p->godiste);
		free(p);
	}
	else {
		printf("Osoba ne postoji u listi.\n");
	}
}



void sortiraj(position p) {
	position temp, start;
	int i = 1;

	printf("\nLista je sortirana, unesite i za ispis\n");

	temp = (position)malloc(sizeof(struct osoba));
	while (i == 1) {
		i = 0;
		start = p;

		

		while (start->next->next != NULL) {
			start = start->next;
			if (strcmp(start->prezime, start->next->prezime) > 0) {
				i = 1;

				strcpy(temp->ime, start->ime);
				strcpy(temp->prezime, start->prezime);
				temp->godiste = start->godiste;

				strcpy(start->ime, start->next->ime);
				strcpy(start->prezime, start->next->prezime);
				start->godiste = start->next->godiste;

				strcpy(start->next->ime, temp->ime);
				strcpy(start->next->prezime, temp->prezime);
				start->next->godiste = temp->godiste;
			}
		}

	}


	free(temp);
}
void unosudatoteku(char file[], position p) {
	FILE* f = fopen(file, "w");
	if (f == NULL) {
		printf("Greska pri ucitavanju datoteke.\n");
		
	}
	if (p->next != NULL) {
		while (p->next != NULL) {
			p = p->next;
			fprintf(f, "%s %s %d\n", p->ime, p->prezime, p->godiste);
		}
		
	}
	fclose(f);
	
}

void citajizdatoteke(position p) {


	FILE* fp;
	char imedat[50];
	position temp;

	printf("Napisi ime datoteke :  ");

	scanf(" %s", imedat);

	fp = fopen(imedat, "r");

	if (fp == NULL) {
		printf("\nDatoteka nije uspjesno otvorena\n");
		return -1;
	}
	else {
		while (!feof(fp)) {


			temp = (position)malloc(sizeof(struct osoba));

			fscanf(fp, "%s %s %d", temp->ime, temp->prezime, &temp->godiste);

			temp->next = p->next;
			p->next = temp;
			p = temp;
		}
	}
	fclose(fp);
	return 0;
}




int main()
{
	struct osoba head, * q;

	head.next = NULL;
	char izbor = 0;

	while (izbor != 'k') {
		printf("\nOdaberite operaciju nad listom:\n");
		printf("i za ispis\n");
		printf("u za upis na prvo mjesto\n");
		printf("z za upis na zadnje mjesto\n");
		printf("p za trazenje elementa\n");
		printf("b za brisanje elementa\n");
		printf("k za kraj programa\n");
		printf("a za dodavanje novog elementa iza odabranog elementa\n");
		printf("r za dodavanje novog elementa prije odabranog elementa\n");
		printf("s za sortiranje liste po prezimenima\n");
		printf("d za unos u datoteku\n");
		printf("c za citanje iz datoteke\n");



		scanf(" %c", &izbor);

		switch (izbor) {
		case 'i':
			ispis(head.next);
			break;
		case 'u':
			upis(&head);
			break;
		case 'z':
			q = pronadizadnji(&head);
			upis(q);
			break;
		case 'p':
			q = pronadiprezime(&head);
			if (q == NULL) {
				printf("Ne postoji ta osoba.\n");
			}
			else {
				printf("%s %s %d\n\n", q->ime, q->prezime, q->godiste);
			}
			break;
		case 'b':
			izbrisielement(&head);
			break;

		case 'a':
			q = pronadiprezime(&head);
			if (q == NULL) {
				printf("Ta osoba ne postoji.\n");
			}
			else {
				upis(q);
			}
			break;

		case 'r':
			q = pronadiprethodni(&head);
			if (q == NULL) {
				printf("Ta osoba ne postoji.\n");
			}
			else {
				upis(q);
			}
			break;

		case 's':
			sortiraj(&head);
			break;

		case 'd':
			unosudatoteku("listastudenata.txt", &head);
			break;
		case 'c':
			citajizdatoteke(&head);
			break;
		}
	}

	return 0;
}