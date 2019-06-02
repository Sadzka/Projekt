#include "stdafx.h"

void clear_stdio()
{
	char c;
	while ((c = getchar()) != '\n'
		&& c != EOF);
}