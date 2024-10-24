#ifndef LIB_H
#define LIB_H

#include <stdbool.h>
#include <stdlib.h>
#include <assert.h>

#define NO_IDX (-1)
#define $min(x, y) ((x) < (y) ? (x) : (y))
#define $abs(x) ((x) < 0 ? (-x) : (x))

typedef struct
{
    char *  cstr;
    int     len;
}   Str;

int     lib_get_line(char * buff, int bsize);
int     lib_count_ws(const char * cstr);
int     lib_word_len(const char * cstr);
int     lib_next_ws(const char * cstr);
int     lib_parse_int(const char * cstr, int * x);
int     lib_parse_int_len(const char * cstr, int len, int * x);
int     lib_match_prefix(const char * cstr, const char * prefix);
void *  lib_mem_dup(const void * mem, int size);

Str     Str_ctor_len(const char * cstr, int len);
Str     Str_ctor(const char * cstr);
bool    Str_empty(Str str);
void    Str_shift(Str * str, int len);
void    Str_shrink(Str * str, int len);
void    Str_trim(Str * str, int len);
Str     Str_slice(Str str, int idx, int len);
Str     Str_slice_end(Str str, int idx);
int     Str_skip_ws(Str * str);
int     Str_next_ws(Str str);
Str     Str_chop(Str * str, int len);
Str     Str_in_brackets(Str * str, char lb, char rb);
Str     Str_word(Str * str);
int     Str_prefix(Str str, const char * cstr);
bool    Str_eq(Str str, const char * cstr);


#endif