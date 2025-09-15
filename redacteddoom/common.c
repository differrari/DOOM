#include "common.h"

void fclose(FILE *file){

}

void sprintf(char* buf, char* fmt, ...){
    __attribute__((aligned(16))) va_list args;
    va_start(args, fmt);
    string_format_va_buf(fmt, buf, args);
    va_end(args);
}