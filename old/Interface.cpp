#include "Interface.h"

void _CheckIfCreated()
{
    if(tab != NULL)
    {
        char ch;

        printf("Tablica jest stworzona, czy chcesz ja usunac i stworzyc nowa? (y/n): ");
        scanf(" %c", &ch);
        if(ch != 'y')
            return;
    }
    _InterfaceDelete();
    _InterfaceCreate();
}

void _InterfaceCreate()
{
    int ile;
    printf("Podaj ilosc elementow: ");
    scanf("%d", &ile);
    tab = (MY_STUDENT*)CreateArray(ile);

    if(tab) printf("Stworzono tablice o rozmiarze %d.\n", ile);
    else printf("todo: allocation error \n");
}

void _InterfaceDelete()
{
    if(tab != NULL)
    {
        FreeArray(&tab);
        printf("Tablica zostala usunieta.\n");
    }
}

void _InterfaceAdd()
{
    if(!tab)
    {
        printf("Pierwsze stworz tablice!\n");
        return;
    }

    char * nazwisko = (char*)malloc(sizeof(char) * 64);
    int rok;
    Kierunek kierunek;

    printf("Podaj nazwisko: ");
    scanf("%s64", nazwisko);

    printf("Podaj rok urodzenia: ");
    scanf("%d", &rok);


    printf("[0] Informatyka\n");
    printf("[1] Matematyka\n");
    printf("[2] Fizyka\n");
    do{
        printf("Podaj kierunek: ");
        scanf("%d", &kierunek);
    } while(kierunek < 0 || kierunek >= Unknown);

    tab = (MY_STUDENT*)Add(tab, nazwisko, rok, kierunek);
}

void _InterfacePrint()
{
    PrintArray(tab);
}

void _InterfacePrintFirst()
{

    MY_STUDENT * student = GetFirstElement(tab);
    if(student == NULL)
        printf("Nie znaleziono!\n");

    printf("%s\t", student->nazwisko);
    printf("%d\t", student->rok);
    printf("%d\n", (int)student->kierunek);

}

void _InterfaceFind()
{
    char * nazwisko = (char*)malloc(sizeof(char) * 64);
    printf("Podaj nazwisko do wyszukania: ");
    scanf("%s64", nazwisko);

    MY_STUDENT * student = Find(tab, nazwisko);
    if(student == NULL)
        printf("Nie znaleziono!\n");

}

void InterfacePrint()
{
    printf("[1]\t Stworz tablice\n");
    printf("[2]\t Usun tablice\n");
    printf("[3]\t Dodaj element\n");
    printf("[4]\t Wypisz pierwszy element\n");
    printf("[5]\t Znajdz element\n");

    printf("[6]\t Zapisz tablice do pliku\n");
    printf("[7]\t Wczytaj tablice z pliku\n");

    printf("[8]\t Wypisz tablice\n\n");

    printf("[0]\t Wyjdz\n");
}

void InterfaceHandleCommand(int ch)
{
    switch(ch)
    {
    case 0:
        _InterfaceDelete();
        break;
    case 1:
        _CheckIfCreated();
        break;
    case 2:
        _InterfaceDelete();
        break;
    case 3:
        _InterfaceAdd();
        break;
    case 4:
        _InterfacePrintFirst();
        break;
    case 5:
        _InterfaceFind();
        break;
    case 6:

        break;
    case 7:

        break;
    case 8:
        _InterfacePrint();
        break;

    default:
        printf("Invalid command!\n");
    }
}
