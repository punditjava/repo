#include <stdio.h>
#include <stdarg.h>

double sum(int n, ...)
{
	double result = 0.0;
	va_list factor;
	va_start(factor,n);
	for(; n>0; n--)
	{
		result += va_arg(factor, double);
	}
	va_end(factor);
	return result;
}

int main()
{
	double res = sum(5, (double) 1, 1.2, 1.3, 1.4, 1.5);
	printf("%f\n", res );
	return 0;
}
