#include <stdio.h>
#include <stdlib.h>



typedef struct student
{
	char ime[20];
	char prezime[20];
	int bodovi;
}_stud;

int main()
{
	FILE* fp = NULL;
	int i, br, max_bodovi;
	i = 0;
	br = 0;
	max_bodovi = 50;
	char c;
	_stud* student;
	double prosjek[20];

	fp = fopen("student.txt", "r");	
	if (fp == NULL) {
		printf("Datoteka nije otvorena.\n");
		return 1;	
	}
	while (!feof(fp)) {
		c = fgetc(fp);
		if (c == '\n')
			br++;
		
	}
	printf("Datoteka ima %d redaka.\n", br);
	rewind(fp);		
	student = (_stud*)malloc(br * sizeof(_stud));	
	while (!feof(fp)) {
		fscanf(fp, "%s %s %d", student[i].ime, student[i].prezime, &student[i].bodovi);	
		i++;	
	}

	for (i = 0; i < br; i++) {
		prosjek[i] = (double)student[i].bodovi /max_bodovi * 100;	
		printf("%s %s %d %.1lf\n", student[i].ime, student[i].prezime, student[i].bodovi, prosjek[i]);	
	}
	fclose(fp);		
	return 0;
}