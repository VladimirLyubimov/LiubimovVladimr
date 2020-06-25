#pragma once
#include <stdio.h>
#include <png.h>
#include <stdlib.h>
#include "struct_png.h"

int ReadFile(char* filename, png* image);
int OutputImage(char* filename, png* image);