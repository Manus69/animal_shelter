#include "IPet.h"
#include "ISumpter.h"
#include "Err.h"
#include "Animal.h"

#define CO_BRACKET '['
#define CC_BRACKET ']'

static int _parse_cmds(const char * cstr, Cmd * cmd)
{
    char *  ptr;
    CMD     current;
    int     len;

    ptr = (char *) cstr;
    cstr ++;

    while (true)
    {
        cstr += lib_count_ws(cstr);

        if (! (len = CMD_parse(cstr, & current)))
        {
            if (* cstr == CC_BRACKET) break ;

            return 0;
        }

        cstr += len;
        Cmd_add(cmd, current);
    }

    return cstr - ptr;
}

static int _parse_base(const char * cstr, Animal * animal)
{
    char *  ptr;
    int     len;

    ptr = (char *) cstr;
    if (! (len = SPECIES_parse(cstr, & animal->species))) return 0;
    cstr += len;

    cstr += lib_count_ws(cstr);

    if (! (len = lib_word_len(cstr))) return 0;
    Animal_set_name_len(animal, cstr, len);
    cstr += len;

    if (! (len = lib_parse_int(cstr, & animal->age))) return 0;
    cstr += len;

    if (* cstr && ! (len = lib_count_ws(cstr))) return 0;
    cstr += len;

    if (* cstr == CO_BRACKET)
    {
        if (! (len = _parse_cmds(cstr, & animal->cmd))) return 0;
        cstr += len;
    }

    return cstr - ptr;
}

ERR Animal_from_cstr(const char * cstr, Animal ** animal)
{
    int     len;
    Animal  aml = {};

    if (! (len = _parse_base(cstr, & aml))) return ERR_PARSE;

    return (* animal = lib_mem_dup(& aml, sizeof(Animal))) ? ERR_NONE : ERR_MEM;
}