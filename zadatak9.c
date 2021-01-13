#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

struct tree;
typedef struct tree* position;
typedef struct tree {

	int num;
	position left;
	position right;

};

position insert(position current, int el) {

	if (current == NULL) {

		current = (position)malloc(sizeof(struct tree));

		current->num = el;
		current->left = NULL;
		current->right = NULL;

	}

	else if (current->num > el) {
		current->left = insert(current->left, el);
	}

	else if (current->num < el) {
		current->right = insert(current->right, el);
	}

	else
		printf("Error: duplicate\n");

	return current;
}

void print(position current) {

	if (current == NULL)
		return NULL;
	
	print(current->left);
	printf(" %d ", current->num);
	print(current->right);
		
}

position search(position current, int el) {

	if (current == NULL)
		printf("Number doesnt exist\n");

	if (current->num == el)
		return current->num;

	else if (current->num < el)
		search(current->right, el);

	else
		search(current->left, el);

}

position findmin(position current) {

	if (current==NULL) return NULL;

	while (current->left != NULL) {
		current = current->left;
	}

	return current;

}

position findmax(position current) {

	if (current == NULL) return NULL;

	while (current->right != NULL) {
		current = current->right;
	}

	return current;

}

position delete(position current, int el) {

	if (current == NULL) return NULL;

	if (current->num > el)
		current->left = delete(current->left, el);

	else if (current->num < el)
		current->right = delete(current->right, el);

	else {

		if (current->left != NULL) {
			position result = findmax(current->left);
			current->num = result->num;
			current->right = delete(current->right, result->num);
		}

		else if (current->right != NULL) {
			position result = findmin(current->right);
			current->num = result->num;
			current->left = delete(current->left, result->num);
		}
		else {
			free(current);
			return NULL;
		}


	}

	return current;



}

int main() {

	position root = NULL;
	
	int num, a, wantednum;
	

	char c = 0;
	while (c != 'e') {

		printf("\nOperation:\n");
		printf("i- insert\np- print\nd- delete\ns- search element\ne- end\n");
		scanf(" %c", &c);

		switch (c) {

		case 'i':

			printf("Insert number: ");
			scanf("%d", &a);
			printf("\n");
			root = insert(root, a);
			break;

		case 'p':

			print(root);
			break;

		case 'd':
			printf("Insert number to delete:");
			scanf("%d", &a);
			printf("\n");
			root = delete(root, a);

			break;

		case's':
			printf("Insert wanted number:");
			scanf("%d", &a);
			printf("\n");
			wantednum = search(root, a);
			if (wantednum != NULL)
				printf("Number %d has been found.\n", a);
			break;

		default:
			break;


		}

	}
	return 0;
}