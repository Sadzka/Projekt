#pragma once
#include "stdafx.h"
#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include "Errors.hpp"

enum Kierunek
{
    Fizyka = 0,
    Matematyka = 1,
    Informatyka = 2,
    Unknown
};

const static char * NazwaKierunku[] =
{
    "Fizyka",
    "Matematyka",
    "Informatyka"
};

struct MY_STUDENT
{
    char * nazwisko;
    int rok;
    Kierunek kierunek;

    size_t size; //nazwisko.length()
};

void MY_STUDENT_init(MY_STUDENT* ptr);
void MY_STUDENT_input(MY_STUDENT* ptr);
void MY_STUDENT_print(void* data);
void MY_STUDENT_free(void** data);
int MY_STUDENT_save(void* data, FILE * file);
int MY_STUDENT_load(void* data, FILE * file);

int MY_STUDENT_compare(void* data1, void* data2);
