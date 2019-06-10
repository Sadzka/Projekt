#include "Interface.hpp"

#pragma warning (disable : 4996)

void MyMenu()
{
    stack_init();

    int select;
    while (1)
    {
        printf( "[0] Add object\n"
                "[1] Print all objects\n"
                "[3] Get first element\n"
                "[4] Save stack to File\n"
                "[5] Load stack from File\n"
                "[6] Free stack\n"
                "[7] Find object\n"
                "[8] Exit\n");

        scanf("%d", &select);

        switch (select)
        {
        case 0:
            AddObject();
            break;
        case 1:
            PrintAllObjects();
            break;
        case 3:
            GetFirstElement();
            break;
        case 4:
            SaveToFile();
            break;
        case 5:
            LoadFromFile();
            break;
        case 6:
            FreeStack();
            break;
        case 7:
            FindObject();
            break;
        case 8:
            Exit();
            break;

        default:
            error(ERROR_UNKNOWN_OPERATION);

        };
        system("pause");
        system("cls");
    }
}

//SF Tu tez Pan zbyt duzo wyciaga "do gory".
//Ja by "oposcil" tworzenie obiektu MY_STUDENT do obslugi studenta,
//a tworzenie kolejnego elementu stosu - do obslugi stosu.
//Wtedy interfejs staje bardziej niezalezny od kontenera i od danych,
//a obsluga odpowiednich obiektow znajduje sie na swoim miejscu.

void AddObject()
{
    int typ;

    printf( "Types:\n"
            "[0] MyStudent\n");
    scanf("%d", &typ);

    switch (typ)
    {
    case DATA_TYPE_STUDENT:
    {
/*
        MY_STUDENT * student = (MY_STUDENT*)malloc(sizeof(MY_STUDENT));
        if(!student)
            error(ERROR_MEM_ALOC_ERROR);


        MY_STUDENT_init(student);
        MY_STUDENT_input(student);

		////SF Nie jest to naturalnie, ze interfejs tworzy obiekt stosu. To stos powinien tworzyc swoj wlasny obiekt.
        Stack * tmp = (Stack*)malloc(sizeof(Stack));
        if(!tmp)
            error(ERROR_MEM_ALOC_ERROR);

        tmp->ptr_fun_print = MY_STUDENT_print;
        tmp->ptr_fun_free = MY_STUDENT_free;
        tmp->ptr_fun_save = MY_STUDENT_save;
        tmp->ptr_fun_load = MY_STUDENT_load;
        tmp->typ = DATA_TYPE_STUDENT;
        tmp->data = (void *)student;
*/

		MY_STUDENT* data = MY_STUDENT_create();
        if(!data)
            error(ERROR_MEM_ALOC_ERROR);

        MY_STUDENT_init( data );
        MY_STUDENT_input( data );

		stack_push(data, MY_STUDENT_print, MY_STUDENT_free, MY_STUDENT_save, MY_STUDENT_load, MY_STUDENT_compare);
        printf("Dodano rekord.\n");
        break;
    }
    default:
        error(ERROR_UNKNOWN_OBJECT);
        break;
    };
}

void PrintAllObjects()
{
    stack_print();
}

void FreeStack()
{
    stack_free();
}

void GetFirstElement()
{
	//SF To tez nie sprawa interfejsu "wyciagac caly stos do gory".
	//Tu trzeba by bylo stworzyc funkcje wydruku pierwszego elementu w obsludze stosu.

/*

    Stack * tmp = stack_pop();
    if(tmp)
    {
        printf("Pobrano dane: ");
        (*tmp->ptr_fun_print)(tmp->data);
        (*(*tmp).ptr_fun_free)(&(*tmp).data);
    }
    else
    {
        error(ERROR_NO_ELEMENTS);
    }
*/
    stack_getLast();
}

void Exit()
{
    printf("Exit...\n");
    stack_free();

    system("pause");
    exit(1);
}

void SaveToFile()
{
	if (stack_getSize() == 0)
	{
		error(ERROR_NULL_SIZE);
		return;
	}

    char filename[64];
    printf("Podaj nazwe pliku:\n");
    
	clear_stdio();
	gets_s(filename, 63);

    stack_save(filename);
}

void LoadFromFile()
{
    if(stack_getSize() > 0)
    {
        char option;
        printf("Stos nie jest pusty, czy chcesz wczytac dane i zastapic istniejace? (y/n): ");
		clear_stdio();
        scanf("%c", &option);
        if(option != 'y')
            return;

        stack_free();
    }
    char filename[64];
    printf("Podaj nazwe pliku: ");

	clear_stdio();
	gets_s(filename);

    stack_load(filename);
}

void FindObject()
{
    printf("Jakiego typu objekt chcesz znalezc?\n");
    printf( "Types:\n"
            "[0] MyStudent\n");

    int typ;
    scanf("%d", &typ);
    switch(typ)
    {
    case DATA_TYPE_STUDENT:
    {
		int kryterium;
		printf("Wybierz kryterium?\n"
			"[0] Nazwisko\n"
			"[1] Kierunek\n"
			"[2] Rok Studiow\n");
		scanf("%d", &kryterium);

		if (kryterium == 0)
		{
			char nazwisko[255];
			printf("Podaj nazwisko: ");
			scanf("%s", nazwisko);
			stack_find(nazwisko, kryterium, DATA_TYPE_STUDENT);
		}
		else if (kryterium == 1)
		{
			int kierunek;
			printf("Podaj kierunek \n"
				   "[0] Fizyka\n"
				   "[1] Matematyka\n"
				   "[2] Informatyka\n");
			scanf("%d", &kierunek);
			if (kierunek < 0 || kierunek >= Kierunek::Unknown)
			{
				printf("Niepoprawny kierunek!\n");
				return;
			}
			stack_find(&kierunek, kryterium, DATA_TYPE_STUDENT);
		}
		else if (kryterium == 2)
		{
			printf("Podaj rok: ");
			int rok;
			scanf("%d", &rok);
			stack_find(&rok, kryterium, DATA_TYPE_STUDENT);
		}
		else
		{
			printf("Niepoprawne kryterium. \n");
		}


    }
        break;


    default:
        error(ERROR_UNKNOWN_OBJECT);
        break;
    }
}

