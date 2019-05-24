// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//
#pragma once

#ifndef __GNUC__
#include "targetver.h"

#include <stdio.h>

#define scanf_s scanf
#define printf_s printf

#endif // __GNUC__

#include <stdio.h>

enum DATA_TYPE
{
    DATA_TYPE_UNKNOWN = -1,
	DATA_TYPE_STUDENT = 0
};
