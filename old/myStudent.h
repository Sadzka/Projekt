#pragma once
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

enum Kierunek
{
    Informatyka,
    Matematyka,
    Fizyka,
    Unknown
};

struct MY_STUDENT
{
    char * nazwisko;
    int rok;
    Kierunek kierunek;
    //pomocnicza
    unsigned len;
};

void * CreateArray(int no_items);

void FreeArray(MY_STUDENT ** tab);
void * Add(MY_STUDENT * tab, char * nazwisko, const int & rok, Kierunek kierunek);

MY_STUDENT * GetFirstElement(MY_STUDENT * tab);
MY_STUDENT * Find(MY_STUDENT * tab, char * nazwisko);

void Save(MY_STUDENT * tab, char *filename);
void * Read(MY_STUDENT * tab, char *filename);

void PrintArray(MY_STUDENT * tab);
