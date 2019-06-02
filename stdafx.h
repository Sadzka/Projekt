// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//
#pragma once

#include "targetver.h"
#include <stdio.h>


enum DATA_TYPE
{
    DATA_TYPE_UNKNOWN = -1,
	DATA_TYPE_STUDENT = 0
};

void clear_stdio();