#include "Program.h"

#include <stdio.h>


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
    printf("-----\n");
    prog->err = DB_print(prog->db);
    printf("-----\n");

    return prog->err;
}

static bool _teach(Program * prog, Animal * aml, Str str)
{
    CMD cmd;
    Str word;

    (void) prog;

    word = Str_word(& str);
    if (CMD_parse_Str(word, & cmd))
    {
        if (! Animal_learn(aml, cmd))
        {
            printf("%s can't %s\n", Animal_name(aml), CMD_name(cmd));
            return false;
        }
    }
    else
    {
        printf("unknown command\n");
        return false;
    }

    return true;
}

static void _help(void)
{
    printf("Enter the command you wish the animal to perform or 'done' to return.\n");
}

static ERR _interact(Program * prog, Animal * aml, int id)
{
    Str str;
    Str word;

    printf("%s is here\n", Animal_name(aml));
    while (true)
    {
        str = _get_input(prog);
        word = Str_word(& str);

        if      (Str_eq(word, "done")) break;
        else if (Str_eq(word, "info")) Animal_dbg(aml);
        else if (Str_eq(word, "speak")) Animal_speak(aml);
        else if (Str_eq(word, "run")) Animal_run(aml);
        else if (Str_eq(word, "fetch"))
        {
            word = Str_word(& str);
            if (word.len) Animal_fetch(aml, word);
            else printf("fetch what ?\n");
        }
        else if (Str_eq(word, "teach"))
        {
            if (_teach(prog, aml, str))
            {
                prog->err = DB_update(prog->db, id, aml);
            }
        }
        else _help();
    }

    return ERR_NONE;
}

static ERR _get_by_id(Program * prog, Str str)
{
    Animal *    aml;
    int         id;
    Str         word;

    word = Str_word(& str);
    if (! lib_parse_int_len(word.cstr, word.len, & id))
    {
        return (prog->err = ERR_PARSE);
    }

    if (! (prog->err = DB_get_by_id(prog->db, id, & aml)))
    {
        prog->err = _interact(prog, aml, id);
        Animal_del(aml);
    }

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

ERR Program_process_input(Program * prog)
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
    else if (Str_eq(word, "get")) _get_by_id(prog, str);
    else    prog->err = ERR_PARSE;

    return prog->err;
}