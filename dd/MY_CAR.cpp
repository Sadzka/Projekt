#include "MY_CAR.hpp"

MY_CAR* MY_CAR_Create()
{
	MY_CAR* ret = (MY_CAR*)malloc( sizeof(MY_CAR) );
	if (!ret)
		exit(0);

	return ret;
}
void MY_CAR_Free(void * data)
{
    MY_CAR * car = (MY_CAR*)data;
    if(car->model)
    {
        free(car->model);
        car->model = NULL;
    }
}
void MY_CAR_Input(MY_CAR * data)
{

    data->model = (char*)malloc( sizeof(char) * 64 );
    printf("Podaj model: ");
    scanf("%s", data->model);

    printf("Podaj rok: ");
    scanf("%d", &data->year);
}

void MY_CAR_Print(void * data)
{
    MY_CAR * car = (MY_CAR*)data;
    printf("MY_CAR: Model: %s, Rok: %d\n", car->model, car->year);
}
