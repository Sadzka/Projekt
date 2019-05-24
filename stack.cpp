#include "stack.hpp"

#include "MyStudent.hpp"
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

    //MY_STUDENT * stud = (MY_STUDENT*)head->data;
    //printf("Nazwisko: %d\n", strlen(stud->nazwisko) );
    //printf("Nazwisko: %s\n", stud->nazwisko );
    //printf("Head: %d\n", head);
    //printf("Prev: %d\n", head->prev);
}

void stack_print()
{
    Stack * tmp = head;
    int ile = 0;
    //printf("Head: %d\n", head);
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
        /*
        Stack * temp = head;
        void * ret = head->data;
        head = (Stack*)head->prev;
        free(temp);
        elements--;
        return ret;
        */

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
	fseek(file, (elements + 1) * sizeof(__int64), SEEK_CUR);

	//zapis danych
    int it;
    for (it = 0; it < elements; ++it)
    {
        file_desc[it] = ftell(file);
        Stack * object = (Stack*)stack_pop();

        //pierwsze zapisuje typ obiektu
        if (fwrite( &object->typ, sizeof(DATA_TYPE), 1, file) != 1)
            stack_fileerror(file_desc, file, ERROR_FAILED_DATA_SAVE);
        if(!(*object->ptr_fun_save)(object->data, file) )
            stack_fileerror(file_desc, file, ERROR_FAILED_DATA_SAVE);

        //usuniecie zapisanego elementu ze stosu
        (*(*object).ptr_fun_free)(&(*object).data);
    }

	//zapisujemy wskazniki pozycji dla kazdego obiektu
	file_desc[it] = ftell(file);
    fseek(file, sizeof(unsigned int), SEEK_SET);
	if (fwrite(file_desc, sizeof(__int64), elements + 1, file) != elements + 1)
        stack_fileerror(file_desc, file, ERROR_FAILED_DATA_SAVE);


	if(file)
		fclose(file);
	file = NULL;


	if (file_desc)
		free(file_desc);
	file_desc = NULL;
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

		fseek(file, file_desc[rec], SEEK_SET);

		Stack * object = (Stack*)malloc(sizeof(Stack));
		//wczytanie typu danych
		if(fread(&object->typ, sizeof(DATA_TYPE), 1, file) != 1)
            stack_fileerror(file_desc, file, ERROR_FAILED_DATA_SAVE);

        //ustawienie funkcji wczytywania do odpowiedniego typu danych
		switch(object->typ)
		{
        case DATA_TYPE_STUDENT:
            object->data = (MY_STUDENT*)malloc(sizeof(MY_STUDENT));
            object->ptr_fun_print = MY_STUDENT_print;
            object->ptr_fun_free = MY_STUDENT_free;
            object->ptr_fun_save = MY_STUDENT_save;
            object->ptr_fun_load = MY_STUDENT_load;
            break;
        default:
            error(ERROR_UNKNOWN_DATA_TYPE);
		}

        //wczytanie danych do okreslonego typu
        if( !(*object->ptr_fun_load)(object->data, file) )
        {
            if(object->data)
                free(object->data);
            if(object)
                free(object);

            return;
        }

        MY_STUDENT * student = (MY_STUDENT*)object->data;
        stack_push(object);

		/*
		if(fread(&tab[rec], sizeof(tab[rec]), 1, file) != 1)
			MyExit(file, tab, file_desc);

		tab[rec].model = (char *)malloc(tab[rec].len*sizeof(char));
		if(!tab[rec].model)
			MyExit(file, tab, file_desc);

		if(fread(tab[rec].model, sizeof(char), tab[rec].len, file) != tab[rec].len)
			MyExit(file, tab, file_desc);
        */
	}

	if (file_desc)
		free(file_desc);
	file_desc = NULL;

	if (file)
		fclose(file);
	file = NULL;
}
