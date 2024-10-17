#ifndef MASTER_H
#define MASTER_H

#include <stdbool.h>
#include <stdlib.h>

#define NO_IDX (-1)
#define $min(x, y) ((x) < (y) ? (x) : (y))
#define $abs(x) ((x) < 0 ? (-x) : (x))

int     lib_count_ws(const char * cstr);
int     lib_word_len(const char * cstr);
int     lib_next_ws(const char * cstr);
int     lib_parse_int(const char * cstr, int * x);
int     lib_match_prefix(const char * cstr, const char * prefix);
void *  lib_mem_dup(const void * mem, int size);

#endif