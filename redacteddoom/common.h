#pragma once

#include "std/std.h"
#include "syscalls/syscalls.h"
#include "math/math.h"

#include "types.h"

#define stderr 
#define stdout
#define stdin  

typedef uintptr_t FILE;

#define sprintf(buf, fmt, ...) printf(fmt, ##__VA_ARGS__)
#define fprintf(buf, fmt, ...) printf(fmt, ##__VA_ARGS__)

#define strcpy(str1, str2) memcpy(str1, str2, strlen(str2,0))
#define strncpy(str1, str2, l) memcpy(str1, str2, l)

#define alloca malloc

typedef uint8_t byte;

void fclose(FILE *file);

#define NOT_IMPLEMENTED printf(">>>>>>>>>>>>>>> Function %s not implemented",__func__);