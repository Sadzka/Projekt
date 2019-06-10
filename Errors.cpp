#include "stdafx.h"
#include "Errors.hpp"
#include "stack.hpp"
#include <string.h>
#include <stdlib.h>

const char *error_str_tab[8] = {
	"EBlad alokacji pamieci!",
	"NBrak elementow do pobrania!",
	"NNieznany typ obiektu, dodawanie przerwane!",
	"NNieznana operacja!",
	"NNie mozna otworzyc pliku!",
	"EBlad zapisu danych do pliku!",
	"ENieznany typ danych w pliku!",
	"NNie mozna zapisac pustego stosu!"
};

void error(enum ERRORS mess)
{
	puts(error_str_tab[mess] + 1);

	if (error_str_tab[mess][0] == 'E')
	{
		system("pause");
		stack_free();
		exit(1);
	}
}
