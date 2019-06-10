#pragma once
#include <malloc.h>
#include "stdlib.h"
#include <stdio.h>

struct MY_TRAIN
{
	char* trace; //na przyk³ad: “Krakow–Warszawa”
};MY_TRAIN* MY_TRAIN_Create();void MY_TRAIN_Free(void * data);void MY_TRAIN_Input(MY_TRAIN * data);
void MY_TRAIN_Print(void * data);
