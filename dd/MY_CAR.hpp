#pragma once
#include <malloc.h>
#include "stdlib.h"
#include <stdio.h>
#include <string.h>

struct MY_CAR
{
	char* model; //nazwa modelu
	int year; //rok sprzeda�y
};
void MY_CAR_Print(void * data);