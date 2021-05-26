#pragma once
#include "structs.h"
#include "stdlib.h"
#include "string.h"
#include "stdio.h"

int isFileExist(database_files* database, const char* filename);
int addFile(database_files* database, const char* filename);
int deleteFile(database_files* database, const char* filename);