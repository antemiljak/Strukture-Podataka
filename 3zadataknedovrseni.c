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

void sortiraj(position p)
{

	printf("Lista sortirana po prezimenima glasi:\n");
	

}
void unosudatoteku(position p)//neradi
{

	FILE *fp;
	char imedat[10];
	printf("\nunesite ime datoteke: ");
	scanf("%s", imedat);

	fp = fopen(imedat, 'w');
	if (fp == NULL)
		printf("Greska pri otvaranju datoteke\n");
	else {

		while (!feof) {
			printf(fp, " %s %s %d\n", p->ime, p->prezime, p->godiste);
			p = p->next;
		}
	}
	fclose(fp);
}


int main()
{
	struct osoba head, *q;

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

		case 'd':
			unosudatoteku(head.next);
			break;
		}
	}

	return 0;
}