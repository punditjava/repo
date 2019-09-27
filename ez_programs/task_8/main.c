#include<stdio.h>
#include <stdlib.h>
#include <dlfcn.h>
#define SIZE 3

int check_file(FILE *file)
{	
	fseek(file,0,SEEK_SET);
	char *matrix = "MATRIX";
	char *str, *a_str = NULL;
	a_str = (char *) malloc(6*sizeof(char));

	if(a_str != NULL)
	{
		str = a_str;
	}
	else return 0;

	fread(str, sizeof(char), 6, file);

	if(*str == *matrix && fread(a_str, sizeof(char), 4, file) == 4)
		puts("\nФаил успешно проверен!\n");
	else {
		puts("\nФаил плохой!\n");
		exit(1);
	};
	return 1;
}
/*Создаю в фаиле бинарную матрицу с размером SIZE*/
void create_matrix(FILE *newfile)
{
	char *matrix = "MATRIX";
	int N = SIZE;
	fwrite(matrix, sizeof(char), 6, newfile); /* Записал в файл слово MATRIX*/
	fwrite(&N, sizeof(int), 1, newfile); /* Записал в файл размер MATRIX(SIZE)*/

	double str[SIZE*SIZE];
	register int i = 0;
	for (i = 0; i < 9; i++)
	{
		str[i] = (double) i;
	}
	fwrite(str, sizeof(double), SIZE*SIZE, newfile);/* Записал в фаил матрицу*/
}
int main(int argc, char* argv[])
{
	FILE *matrix_file; 
	matrix_file = fopen("matrix2.bin","w+b");

	create_matrix(matrix_file);
	
	void *ext_lib;

	double sum = 0;

	double (*powerfunc)(FILE *file, int size);

	ext_lib = dlopen("/home/andrey/8/lib.so",RTLD_LAZY);
	if(!ext_lib)
	{
		fprintf(stderr, "dlopen() error: %s/n",dlerror());
		return 1;
	};
 	
 	powerfunc = dlsym(ext_lib, argv[1]);

	printf("%lf\n",(*powerfunc)(matrix_file, SIZE));	
	fclose(matrix_file);
	dlclose(ext_lib);
	return 0;
}