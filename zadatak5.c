#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct lista*position;
struct lista {

	int x;
	position next;

};


void ucitaj(position);
void ispisi(position);
void sortiraj(position);
void unija(position, position, position);
void presjek(position, position, position);

int main() {

	struct lista list1, list2, un, pr;

	list1.next = NULL;
	list2.next = NULL;
	un.next = NULL;
	pr.next = NULL;

	ucitaj(&list1);
	ucitaj(&list2);

	sortiraj(&list1);
	sortiraj(&list2);

	ispisi(&list1);
	ispisi(&list2);

	printf("\n\nNova lista koju dobijemo unijom:\n");

	unija(list1.next, list2.next, &un);
	ispisi(&un);

	printf("\n\nNova lista koju dobijemo presjekom:\n");

	presjek(list1.next, list2.next, &pr);
	ispisi(&pr);

	system("pause");
	return 0;


}


void ucitaj(position p) {

	FILE* fp;
	char imedat[50];
	position temp;

	printf("\nUnesi ime datoteke iz koje zelis ucitati listu: ");
	scanf("%s", imedat);

	fp = fopen(imedat, "r");

	if (fp == NULL)
		printf("\nDatoteka nije uspjesno otvorena\n");
	else {
		while (!feof(fp)) {
			temp = (position)malloc(sizeof(struct lista));
			fscanf(fp, "%d ", &temp->x);
			temp->next = p->next;
			p->next = temp;
			p = temp;
		}
	}
	fclose(fp);
}

void ispisi(position p) {

	p = p->next;
	printf("\nLISTA :  ");
	while (p != NULL) {

		printf("%d  ", p->x);
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

			if (q->x > q->next->x) {

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

void unija(position p1, position p2, position rez) {

	position q, temp;

	temp = rez;

	while (p1 != NULL && p2 != NULL) {

		if (p1->x < p2->x) {
			q = (position)malloc(sizeof(struct lista));

			q->x = p1->x;


			q->next = rez->next;
			rez->next = q;

			p1 = p1->next;

			rez = rez->next;
		}

		else if (p1->x > p2->x) {
			q = (position)malloc(sizeof(struct lista));

			q->x = p2->x;


			q->next = rez->next;
			rez->next = q;

			p2 = p2->next;
			rez = rez->next;
		}

		else if (p1->x == p2->x) {
			q = (position)malloc(sizeof(struct lista));

			q->x = p2->x;



			q->next = rez->next;
			rez->next = q;

			p1 = p1->next;
			p2 = p2->next;

			rez = rez->next;
		}

	}

	if (p1 != NULL) {
		while (p1 != NULL) {
			q = (position)malloc(sizeof(struct lista));

			q->x = p1->x;


			q->next = rez->next;
			rez->next = q;

			p1 = p1->next;
			rez = rez->next;
		}

	}

	if (p2 != NULL) {
		while (p2 != NULL) {
			q = (position)malloc(sizeof(struct lista));

			q->x = p2->x;


			q->next = rez->next;
			rez->next = q;

			p2 = p2->next;
			rez = rez->next;
		}

	}

}

void presjek(position p1, position p2, position rez) {

	position q, temp;

	temp = rez;

	while (p1 != NULL && p2 != NULL) {

		if (p1->x < p2->x) {

			p1 = p1->next;

		}

		else if (p1->x > p2->x) {

			p2 = p2->next;

		}

		else if (p1->x == p2->x) {

			q = (position)malloc(sizeof(struct lista));

			q->x = p2->x;

			q->next = rez->next;
			rez->next = q;

			p1 = p1->next;
			p2 = p2->next;

			rez = rez->next;
		}

	}

}