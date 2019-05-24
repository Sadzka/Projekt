#pragma once
#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>

enum ERRORS
{
	ERROR_MEM_ALOC_ERROR = 0,
	ERROR_NO_ELEMENTS,
	ERROR_UNKNOWN_OBJECT,
	ERROR_UNKNOWN_OPERATION,
	ERROR_FAILED_OPEN_FILE,
	ERROR_FAILED_DATA_SAVE,
	ERROR_UNKNOWN_DATA_TYPE,
	ERROR_TOTAL
};

void error(enum ERRORS mess);
