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

static void _print_break(void)
{
    printf("-----\n");
}

static ERR _print_species(Program * prog, SPECIES sp)
{
    _print_break();
    prog->err = DB_print_species(prog->db, sp);
    _print_break();

    return prog->err;
}

static ERR _print_all(Program * prog)
{
    _print_break();
    prog->err = DB_print_all(prog->db);
    _print_break();

    return prog->err;
}

static ERR _print(Program * prog, Str str)
{
    Str     word;
    SPECIES sp;

    word = Str_word(& str);

    if      (word.len == 0)                 return _print_all(prog);
    else if (SPECIES_parse_Str(word, & sp)) return _print_species(prog, sp);
    else    prog->err = ERR_PARSE;

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
    else return (void) printf("unknown command\n");
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

static ERR _remove_by_id(Program * prog, int id)
{
    return (prog->err = DB_del_id(prog->db, id));
}

static ERR _remove_by_species(Program * prog, SPECIES sp)
{
    return (prog->err = DB_del_species(prog->db, sp));
}

static ERR _remove_interactive(Program * prog, int id, const Animal * aml)
{
    printf("%s is kicked out\n", Animal_name(aml));

    return _remove_by_id(prog, id);
}

static ERR _interact(Program * prog, Animal * aml, int id)
{
    Str str;
    Str word;

    if (! aml) return ({printf("No animal\n"); ERR_NONE;});

    printf("'%s' the %s is here\n", Animal_name(aml), SPECIES_name(Animal_species(aml)));
    
    while (true)
    {
        if ((str = _get_input(prog)).len < 0)   break;
        
        word = Str_word(& str);

        if      (Str_eq(word, PROG_CMD_DONE))   break;
        else if (Str_eq(word, PROG_CMD_HELP))   Program_help_inter_msg(prog);
        else if (Str_eq(word, PROG_CMD_INFO))   Animal_dbg(aml);
        else if (Str_eq(word, PROG_CMD_TEACH))  _teach(prog, str, id, aml);
        else if (Str_eq(word, CMD_STR_SPEAK))   Animal_speak(aml);
        else if (Str_eq(word, CMD_STR_RUN))     Animal_run(aml);
        else if (Str_eq(word, CMD_STR_JUMP))    Animal_jump(aml);
        else if (Str_eq(word, CMD_STR_FETCH))   _fetch(prog, str, aml);
        else if (Str_eq(word, CMD_STR_SPIT))    _spit(prog, str, aml);
        else if (Str_eq(word, CMD_STR_CARRY))   _carry(prog, str, aml);
        else if (Str_eq(word, PROG_CMD_REM))    return _remove_interactive(prog, id, aml);
        else    Program_help_inter_msg(prog);
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

static ERR _remove(Program * prog, Str str)
{
    int     id;
    Str     word;
    SPECIES sp;

    word = Str_word(& str);
    
    if (lib_parse_int_len(word.cstr, word.len, & id)) return _remove_by_id(prog, id);
    if (SPECIES_parse_Str(word, & sp)) return _remove_by_species(prog, sp);

    return (prog->err = ERR_PARSE);
}

static ERR _count(Program * prog, Str str)
{
    int x;
    
    (void) str;
    
    if ((prog->err = DB_count(prog->db, & x)) == ERR_NONE)
    {
        printf("Number of animals: %d\n", x);
    }

    return prog->err;
}

ERR Program_process_input(Program * prog)
{
    Str str;
    Str word;

    str = _get_input(prog);
    word = Str_word(& str);

    if      (word.len == 0) {}
    else if (word.len < 0 || Str_eq(word, PROG_CMD_QUIT))
    {
        prog->runs = false;
    }
    else if (Str_eq(word, PROG_CMD_PRINT))  _print(prog, str);
    else if (Str_eq(word, PROG_CMD_ADD))    _add(prog, str);
    else if (Str_eq(word, PROG_CMD_REM))    _remove(prog, str);
    else if (Str_eq(word, PROG_CMD_GET))    _get_by_id(prog, str);
    else if (Str_eq(word, PROG_CMD_COUNT))  _count(prog, str);  
    else if (Str_eq(word, PROG_CMD_HELP))   Program_help_msg(prog);
    else    prog->err = ERR_PARSE;

    return prog->err;
}