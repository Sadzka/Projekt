#include "stack.hpp"

#include "MyStudent.hpp"

//////SF po zapisie stosu do pliku zamykam program, 
//uruchomiam jego ponownie, odczytuje stos z pliku i proboje jego wyswietlic.
//Dostaje informacje o 0 elementach.

////////SF
//1. Przy pobieraniu ostatniego elementu ze stosu ten elment powinie by? wykre?lony ze stosu, a dane wy?wietlone na monitorze.
//Pierwsze nie jest wykonane.
//2. Poszukiwanie odbywa si? wed?ug pewnych kryteri?w.Je?li poszukujemy po nazwisku, to rok urodzenia oraz inne dane nas nie interesuj?.
//Dalej, algorytm powinien odnale?? wszystkie wchodzenia i wyprowadzi? dane na monitor, a nie stwierdza?, odnaleziono lub nie.

typedef void (*PrintObject)(void*);
#pragma warning (disable : 4996)

Stack * head;
static int elements = 0;

void stack_init()
{
    head = NULL;
}

void stack_free()
{
    int ile = 0;
    Stack * tmp = head;
    while(tmp != NULL)
    {
        (*(*tmp).ptr_fun_free)(&(*tmp).data);
        tmp = (Stack*)head->prev;
        free(head);
        head = tmp;
        ile++;
    }
    printf("Usunieto %d elementow.\n", ile);
    elements = 0;
}
/*
void stack_push(Stack * object)
{
    if(head == NULL)
    {
        head = object;
        object->prev = nullptr;
    }
    else
    {
        object->prev = head;
        head = object;
    }
    elements++;
}
*/
void stack_push(void * data, PrintObject fun_print, FreeObject fun_free,
	SaveObject fun_save, LoadObject fun_load, CompareObject fun_compare)
{ 
	Stack * object = (Stack*)malloc(sizeof(Stack));
	if(!object)
	    error(ERROR_MEM_ALOC_ERROR);

	if (head == NULL)
		object->prev = nullptr;
	else
		object->prev = head;

	head = object;
	elements++;

	head->data = data;
	head->ptr_fun_print = fun_print;
	head->ptr_fun_free = fun_free;
	head->ptr_fun_load = fun_load;
	head->ptr_fun_save = fun_save;
	head->ptr_fun_compare = fun_compare;

}

void stack_print()
{
    Stack * tmp = head;
    int ile = 0;
    while(tmp != NULL)
    {
        (*tmp->ptr_fun_print)(tmp->data);
        tmp = (Stack*)tmp->prev;
        ile++;
    }
    printf("Ilosc Elementow stosu: %d\n", ile);
}

Stack * stack_pop()
{
    if(head != NULL)
    {
        Stack * ret = head;
        head = (Stack*)head->prev;
        elements--;
        return ret;
    }
    return NULL;
}

int stack_getSize() { return elements; }

void stack_fileerror(__int64 * filedesc, FILE * file, ERRORS blad)
{
    if(file)
        fclose(file);
    if(filedesc)
        free(filedesc);

    error(blad);
}

void stack_save(char * filename)
{
    //otworzenie pliku

	FILE *file = fopen(filename, "wb");
	if (!file)
    {
        error(ERROR_FAILED_OPEN_FILE);
        return;
    }

    //wskazniki na poczatki danych obiektu w pliku
    unsigned int elements = stack_getSize();
	__int64 filepos = 0;
	__int64 * file_desc = (__int64 *)malloc((elements + 1) * sizeof(__int64));
	if(!file_desc)
        stack_fileerror(file_desc, file, ERROR_MEM_ALOC_ERROR);

    //zapis liczby elementow
	if ( fwrite(&elements, sizeof(unsigned int), 1, file) != 1)
        stack_fileerror(file_desc, file, ERROR_FAILED_DATA_SAVE);


	//rezerwacja miejsca w pliku dla file_descr
	_fseeki64(file, (elements + 1) * sizeof(__int64), SEEK_CUR);

	//zapis danych
    //int it; //SF warning przy kompilacji!
	unsigned it;
    for (it = 0; it < elements; ++it)
    {
        file_desc[it] = ftell(file);
        Stack * object = (Stack*)stack_pop();

        //pierwsze zapisuje typ obiektu
        if(!(*object->ptr_fun_save)(object->data, file) )
            stack_fileerror(file_desc, file, ERROR_FAILED_DATA_SAVE);

        //usuniecie zapisanego elementu ze stosu
        (*(*object).ptr_fun_free)(&(*object).data);
    }

	//zapisujemy wskazniki pozycji dla kazdego obiektu
	file_desc[it] = ftell(file);
    _fseeki64(file, sizeof(unsigned int), SEEK_SET);
	if (fwrite(file_desc, sizeof(__int64), elements + 1, file) != elements + 1)
        stack_fileerror(file_desc, file, ERROR_FAILED_DATA_SAVE);


	if(file)
		fclose(file);
	file = NULL;


	if (file_desc)
		free(file_desc);
	file_desc = NULL;

	printf("Zapisano pomyslnie\n");
}

void stack_load(char * filename)
{
	unsigned int elements = 0, it, rec;
	__int64 rec_len;
	__int64 *file_desc = NULL;

	FILE *file = fopen(filename, "rb");
	if(!file)
    {
        error(ERROR_FAILED_OPEN_FILE);
        return;
    }

    //wczytanie liczby elementow
	if(fread(&elements, sizeof(unsigned int), 1, file) != 1)
        stack_fileerror(file_desc, file, ERROR_FAILED_DATA_SAVE);
    //printf("%d\n", elements);

    //wczytanie pozycji elementow
	file_desc = (__int64 *)malloc((elements + 1) * sizeof(__int64));
	if(!file_desc)
		error(ERROR_MEM_ALOC_ERROR);

	if(fread(file_desc, sizeof(file_desc[0]), elements + 1, file) != elements + 1)
        stack_fileerror(file_desc, file, ERROR_FAILED_DATA_SAVE);

	for (it = 0; it < elements; ++it)
	{
		rec = elements - it - 1;
		rec_len = file_desc[rec + 1] - file_desc[rec];

		//SF fseek nie poradzi z dlugimi plikami. Trzeba fseek64.
		_fseeki64(file, file_desc[rec], SEEK_SET);

		//Stack * object = (Stack*)malloc(sizeof(Stack));
		//wczytanie typu danych

		void* data = NULL;
		DATA_TYPE typ;
		if(fread(&typ, sizeof(DATA_TYPE), 1, file) != 1)
            stack_fileerror(file_desc, file, ERROR_FAILED_DATA_SAVE);

        //ustawienie funkcji wczytywania do odpowiedniego typu danych
		switch(typ)
		{
        case DATA_TYPE_STUDENT:
			data = MY_STUDENT_create();
			MY_STUDENT_load(data, file);
			stack_push(data, MY_STUDENT_print, MY_STUDENT_free, MY_STUDENT_save, MY_STUDENT_load, MY_STUDENT_compare);
            break;
        default:
            error(ERROR_UNKNOWN_DATA_TYPE);
			break;
		}


		//SF W kontenerze nie powinno byc zadnego typu danych, na przyklad, MY_STUDENT
		//stack_push(data);
	}

	printf("Wczytano %d elementow. \n", elements);

	if (file_desc)
		free(file_desc);
	file_desc = NULL;

	if (file)
		fclose(file);
	file = NULL;
}

void stack_find(void * data, int typ)
{
	//SF W kontenerze nie powinno byc zadnego typu danych.
	//MY_STUDENT * student = (MY_STUDENT*)data; - to trzeba przeniesc do danych.

	Stack* tmp = head;
	int ile = 0; //do wypisania ze elementu nie znaleziono
	while (tmp != NULL)
	{
		if ((tmp->ptr_fun_compare)(tmp->data, data, typ))
		{
			tmp->ptr_fun_print(tmp->data);
			ile++;
		}
		
		tmp = (Stack*)tmp->prev;
	}
	if (ile == 0)
		printf("Nie znaleziono zadnych elementow spelniajacych kryteria.\n");

	/*
    switch(type)
    {
		////SF kontener nic nie zna o typach danych
    case DATA_TYPE_STUDENT:
        //MY_STUDENT * student = (MY_STUDENT*)data;

		//MY_STUDENT* student = (MY_STUDENT*)data;
        
			//SF Kontener nie powinien wiedziec nic o typach danych
			
            MY_STUDENT * student2 = (MY_STUDENT*)tmp->data;
            if( student2->rok == student->rok
            &&  student2->kierunek == student->kierunek
            &&  strcmp(student2->nazwisko, student->nazwisko) == 0)
            {
                return 1;
            }
			

        break;
    //default: //zabezpieczone w interface
    }
	*/
}

void stack_getLast()
{
    if(elements != 0)
    {
		Stack* pop = stack_pop();
        if(pop)
        {
            printf("Ostatni element: ");
            (pop->ptr_fun_print)(pop->data);
        }
    }
    else error(ERROR_NO_ELEMENTS);
}
