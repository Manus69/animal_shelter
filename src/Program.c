#include "Program.h"
#include "master.h"

#include <stdio.h>

ERR Animal_build_Str(Str str, Animal ** animal);

ERR Program_init(Program * prog)
{
    * prog = (Program) {};

    if (DB_init(& prog->db)) return ERR_DB;
    prog->runs = true;

    return ERR_NONE;
}

void Program_del(Program * prog)
{
    DB_deinit(prog->db);
}

ERR Program_status(const Program * prog)
{
    return prog->err;
}

static Str _get_input(Program * prog)
{
    int len;

    len = lib_get_line(prog->buff, PROG_BSIZE);

    return Str_ctor_len(prog->buff, len);
}

static ERR _add(Program * prog, Str str)
{
    Animal * aml;
    
    if ((prog->err = Animal_build_Str(str, & aml))) return prog->err;

    prog->err = DB_insert(prog->db, aml);
    Animal_del(aml);

    return prog->err;
}

static ERR _print(Program * prog)
{
    return (prog->err = DB_print(prog->db));
}

static ERR _edit(Program * prog, Animal * aml)
{
    Str str;

    printf("%s is here\n", Animal_name(aml));
    while (true)
    {
        str = _get_input(prog);
        if (Str_eq(str, "done")) return ERR_NONE;
    }
}

static ERR _get_by_id(Program * prog, Str str)
{
    Animal *    aml;
    int         id;

    if (! lib_parse_int_len(str.cstr, str.len, & id))
    {
        return (prog->err = ERR_PARSE);
    }

    if (! (prog->err = DB_get_by_id(prog->db, id, & aml)))
    {
        prog->err = _edit(prog, aml);
    }

    Animal_del(aml);

    return prog->err;
}

static ERR _get_by_name(Program * prog, Str str)
{
    Animal *    aml;
    Str         word;
    
    word = Str_word(& str);
    prog->err = DB_get_by_name(prog->db, word.cstr, word.len, & aml);

    return prog->err;
}

static ERR _remove_by_id(Program * prog, Str str)
{
    Animal *    aml;
    int         id;
    Str         word;

    word = Str_word(& str);
    if (! lib_parse_int_len(word.cstr, word.len, & id)) return ERR_PARSE;

    if (! (prog->err = DB_remove_by_id(prog->db, id, & aml)))
    {
        printf("%s is kicked out\n", Animal_name(aml));
        Animal_del(aml);
    }

    return prog->err;
}

bool Program_run(Program * prog)
{
    Str str;
    Str word;

    str = _get_input(prog);
    word = Str_word(& str);

    if      (! word.len) {}
    else if (Str_eq(word, "quit"))
    {
        prog->runs = false;
    }
    else if (Str_eq(word, "print")) _print(prog);
    else if (Str_eq(word, "add")) _add(prog, str);
    else if (Str_eq(word, "remove")) _remove_by_id(prog, str);
    else if (Str_eq(word, "get"))
    {
        word = Str_word(& str);

        if      (Str_eq(word, "id")) _get_by_id(prog, str);
        else if (Str_eq(word, "name")) _get_by_name(prog, str);
        else    prog->err = ERR_PARSE;
    }

    return prog->runs;
}