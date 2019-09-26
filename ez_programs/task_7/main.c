#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "support.h"
#include "sort.h"
#include "work.h"

#define INNAME "in.txt"
#define OUTNAME "out.txt"

int main() {
	if(delete(INNAME) == 0)
	{
		return 0;
	}

	sort(INNAME, OUTNAME);
		
	return 0;
}