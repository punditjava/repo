#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "support.h"
#include "delete.h"

#define INNAME "in.txt"
#define OUTNAME "out.txt"

int main() {

	delete(INNAME, OUTNAME);
		
	return 0;
}