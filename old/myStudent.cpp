#include "myStudent.h"

int _msize;

void * CreateArray(int no_items)
{
	MY_STUDENT * tab = (MY_STUDENT*)malloc(no_items * sizeof(MY_STUDENT));
	if (tab)
    {
		memset(tab, 0, no_items * sizeof(MY_STUDENT));
		_msize = no_items;
        return tab;
    }
    return 0;
}

void FreeArray(MY_STUDENT ** tab)
{
    if(*tab)
    {
        for(int i = 0; i < _msize; i++)
        {
            if( &tab[i]->nazwisko)
                free( &tab[i]->nazwisko);

        }
        free(*tab);
    }

    *tab = NULL;
}

void * Add(MY_STUDENT * tab, char * nazwisko, const int & rok, Kierunek kierunek)
{
    int last = _msize;
    tab = (MY_STUDENT*)realloc( tab, (_msize + 1) * sizeof(MY_STUDENT));
    if(tab)
    {
        tab[last].nazwisko = nazwisko;
        tab[last].rok = rok;
        tab[last].kierunek = kierunek;

        _msize++;
        return tab;
    }
    return NULL;
}

MY_STUDENT * GetFirstElement(MY_STUDENT * tab)
{
    if(tab)
        return &tab[0];
    return NULL;
}

MY_STUDENT * Find(MY_STUDENT * tab, char * nazwisko)
{
    for (int i = 0; i < _msize; i++ )
    {
        if(tab[i].nazwisko == nazwisko)
        {
            return &tab[i];
        }
    }
    return NULL;
}

void Save(MY_STUDENT * tab, char *filename)
{
    FILE * file = fopen(filename, "wb");
    if(!file)
        return;

    unsigned ile = (unsigned)_msize;

    fwrite(&ile, sizeof(unsigned), 1, file);
    for (int it = 0; it < _msize; ++it)
	{
	    tab[it].len = strlen(tab[it].nazwisko) + 1;

		fwrite(&tab[it],         sizeof( tab[0] ),  1,           file );
		fwrite(tab[it].nazwisko, sizeof( char ),    tab[it].len, file );
	}
	fclose(file);
}

void * Read(MY_STUDENT * tab, char *filename)
{
    int no_items;
	if (tab)
        FreeArray(&tab);

	FILE * file = fopen(filename, "rb");
    if(!file)
        return 0;

	fread(&no_items, sizeof(unsigned int), 1, file);
	printf("%d\n", no_items);

	tab = (MY_STUDENT*)CreateArray( no_items);

    for (int it = 0; it < no_items; ++it)
	{

	    fread(&tab[it], sizeof(MY_STUDENT), 1, file);

        tab[it].nazwisko = (char*)malloc( (tab[it].len+1) * sizeof(char) );
        if(!tab[it].nazwisko) return NULL;

		fread(tab[it].nazwisko, sizeof(char), tab[it].len, file);
		//tab[it].nazwisko[tab[it].len] = '\0';
	}

	fclose(file);
	return tab;
}

void PrintArray(MY_STUDENT * tab)
{
    for(int i=0; i< _msize; i++ )
    {
        printf("%s\t", tab[i].nazwisko);
        printf("%d\t", tab[i].rok);
        printf("%d\n", (int)tab[i].kierunek);
    }
}
