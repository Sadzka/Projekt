#pragma once
#include "myStudent.h"
#include <iostream>

static MY_STUDENT * tab = NULL;

void _CheckIfCreated();
void _InterfaceCreate();
void _InterfaceDelete();
void _InterfaceAdd();
void _InterfacePrint();
void _InterfacePrintFirst();
void _InterfaceFind();


void InterfacePrint();
void InterfaceHandleCommand(int ch);
