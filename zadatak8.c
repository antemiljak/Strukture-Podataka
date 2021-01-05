#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define BUFF 200

typedef struct direktorij;
typedef struct direktorij* dirposition;


struct direktorij
{
	char* dirime;
	dirposition sibling;
	dirposition child;
};

typedef struct stog;
typedef struct stog* stogposition;


struct stog
{
	dirposition dirpok;
	stogposition next;
};

stogposition napravistog();

int operacijia(dirposition, stogposition);
char* polozaj(stogposition);
int ispis(stogposition);

dirposition pop(stogposition);
int push(stogposition, dirposition);

int md(dirposition, char*);
dirposition cd(dirposition, stogposition, char*);


int izbrisi(dirposition);


int main()
{
	dirposition root;
	stogposition start;
	dirposition state;

	root = (dirposition)malloc(sizeof(struct direktorij));

	start = napravistog();

	root->sibling = NULL;
	root->child = NULL;
	root->dirime = NULL;

	state = root;

	start->dirpok = root;
	start->next = NULL;

	printf("Terminal:\n\n");
	printf("Operacije:\n");
	printf("1 - md\n2 - cd dir\n3 - cd .. \n4 - dir \n5 - exit\n");
	
	operacija(state, start);

	return 0;
}


stogposition napravistog()
{
	stogposition el;
	dirposition novidir;

	el = (stogposition)malloc(sizeof(struct stog));
	novidir = (dirposition)malloc(sizeof(struct direktorij));

	novidir->sibling = NULL;
	novidir->child = NULL;

	if (el != NULL && novidir != NULL)
	{
		
		el->dirpok = novidir;
		el->next = NULL;

		return el;
	}
	else
	{
		printf("\nGreska!!!\n");
		return -1;
		
	}
}

int push(stogposition s, dirposition p)
{
	stogposition q;

	q = napravistog();

	q->dirpok = p;

	q->next = s->next;
	s->next = q;

	return 0;
}

dirposition pop(stogposition s)
{
	stogposition q;

	q = s->next;

	if (q->next != NULL) {

		s->next = q->next;
	}


	return q->dirpok;
}

int operacija(dirposition p, stogposition s)
{
	char* a;
	int i = 1, el = 0;
	char order[10], ime[BUFF], _polozaj[BUFF];

	a = (char*)malloc(sizeof(char)* BUFF);

	printf("\n\n");


	while (i != 0)
	{

		a = polozaj(s);
		strcpy(_polozaj, a);

		printf("%s>", _polozaj);
		scanf("%s", order);

		if (strcmp(order, "dir") == 0)
			i = ispis(p);
		else if (strcmp(order, "exit") == 0)
		{
			izbrisi(p);

			return 0;
		}
		else if (strcmp(order, "md") != 0 && strcmp(order, "cd") != 0)
			i = 3;
		else
			scanf("%s", ime);



		if (strcmp(order, "md") == 0)
			i = md(p, ime);
		else if (strcmp(order, "cd") == 0)
		{
			if (strcmp(ime, "..") == 0)
				p = pop(s);
			else
				p = cd(p, s, ime);

			i = 1;

		}

		if (i == 3)
			printf("Greska!!!\n");


		printf("\n");
	}



	return 0;
}

char* polozaj(stogposition s)
{
	char a[BUFF];

	strcpy(a, "C:\\Korisnici");

	while (s->next != NULL)
	{
		strcat(a, "\\");
		strcat(a, s->dirpok->child->dirime);

		s = s->next;

	}


	return a;
}


int md(dirposition p, char* ime)
{
	dirposition q;
	dirposition _child;

	q = (dirposition)malloc(sizeof(struct direktorij));

	q->sibling = NULL;
	q->child = NULL;

	 _child = p->child;


	q->dirime = (char*)malloc(strlen(ime) + 1);

	strcpy(q->dirime, ime);


	if (p->child == NULL) {
		p->child = q;
	}
	else
	{
		q->sibling = _child;
		p->child = q;

	}


	return 1;
}


dirposition cd(dirposition p, stogposition s, char* a)
{
	dirposition q;

	q = p->child;

	while (q != NULL && strcmp(q->dirime, a) != 0)
		q = q->sibling;

	if (q == NULL)
	{
		printf("Greska!\n");

		return p;
	}
	else 
		push(s, p);


	return q;
}


int izbrisi(dirposition p)
{
	if (p == NULL)
		return;


	izbrisi(p->sibling);
	izbrisi(p->child);


	free(p);
}


int ispis(dirposition p)
{
	int i = 0;
	dirposition q;

	q = p->child;

	printf("\n");

	while (q != NULL)
	{
		printf("%s\n\n", q->dirime);

		q = q->sibling;

		i++;
	}

	printf("%d directories\n", i);


	return 1;
}





