#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

struct node;//stablo
typedef struct node *position;
typedef struct node {
	int br;
	position left;
	position right;

};


position insert(position current, position el) {

	if (NULL == current) return el;

	if (current->br > el->br) {
		current->left = insert(current->left, el);

	}

	else if (current->br < el->br) {
		current->right = insert(current->right, el);

	}

	else {
		printf("Greska dupli element: %d\n", el->br);
		free(el);
	
	}

	return current;

}

void printinorder(position current) {
	if (NULL == current) {
		return;
	}
	printinroder(current->left);
	printf("%d ", current->br);
	printinorder(current->right);//ako zamijenimo left i right imamo ispis postorder a ako je prvi printf%d onda je preorder

}

position search(position current, int num) {

	if (NULL == current) return NULL;
	if (current->br == num)
		return current;
	else if (current->br > num) {
		return search(current->left, num);
	}
	else return find(current->right, num);

}

position findmax(position current) {

	if (NULL == current) return NULL;

	while (current->right != NULL) {
		current = current->right;
	}

	return current;

}

position findmin(position current) {

	if (NULL == current) return NULL;

	while (current->left != NULL) {
		current = current->left;
	}

	return current;

}

position delete(position current, int num) {

	if (NULL == current) return NULL;

	if (current->br == num) {

		if (current->left != NULL ) {
			position result = findmax(current->left);
			current->br = result->br;
			current->left = delete(current->left, result->br);
		}
		else if (current->right != NULL) {
			position result = findmin(current->left);
			current->br = result->br;
			current->right = delete(current->right, result->br);
		}
		else {
			free(current);
			return NULL;
		}

	}

	else if (current->br > num)
		current->left = delete(current->left, num);

	else current->right = delete(current->right, num);

	return current;

}

int main() {

	position root = NULL;

	root = delete(root, 5);





	return 0;


}