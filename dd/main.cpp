#include <stdlib.h>
#include <stdio.h>
#include "MY_DYN.hpp"

int main()
{
    printf("Podaj ilosc elementow tablicy: ");
    int ile;
    scanf("%d", &ile);
    TAB_DYN_Create(ile);

    int option;
    while(true)
    {
        printf("[0] Dodaj obiekt\n"
               "[1] Wydrukuj tablice\n"
               "[2] Zakoncz\n" );
        scanf("%d", &option);
        switch(option)
        {
        case 0:
        {
            printf("[0] car\n"
                   "[1] train\n");
            int typ;
            scanf("%d", &typ);
            if(typ == 0)
            {
                MY_CAR * car = MY_CAR_Create();
                MY_CAR_Input(car);
                TAB_DYN_Add( (void*)car, &MY_CAR_Free, &MY_CAR_Print);
            }
            else if(typ == 1)
            {
                MY_TRAIN * train = MY_TRAIN_Create();
                MY_TRAIN_Input(train);
                TAB_DYN_Add( (void*)train, MY_TRAIN_Free, MY_TRAIN_Print);
            }

            break;
        }
        case 1:
            TAB_DYN_Print();
            break;
        case 2:
            TAB_DYN_Free();
            return 0;
            break;
        default:
            printf("Nieznana opcja\n");
            break;
        }

        system("pause");
        system("cls");
    }
    return 0;
}
