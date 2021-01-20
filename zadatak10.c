#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define SIZE 10

struct tree;
typedef struct tree* positiontree;
struct tree {

	char element[SIZE];
	positiontree left;
	positiontree right;
};

struct stack;
typedef struct stack* position;
struct stack {

	positiontree adr;
	position next;
};


int push(positiontree p, position s) {
	position q = NULL;
	q = createstack(p);

	if (q == NULL) return NULL;

	q->next = s->next;
	s->next = q;

	return 0;
}

positiontree pop(position s){

	position q = NULL;
	positiontree result = NULL;

	if (s->next == NULL) return NULL;

	q = s->next;
	result = q->adr;
	s->next = q->next;
	free(q);

	return result;
}

positiontree createtree(char* x) {

	positiontree p = NULL;
	p = (positiontree)malloc(sizeof(struct tree));

	if (p == NULL) {
		printf("Greska!\n");
		return NULL;
	}

	strcpy(p->element, x);
	p->left = NULL;
	p->right = NULL;
}

int createstack(positiontree s) {

	position q = NULL;

	q = (position)malloc(sizeof(struct stack));
	
	if (q == NULL) {
		printf("Greska!\n");
		return NULL;
	}

	q->adr = s;
	q->next = NULL;

	return q;

}

positiontree postfix(positiontree p) {
	
	struct stack head;
	head.next = NULL;
	positiontree result = NULL;
	char dat[30];
	char buffer[100] = { 0 };



	printf("Unesite ime datoteke:");
	scanf("%s", dat);
	printf("\n");

	FILE* fp = NULL;
	fp = fopen(dat, "r");

	if (fp == NULL) {
		printf("Greskaa!\n");
		return NULL;
	}
	while (!feof(fp)) {

		positiontree _tree = NULL;
		fscanf(fp, "%s", buffer);
		_tree = createtree(buffer);

		if (_tree == NULL) {
			fclose(fp);
			return NULL;
		}

		if (atoi(_tree->element)) {

			push(_tree, &head);

		}

		else {

			_tree->right = pop(&head);
			

			if (_tree->right == NULL) {
				printf("Greska!!\n");
				return NULL;
			}

			_tree->left = pop(&head);

			if (_tree->left == NULL) {
				printf("Greskaaa!\n");
				return NULL;
			}

			push(_tree, &head);
		}
	}

	result = pop(&head);

	if (result == NULL) {
		printf("Greska!!!\n");
		return NULL;
	}

	return result;
}

int infix(char *dat ,positiontree p) {

	FILE* fp = NULL;
	
	fp = fopen(dat, "w");
	
	if (fp == NULL) {
		printf("Greska\n");
		return NULL;
	}


	if (p->left != NULL) {
		fprintf(fp, "(");
		fclose(fp);

		infix(dat, p->left);

		fp = fopen(dat, "w");
		fprintf(fp, " %s ", p->element);
		fclose(fp);

		infix(dat, p->right);

		fp = fopen(dat, "w");
		fprintf(fp, ")");

	}

	else fprintf(fp, " %s ", p->element);
	
	fclose(fp);
	return 0;

}

int main() {

	positiontree root = NULL;

	root = postfix(root);

	if (root == NULL) return NULL;
	
	char dat[30];
	printf("Unesite ime datoteke u koji zelite upisati infix:");
	scanf("%s", dat);
	printf("\n");
	infix(dat,root);

	printf("Infix izraz je upisan u datoteku.\n");

	return 0;
}