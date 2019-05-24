#include "MyStudent.hpp"

void MY_STUDENT_init(MY_STUDENT *ptr)
{
    ptr->nazwisko = "Unknown";
    ptr->rok = -1;
    ptr->kierunek = Unknown;

    ptr->size = 0;
}

void MY_STUDENT_input(MY_STUDENT *ptr)
{
    printf("Podaj nazwisko: ");
    char temp[64];
    scanf("%s", temp);

    ptr->nazwisko = (char*)malloc( sizeof(char) * (strlen(temp) + 1) );
    if(!ptr)
        error(ERROR_MEM_ALOC_ERROR);

    strcpy(ptr->nazwisko, temp);
    ptr->size = strlen(ptr->nazwisko);

    printf("Podaj rok urodzenia: ");
    scanf("%d", &ptr->rok);

    do
    {
        printf("Podaj kierunek:\n");
        printf( "[0] Fizyka \n"
                "[1] Matematyka \n"
                "[2] Informatyka \n");
        scanf("%d", &ptr->kierunek);
    }
    while(ptr->kierunek < 0 || ptr->kierunek >= Unknown);

}

void MY_STUDENT_print(void * data)
{
    MY_STUDENT *ptr = (MY_STUDENT *)data;

    printf( "\n"
            "Nazwisko: %s\n"
            "Rok: %d\n"
            "Kierunek: %s\n", ptr->nazwisko, ptr->rok, NazwaKierunku[ptr->kierunek]);
}

void MY_STUDENT_free(void ** data)
{
    if(data)
	{
		if (*data)
		{
		    MY_STUDENT *ptr = (MY_STUDENT *)(*data);
		    if (ptr->nazwisko)
                free(ptr->nazwisko);
            ptr->nazwisko = NULL;

			free(*data);
			*data = NULL;
		}
	}
}

int MY_STUDENT_save(void * data, FILE * file)
{
    MY_STUDENT * student = (MY_STUDENT*)data;

    //zapis danych z struktury
    if (fwrite(student, sizeof(MY_STUDENT), 1, file) != 1)
        return 0;

    //zapisz danych z wskaznika z nazwiskiem
    if (fwrite(student->nazwisko, sizeof(char), (size_t)(student->size+1), file) != (student->size+1))
        return 0;

    return 1;
}

int MY_STUDENT_load(void * data, FILE * file)
{
    MY_STUDENT * student = (MY_STUDENT*)data;
    if(fread(student, sizeof(MY_STUDENT), 1, file) != 1)
        return 0;


    student->nazwisko = (char*)malloc( sizeof(char) * (student->size+1) );
    if(fread(student->nazwisko, sizeof(char), student->size+1, file) != student->size+1)
        return 0;
/*
    printf("rok: %d\n", student->rok );
    printf("kierunek: %d\n", student->kierunek );
    printf("Size: %d\n", student->size );
    printf("nazw: %s\n", student->nazwisko );
*/
    return 1;
}
