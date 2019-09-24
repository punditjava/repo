#include <stdio.h>

void Func2(int number)
{
	register int i = 1;
	unsigned int mask = ~((~0u) >> 1);
	for (mask = ~((~0u) >> 1); mask != 0; mask >>= 1, ++i)
	{
		putchar(mask & (unsigned int)number ? '1' : '0');
		if (i % 8 == 0 && mask != 1)
		{
			putchar('|');
			continue;
		}
		else 
		{
			if (i % 4 == 0)
				putchar(' ');
		}
	}
}
int main(void) 
{ 
	Func2(10);
	return 0;
}
