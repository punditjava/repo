#include<stdio.h>
#include <stdlib.h>
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

double sum_main_diagonal(FILE *file)
{	
	check_file(file);

	double result = 0.0;
	int label = 10;/*Здесь 10 это размер слова MATRIX и его SIZE */
	int i = 0;
	puts("Элементы главной диагонали :");
	for (i = 0; i < SIZE; ++i)
	{	
		double str[1]; /* Вспомогательный массив*/

		fseek(file, label, SEEK_SET); /* Перемещаемся по массиву */
		fread(str,sizeof(double),1,file); /*Считываем элемент на главной диагонали */
		printf("%lf ", str[0]); /* Вывожу элемент*/
		result += str[0];
		label += sizeof(double) * (SIZE + 1); /* Ставим метку относительно начала прошлого элемента */
	}
	return result;
}

void reset_columns(FILE *file)
{
	check_file(file);

	int label = 10;
	int i,j = 0;
	double O = 0.0;
	for(i = 0; i < SIZE; ++i)
	{
		for (j = 0; j < 2; ++j)
		{
			fseek(file, label, SEEK_SET);
			fwrite(&O, sizeof(double), 1, file);
			if(j == 0)
			{
				label += sizeof(double) * 2;
			}	
		}
		label += sizeof(double);
	}

	double str[SIZE*SIZE];
	fseek(file, 10, SEEK_SET);
	fread(str, sizeof(double), SIZE*SIZE, file);
	puts("Обнулил элементы в нечётных столбцах");
	for (i = 0; i < SIZE*SIZE; ++i)
	{
		printf("%lf\n",str[i]);

	}
}

int main()
{
	FILE *matrix_file; 
	matrix_file = fopen("matrix2.bin","w+b");

	create_matrix(matrix_file);
	
	double sum;
	sum = sum_main_diagonal(matrix_file);
	puts("\nСумма на главной диагонали :");
	printf("%lf\n",sum);	

	reset_columns(matrix_file);

	fclose(matrix_file);
	return 0;
}