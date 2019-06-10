#pragma once
#include <stdlib.h>
#include "MY_CAR.hpp"
#include "MY_TRAIN.hpp"

typedef void(*PTR_FUN_FREE)(void*);
typedef void(*PTR_FUN_PRINT)(void*);

struct TAB_DYN
{
	void* pDat; //wskaünik do danych.
	PTR_FUN_FREE pFunFree; //wskaünik do funkcji, ktÛra zwalnia dane.
	PTR_FUN_PRINT pFunPrint; //wskaünik do funkcji, ktÛra wyprowadzi dane na monitor.
	static int last; //Pierwszy wolny element tablicy
};void TAB_DYN_Create(unsigned no);void TAB_DYN_Free();void TAB_DYN_Add(void * data, PTR_FUN_FREE fun_free, PTR_FUN_PRINT fun_print);void TAB_DYN_Print();
