#include "Interface.hpp"

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
        MY_STUDENT * student = (MY_STUDENT*)malloc(sizeof(MY_STUDENT));
        if(!student)
            error(ERROR_MEM_ALOC_ERROR);


        MY_STUDENT_init(student);
        MY_STUDENT_input(student);

        Stack * tmp = (Stack*)malloc(sizeof(Stack));
        if(!tmp)
            error(ERROR_MEM_ALOC_ERROR);


        tmp->ptr_fun_print = MY_STUDENT_print;
        tmp->ptr_fun_free = MY_STUDENT_free;
        tmp->ptr_fun_save = MY_STUDENT_save;
        tmp->ptr_fun_load = MY_STUDENT_load;
        tmp->typ = DATA_TYPE_STUDENT;
        tmp->data = (void *)student;

        stack_push(tmp);
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
}

void FindElement()
{
    /// \todo
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
    char filename[64];
    printf("Podaj nazwe pliku: ");
    fflush(stdin);
    gets(filename);
    stack_save(filename);
    printf("Pomyslnie zapisano do pliku: %s\n", filename);
}

void LoadFromFile()
{
    if(stack_getSize() > 0)
    {
        char option;
        printf("Stos nie jest pusty, czy chcesz wczytac dane i zastapic istniejace? (y/n): ");
        fflush(stdin);
        scanf("%c", &option);
        if(option != 'y')
            return;

        stack_free();
    }
    char filename[64];
    printf("Podaj nazwe pliku: ");
    fflush(stdin);
    gets(filename);
    stack_load(filename);
    printf("Pomyslnie wczytano z pliku: %s\n", filename);
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
        MY_STUDENT * student = (MY_STUDENT*)malloc(sizeof(MY_STUDENT));
        if(!student)
            error(ERROR_MEM_ALOC_ERROR);

        MY_STUDENT_init(student);
        MY_STUDENT_input(student);

        if( stack_find(student, DATA_TYPE_STUDENT) )
            printf("Objekt instnieje w stosie.\n");
        else
            printf("Objekt nie instnieje w stosie.\n");

        if(student)
            free(student);

        break;
    }


    default:
        error(ERROR_UNKNOWN_OBJECT);
        break;
    }
}
