#include <stdio.h>
#include <inttypes.h>
void binary (double d)
{
    uint64_t *p1, a=0;
    int i=1;
    void *p2;
    uint64_t mask;
    p2 = &d;
    p1 = (uint64_t*)p2;
    mask = ~((~a)>>1);
    for (;mask!=0; mask=mask>>1,i++)
    {
        if ((*p1 & mask) == 0) 
        {
            putchar('0');
        }
        else
            putchar('1');
    }
    putchar ('\n');
}

int main()
{
    double c;
    scanf("%lf",&c);
    binary (c);
    return 0;
}
