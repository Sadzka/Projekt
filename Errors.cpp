#include "Errors.hpp"
#include "stack.hpp"

static char *error_str_tab[] = {
	"EBlad alokacji pamieci!",
	"NBrak elementow do pobrania!",
	"NNieznany typ obiektu, dodawanie przerwane!",
	"NNieznana operacja!",
	"NNie mozna otworzyc pliku!",
	"EBlad zapisu danych do pliku!",
	"ENieznany typ danych w pliku!"
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
