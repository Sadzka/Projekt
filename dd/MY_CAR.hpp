#pragma once
#include <malloc.h>
#include "stdlib.h"
#include <stdio.h>
#include <string.h>

struct MY_CAR
{
	char* model; //nazwa modelu
	int year; //rok sprzeda¿y
};MY_CAR* MY_CAR_Create();void MY_CAR_Free(void * data);void MY_CAR_Input(MY_CAR * data);
void MY_CAR_Print(void * data);
