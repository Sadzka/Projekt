#pragma once
#include "stdafx.h"
#include "Errors.hpp"
#include <malloc.h>

typedef void (*PrintObject)(void *);
typedef void (*FreeObject)(void **);
typedef int  (*SaveObject)(void *, FILE*);
typedef int  (*LoadObject)(void *, FILE*);

struct Stack
{
    void * data;
    void * prev;
    DATA_TYPE typ;              //typ obiektu na ktory wskazuje 'data'
	PrintObject ptr_fun_print;  //wskaznik do funkcji, ktora wyswietla obiekt danych
	FreeObject  ptr_fun_free;   //wskaznik do funkcji z obslugi danych, ktora zwalnia pamiec
	SaveObject  ptr_fun_save;   //wskaznik do funkcji ktora zapisuje do pliku
	LoadObject  ptr_fun_load;   //wskaznik do funkcji ktora wczytuje z pliku
};

void stack_init();
void stack_free();

void stack_push(Stack * object);
void stack_print();
Stack * stack_pop();

void stack_fileerror(__int64 * filedesc, FILE * file, ERRORS blad); // dodatkowa obsluga czyszczenia pamieci podczas bledu
void stack_save(char * filename);
void stack_load(char * filename);

int stack_find(void * data, DATA_TYPE type);

int stack_getSize();
