#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>



struct stog;

typedef struct stog* position;


struct stog {
    int el;
    position next;
} ;


int push(position s, int element) {
    
    position q;

    q = (position)malloc(sizeof(struct stog));

    if (q == NULL) {
        
        printf("Greska");
        return -1;
    }
    q->el = element;

    q->next = s->next;
    s->next = q;

    return  0;
}

int pop(position s) {

    int broj = s->next->el;

    position q;

    q = s->next;
    s->next = q->next;

    free(q);

    return broj;
}


int ispisi(position s) {
    
    if (s == NULL) {
        printf("Greska\n");
        return -1;
    }
    while (s != NULL) {

        printf("%d  ", s->el);
        s = s->next;
    }
    printf("\n");

    return 0;
}




int izracun(position s, char* str) {
    
    char* token;

    token = strtok(str, " ");

    while (token != NULL) {

        if (isdigit(*token))
            push(s, atoi(token));

        else
            operacija(s, *token);

        token = strtok(NULL, " ");
    }

    return pop(s);
}

int operacija(position s, char c) {
   
    int a = pop(s);
    int b = pop(s);
    
    switch (c)
    {
    case '+':
        push(s, a + b);
        break;

    case '-':
        push(s, b - a);
        break;

    case '*':
        push(s, a * b);
        break;

    default:
        break;
    }
    return 0;
}

int main() {
    
    struct stog stog1;
    stog1.next = NULL;

    char ime[20];

    char str[100];
    
    printf("\nUnesite ime datoteke iz koje zelite ucitati postfix!\n");
    scanf(" %s", ime);

    FILE* fp = fopen(ime, "r");

    fgets(str, 100, fp);

    fclose(fp);

   
    
    printf(" Rezultat je %d", izracun(&stog1, str));


    return 0;
}