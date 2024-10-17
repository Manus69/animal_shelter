#include "master.h"

#include <string.h>
#include <ctype.h>
#include <limits.h>

int lib_count_ws(const char * cstr)
{
    int k;

    for (k = 0; isspace(cstr[k]); k ++) {}

    return k;
}

int lib_next_ws(const char * cstr)
{
    for (int k = 0; cstr[k]; k ++)
    {
        if (isspace(cstr[k])) return k;
    }

    return NO_IDX;
}

int lib_word_len(const char * cstr)
{
    int len;

    for (len = 0; cstr[len]; len ++)
    {
        if (isspace(cstr[len])) break;
    }

    return len;
}

int lib_match_prefix(const char * cstr, const char * prefix)
{
    int k;

    for (k = 0; cstr[k] && prefix[k]; k ++)
    {
        if (cstr[k] != prefix[k]) return 0;
    }

    return k;
}

int lib_parse_int(const char * cstr, int * x)
{
    char *  end;
    long    val;

    val = strtol(cstr, & end, 10);

    if (end == cstr)                    return 0;
    if (val > INT_MAX || val < INT_MIN) return 0;

    * x = val;

    return end - cstr;
}

void * lib_mem_dup(const void * mem, int size)
{
    void * ptr;

    if ((ptr = calloc(1, size)))
    {
        return memcpy(ptr, mem, size);
    }

    return NULL;
}