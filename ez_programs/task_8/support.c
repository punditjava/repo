#include <stdio.h>
double sum_main_diagonal(FILE *file, int SIZE)
{	
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