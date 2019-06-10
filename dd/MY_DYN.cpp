#include "MY_DYN.hpp"

TAB_DYN* tablica;int size = 0;
int TAB_DYN::last = 0;

void TAB_DYN_Create(unsigned no)
{
	size = no;
	tablica = (TAB_DYN*)malloc(sizeof(TAB_DYN) * size);
	if (!tablica)
		exit(0);
}

void TAB_DYN_Free()
{
    for(int i=0; i<TAB_DYN::last; i++)
        tablica[i].pFunFree( tablica[i].pDat );

    free(tablica);
    tablica = NULL;
}

void TAB_DYN_Add(void* data, PTR_FUN_FREE fun_free, PTR_FUN_PRINT fun_print)
{
    if(TAB_DYN::last >= size)
    {
        printf("Brak miejsca w tablicy!\n");
        return;
    }


    tablica[TAB_DYN::last].pDat = data;
    tablica[TAB_DYN::last].pFunFree = fun_free;
    tablica[TAB_DYN::last].pFunPrint = fun_print;

/*
	(tablica + TAB_DYN::last )->pDat = data;
	(tablica + TAB_DYN::last )->pFunFree = fun_free;
	(tablica + TAB_DYN::last )->pFunPrint = fun_print;
*/

	TAB_DYN::last++;
}

void TAB_DYN_Print()
{
	for (int i = 0; i < TAB_DYN::last; i++)
		(tablica[i].pFunPrint)(tablica[i].pDat);
}
