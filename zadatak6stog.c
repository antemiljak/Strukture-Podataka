#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>


struct stog;
typedef struct stog* position;
struct stog 
{
	int element;
	position next;
};


void push(int el, position s) {

	position q;
	q = (position)malloc(sizeof(struct stog));

	q->element = el;
	
	q->next = s->next;
	s->next = q;

	printf("\n U stog je upisan element %d\n", el);


}


int pop(position s) {

	position q;
	if (s->next == NULL)
		printf("\nGreska!! Stog je prazan\n");

	else {
		printf("Skidamo sa stoga element %d", s->next->element);
		q = s->next;
		s->next = q->next;

		free(q);
	}

}

ispis(position s) {

	if (s == NULL)
		printf("\nGreska!! Stog je prazan\n");
	else {
		printf("\nU stogu se nalaze elementi: ");
		while (s != NULL) {
			printf("%d   ", s->element);
			s = s->next;
		}

		printf("\n");
	}

}


int main() {

	struct stog stog1;
	stog1.next = NULL;
	int broj;

	char c= 0;

	while (c != 'k') {

		printf("\nUnesite slovo za odredenu operaciju: \n\n a za push\n\n b za pop\n\n c za ispis\n\n k za kraj programa\n\n");

		scanf(" %c", &c);

		switch (c) {

		case 'a':
			broj = rand() % (100 - 10 + 1) + 10;
			push(broj, &stog1);
			break;

		case 'b':
			pop(&stog1);
			break;

		case 'c':
			ispis(stog1.next);
			break;
		}
	}


	return 0;
}