#include "master.h"

#include <string.h>
#include <ctype.h>
#include <limits.h>
#include <stdio.h>

int lib_get_line(char * buff, int bsize)
{
    int x;
    int len;

    memset(buff, 0, bsize);
    len = 0;

    while (true)
    {
        x = getchar();
        if (x == '\n' || x == EOF) break;

        buff[len ++] = x;

        if (len == bsize - 1) break;
    }

    return len;
}

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

#define BSIZE (1 << 4)
int lib_parse_int_len(const char * cstr, int len, int * x)
{
    char buff[BSIZE] = {};

    if (len >= BSIZE) return 0;

    memcpy(buff, cstr, len);

    return lib_parse_int(buff, x);
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

Str Str_ctor_len(const char * cstr, int len)
{
    return (Str) {(char *) cstr, len};
}

Str Str_ctor(const char * cstr)
{
    return Str_ctor_len(cstr, strlen(cstr));
}

bool Str_empty(Str str)
{
    return str.len == 0;
}

void Str_shift(Str * str, int len)
{
    str->cstr += len;
    str->len -= len;
}

void Str_shrink(Str * str, int len)
{
    str->len -= len;
}

void Str_trim(Str * str, int len)
{
    Str_shift(str, len);
    Str_shrink(str, len);
}

Str Str_slice(Str str, int idx, int len)
{
    return Str_ctor_len(str.cstr + idx, len);
}

Str Str_slice_end(Str str, int idx)
{
    return Str_ctor(str.cstr + idx);
}

int Str_skip_ws(Str * str)
{
    int len;

    len = lib_count_ws(str->cstr);
    Str_shift(str, len);

    return len;
}

Str Str_chop(Str * str, int len)
{
    Str chop;

    chop = Str_ctor_len(str->cstr, len);
    Str_shift(str, len);

    return chop;
}

Str Str_in_brackets(Str * str, char lb, char rb)
{
    int count;
    int len;

    if (* str->cstr != lb) return (Str) {};

    count = 1;
    len = 0;

    for (int k = 1; k < str->len; k ++)
    {
        if (str->cstr[k] == lb) count ++;
        else if (str->cstr[k] == rb) count --;

        if (count == 0)
        {
            len = k + 1;
            break ;
        }
    }

    return Str_chop(str, len);
}

int Str_next_ws(Str str)
{
    for (int k = 0; k < str.len; k ++)
    {
        if (isspace(str.cstr[k])) return k;
    }

    return NO_IDX;
}

Str Str_word(Str * str)
{
    int idx;

    Str_skip_ws(str);
    idx = Str_next_ws(* str);

    return idx == NO_IDX ? Str_chop(str, str->len) : Str_chop(str, idx);
}

int Str_prefix(Str str, const char * cstr)
{
    int k;

    for (k = 0; k < str.len; k ++)
    {
        if (! * cstr) return k;
        if (* cstr != str.cstr[k]) return 0;

        cstr ++;
    }

    return * cstr ? 0 : k;
}

bool Str_eq(Str str, const char * cstr)
{
    return Str_prefix(str, cstr) == str.len;
}