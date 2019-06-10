#include "MY_TRAIN.hpp"

MY_TRAIN* MY_TRAIN_Create()
{
	MY_TRAIN* ret = (MY_TRAIN*)malloc(sizeof(MY_TRAIN));
	if (!ret)
		exit(0);

	return ret;
}
void MY_TRAIN_Free(void * data)
{
    MY_TRAIN * train = (MY_TRAIN*)data;
    if(train->trace)
    {
        free(train->trace);
        train->trace = NULL;
    }
}
void MY_TRAIN_Input(MY_TRAIN * data)
{
    data->trace = (char*)malloc( sizeof(char) * 64 );
    printf("Podaj trase: ");
    scanf("%s", data->trace);
}

void MY_TRAIN_Print(void * data)
{
    MY_TRAIN * train = (MY_TRAIN*)data;
    printf("MY_TRAIN: Trasa: %s\n", train->trace);
}
