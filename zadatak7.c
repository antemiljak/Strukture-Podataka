
//nije dovrseno

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct stog;
typedef struct stog *position;

struct stog{

	int element;
	position next;

};

void push(int el, position s) {

	position q;
	q = (position)malloc(sizeof(struct stog));

	q->element = el;

	q->next = s->next;
	s->next = q;

	printf("\nUcitan je broj %d", el);

}

int pop(position s) {

	position q;
	if (s->next == NULL)
		printf("\nU stogu nema brojeva\n");

	else {

		printf("\nU operaciju ulazi broj: ");

		q = s->next;
		s->next = q->next;

		free(q);

	}

}

ispis(position s) {

	printf("\nRjesenje je ");
	
	if (s == NULL)
		printf("Greska!!!");

	else {

		while (s->next != 0) {
			printf(" %d ", s->element);
			s = s->next;
		}
	}
	printf("\n");
}

int main() {

	struct stog stog1;
	stog1.next = NULL;
	char digit = 0;
	int a, b;
	char imedat[50];

	FILE *fp;
	printf("Unesite ime datoteke iz koje zelite ucitati postfix: \n");
	scanf(" %s", imedat);

	fp = fopen(imedat, "r");
	if (fp == NULL)
		printf("Datoteka nije uspjesno otvorena!\n");

	else {
		while (!feof(fp))
		{
			fscanf(fp, " %c", &digit);

			if (isdigit(digit) != 0) {

				push(digit, &stog1);

			}

			else if (digit == '+' || digit == '-' || digit == '*' ) {

				switch (digit) {
				case '+':
					a = pop(&stog1);
					b = pop(&stog1);

					push(a + b, &stog1);
					break;


				case '-':
					a = pop(&stog1);
					b = pop(&stog1);

					push(a - b, &stog1);
					break;

				case '*':
					a = pop(&stog1);
					b = pop(&stog1);

					push(a * b, &stog1);
					break;

				}


	
			}

			else break;

		}
	}

	ispis(stog1.next);

	return 0;

}
