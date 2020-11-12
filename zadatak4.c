#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct polinom;
typedef struct polinom* position;

typedef struct polinom {

	int koef;
	int exp;
	position next;


};

void ucitaj(position);
void ispisi(position);
void sortiraj(position);
void zbroji(position, position, position);
void mnozi(position, position, position);
position traziprethodninule(position);
void brisinulu(position);
void zbrojiexp(position);

int main()
{
	struct polinom POL1, POL2, SUMA, PRODUKT;

	POL1.next = NULL;
	POL2.next = NULL;
	SUMA.next = NULL;
	PRODUKT.next = NULL;

	ucitaj(&POL1);
	ucitaj(&POL2);

	sortiraj(&POL1);
	sortiraj(&POL2);

	//zbrojiexp(&POL1);
	//zbrojiexp(&POL2);

	ispisi(&POL1);
	ispisi(&POL2);

	printf("\nZbrojeni polinom:\n");
	zbroji(POL1.next, POL2.next, &SUMA);
	sortiraj(&SUMA);
	brisinulu(&SUMA);
	ispisi(&SUMA);

	printf("\nPomnozeni polinom:\n");
	mnozi(POL1.next, POL2.next, &PRODUKT);
	sortiraj(&PRODUKT);
	brisinulu(&PRODUKT);
	zbrojiexp(&PRODUKT);
	ispisi(&PRODUKT);

	return 0;
}



void ucitaj(position p){

	FILE* fp;
	char imedat[50];
	position temp;

	printf("\nUnesi ime datoteke iz koje zelis ucitati polinom: ");
	scanf("%s", imedat);

	fp = fopen(imedat, "r");
	
	if (fp == NULL)
		printf("\nDatoteka nije uspjesno otvorena\n");
	else {
		while (!feof(fp)) {
			temp = (position)malloc(sizeof(struct polinom));
			fscanf(fp, "%d %d", &temp->koef, &temp->exp);
			temp->next = p->next;
			p->next = temp;
			p = temp;
		}
	}
	fclose(fp);
}

void ispisi(position p) {

	p = p->next;
	printf("\nPOLINOM :  ");
	while (p != NULL) {

		if (p->exp == 0) {
			printf("%d  ", p->koef);
		}
		else if (p->exp == 1) {
			printf("%dx  ", p->koef);
		}
		else {
			printf("%dx^%d  ", p->koef, p->exp);
		}
		p = p->next;
	}
	printf("\n\n");
}

void sortiraj(position p) {

	position q, q_prev, temp, end;
	end = NULL;

	while (p->next != end) {
		q_prev = p;
		q = p->next;

		while (q->next != end) {

			if (q->exp > q->next->exp) {

				temp = q->next;
				q_prev->next = temp;
				q->next = temp->next;
				temp->next = q;

				q = temp;

			}

			q_prev = q;
			q = q->next;
		}

		end = q;

	}

}	

void zbroji(position p1, position p2, position rez) {
	position q, temp;

	temp = rez;

	while (p1 != NULL && p2 != NULL) {

		if (p1->exp < p2->exp) {
			q = (position)malloc(sizeof(struct polinom));

			q->exp = p1->exp;
			q->koef = p1->koef;

			q->next = rez->next;
			rez->next = q;

			p1 = p1->next;

			rez = rez->next;
		}

		else if (p1->exp > p2->exp) {
			q = (position)malloc(sizeof(struct polinom));	

			q->exp = p2->exp;
			q->koef = p2->koef;

			q->next = rez->next;	
			rez->next = q;

			p2 = p2->next;
			rez = rez->next;
		}

		else if (p1->exp == p2->exp) {
			q = (position)malloc(sizeof(struct polinom));	

			q->exp = p2->exp;	
			q->koef = p2->koef + p1->koef;

			
			q->next = rez->next;	
			rez->next = q;

			p1 = p1->next;
			p2 = p2->next;

			rez = rez->next;
		}

	}

	

	if (p1 != NULL) {
		while (p1 != NULL) {
			q= (position)malloc(sizeof(struct polinom));

			q->koef = p1->koef;
			q->exp = p1->exp;

			q->next = rez->next;	
			rez->next = q;

			p1 = p1->next;
			rez = rez->next;
		}

	}

	if (p2 != NULL) {
		while (p2 != NULL) {
			q = (position)malloc(sizeof(struct polinom));

			q->koef = p2->koef;
			q->exp = p2->exp;

			q->next = rez->next;	
			rez->next = q;

			p2 = p2->next;
			rez = rez->next;
		}

	}

	
}

void brisinulu(position p) {
	
	position temp;

	temp = traziprethodninule(p);

	if (temp != NULL) {
		p = temp->next;
		temp->next = p->next;

		free(p);
	}
	else printf("\nPolinom je ispravan\n");

}

position traziprethodninule(position p) {
	
	if (p->next == NULL)
		p = NULL;

	else {
		while (p->next->koef != 0 && p->next->next != NULL)
			p = p->next;

		if (p->next->koef != 0)
			p = NULL;

	}

	return p;
}

void mnozi(position p1, position p2, position rez) {

	position q, temp;
	position p2head;

	temp = rez;
	p2head = p2;

	while (p1 != NULL) {

		while (p2 != NULL) {

			q = (position)malloc(sizeof(struct polinom));

			q->exp = p1->exp + p2->exp;
			q->koef = p1->koef * p2->koef;

			q->next = rez->next;
			rez->next = q;

			

			rez = rez->next;

			p2 = p2->next;
		}

		p1 = p1->next;
		p2 = p2head;
	}

}


void zbrojiexp(position p)
{
	position pret, q, sljed;

	pret = p;
	q = p->next;
	sljed = q->next;

	while (sljed != NULL)
	{
		if (q->exp == sljed->exp) {	
			sljed->koef =sljed->koef + q->koef;	

			pret->next = sljed;	

			free(q);	

			q = sljed;	
			sljed = sljed->next;	
			pret = pret;
		}
		else {

			pret = q;	
			q = sljed;	
			sljed = sljed->next; 
		}
	}
	
}
