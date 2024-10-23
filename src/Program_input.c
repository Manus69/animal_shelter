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

//to help msg functions
static void _print_help(void)
{
    printf("Enter the command you wish the animal to perform or 'done' to return.\n");
}

static void _print_break(void)
{
    printf("-----\n");
}

static ERR _print_species(Program * prog, SPECIES sp)
{

}

static ERR _print(Program * prog, Str str)
{
    Str     word;
    SPECIES sp;

    word = Str_word(& str);

    if (SPECIES_parse_Str(word, & sp)) return _print_species(prog, sp);
    if (word.len == 0)
    {
        _print_break();
        prog->err = DB_print_all(prog->db);
        _print_break();
    }

    return prog->err;
}



static void _teach(Program * prog, Str str, int id, Animal * aml)
{
    CMD cmd;
    Str word;

    word = Str_word(& str);
    if (CMD_parse_Str(word, & cmd))
    {
        if (! Animal_learn(aml, cmd))
        {
            return (void) printf("%s can't %s\n", Animal_name(aml), CMD_name(cmd));
        }
        
        prog->err = DB_update(prog->db, id, aml);
    }
    else
    {
        return (void) printf("unknown command\n");
    }
}

static void _fetch(Program * prog, Str str, const Animal * aml)
{
    Str word;

    (void) prog;
    word = Str_word(& str);

    if  (word.len) Animal_fetch(aml, word);
    else printf("fetch what ?\n");
}

static void _spit(Program * prog, Str str, const Animal * aml)
{
    Str word;

    (void) prog;
    word = Str_word(& str);

    Animal_spit(aml, word);
}

static void _carry(Program * prog, Str str, const Animal * aml)
{
    Str word;
    int weight;

    (void) prog;
    
    word = Str_word(& str);
    if (! (lib_parse_int_len(word.cstr, word.len, & weight)))
    {
        return (void) printf("How much to carry ?\n");
    }

    Animal_carry(aml, weight);
}

static ERR _interact(Program * prog, Animal * aml, int id)
{
    Str str;
    Str word;

    if (! aml)
    {
        printf("No animal\n");

        return ERR_NONE;
    }

    printf("'%s' is here\n", Animal_name(aml));
    while (true)
    {
        str = _get_input(prog);
        word = Str_word(& str);

        if      (Str_eq(word, "done"))  break;
        else if (Str_eq(word, "info"))  Animal_dbg(aml);
        else if (Str_eq(word, "speak")) Animal_speak(aml);
        else if (Str_eq(word, "run"))   Animal_run(aml);
        else if (Str_eq(word, "jump"))  Animal_jump(aml);
        else if (Str_eq(word, "fetch")) _fetch(prog, str, aml);
        else if (Str_eq(word, "spit"))  _spit(prog, str, aml);
        else if (Str_eq(word, "carry")) _carry(prog, str, aml);
        else if (Str_eq(word, "teach")) _teach(prog, str, id, aml);
        else _print_help();
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
    int id;
    Str word;

    word = Str_word(& str);
    if (! lib_parse_int_len(word.cstr, word.len, & id)) return ERR_PARSE;

    return (prog->err = DB_del_id(prog->db, id));
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
    else if (Str_eq(word, "print")) _print(prog, str);
    else if (Str_eq(word, "add")) _add(prog, str);
    else if (Str_eq(word, "remove")) _remove_by_id(prog, str);
    else if (Str_eq(word, "get")) _get_by_id(prog, str);
    else    prog->err = ERR_PARSE;

    return prog->err;
}