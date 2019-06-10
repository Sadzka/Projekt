#pragma once
#include <stdlib.h>
#include "MY_CAR.hpp"
#include "MY_TRAIN.hpp"

typedef void(*PTR_FUN_FREE)(void*);
typedef void(*PTR_FUN_PRINT)(void*);

struct TAB_DYN
{
	void* pDat; //wska�nik do danych.
	PTR_FUN_FREE pFunFree; //wska�nik do funkcji, kt�ra zwalnia dane.
	PTR_FUN_PRINT pFunPrint; //wska�nik do funkcji, kt�ra wyprowadzi dane na monitor.
	static int last; //Pierwszy wolny element tablicy
};