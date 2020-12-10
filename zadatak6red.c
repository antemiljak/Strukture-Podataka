#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

struct red;
typedef struct red* position;
struct red {

	int element;
	position next;

 };

void push(int el, position r) {

	position q;
	q = (position)malloc(sizeof(struct red));

	while (r->next != NULL)
		r = r->next;
	
	q->element = el;


	q->next = r->next;
	r->next = q;


	printf("\nU red je upisan element %d\n", el);

}

int pop(position r) {

	position q;

	if (r->next == NULL)
		printf("\Greska!!! U redu nema clanova\n");
	else {

		printf("Skidamo sa reda element %d", r->next->element);
		q = r->next;
		r->next = q->next;

		free(q);
}

}

ispis(position r) {

	if (r == NULL)
		printf("\nGreska!! Red je prazan\n");
	else {
		printf("\nU redu se nalaze elementi: ");
		while (r != NULL) {
			printf("%d   ", r->element);
			r = r->next;
		}

		printf("\n");
	}
	
}


int main() {

	struct red red1;
	red1.next = NULL;
	
	int broj;

	char c = 0;

	while (c != 'k') {

		printf("\nUnesite slovo za odredenu operaciju: \n\n a za push\n\n b za pop\n\n c za ispis\n\n k za kraj programa\n\n");

		scanf(" %c", &c);

		switch (c) {

		case 'a':
			broj = rand() % (100 - 10 + 1) + 10;
			push(broj, &red1);
			break;

		case 'b':
			pop(&red1);
			break;

		case 'c':
			ispis(red1.next);
			break;
		}
	}


	return 0;
}