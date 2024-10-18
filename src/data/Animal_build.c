#include "Err.h"
#include "Animal.h"
#include "Sumpter.h"
#include "Pet.h"

#define CO_BRACKET '['
#define CC_BRACKET ']'

static bool _parse_species(Str * str, Animal * aml)
{
    Str word;

    word = Str_word(str);
    
    return SPECIES_parse_Str(word, & aml->species);
}

static bool _parse_name(Str * str, Animal * aml)
{
    Str word;

    word = Str_word(str);
    if (! word.len) return false;

    Animal_set_name_len(aml, word.cstr, word.len);

    return true;
}

static bool _parse_owner(Str * str, Pet * pet)
{
    Str word;

    if (! (word = Str_word(str)).len) return false;

    Pet_set_owner_len(pet, word.cstr, word.len);

    return true;
}

static bool _parse_integer(Str * str, int * x)
{
    Str word;

    word = Str_word(str);

    return lib_parse_int_len(word.cstr, word.len, x);
}

static bool _parse_age(Str * str, Animal * aml)
{
    return _parse_integer(str, & aml->age);
}

static bool _parse_capacity(Str * str, Sumpter * sr)
{
    return _parse_integer(str, & sr->capacity);
}

static bool _parse_cmds(Str * str, Animal * aml)
{
    Str bracketed;
    Str word;
    CMD cmd;

    Str_skip_ws(str);
    if (* str->cstr != CO_BRACKET) return true;

    bracketed = Str_in_brackets(str, CO_BRACKET, CC_BRACKET);
    if (Str_empty(bracketed)) return false;

    Str_trim(& bracketed, 1);

    while (! Str_empty(bracketed))
    {
        word = Str_word(& bracketed);

        if (Str_empty(word)) break;
        if (! CMD_parse_Str(word, & cmd)) return false;

        Cmd_add(& aml->cmd, cmd);
    }

    return true;
}

static bool _parse_base(Str * str, Animal * aml)
{
    if (! _parse_species(str, aml)) return false;
    if (! _parse_name(str, aml))    return false;
    if (! _parse_age(str, aml))     return false;
    if (! _parse_cmds(str, aml))    return false;

    return true;
}

static ERR _build_Pet(Str * str, const Animal * current, Animal ** animal)
{
    Pet pet = {};

    pet.animal = * current;
    _parse_owner(str, & pet);

    Str_skip_ws(str);
    if (! Str_empty(* str)) return ERR_PARSE;

    return (* animal = lib_mem_dup(& pet, sizeof(pet))) ? ERR_NONE : ERR_MEM;
}

static ERR _build_Sumpter(Str * str, const Animal * current, Animal ** animal)
{
    Sumpter sr = {};

    sr.animal = * current;
    if (! _parse_capacity(str, & sr)) return ERR_PARSE;

    Str_skip_ws(str);
    if (! Str_empty(* str)) return ERR_PARSE;

    return (* animal = lib_mem_dup(& sr, sizeof(sr))) ? ERR_NONE : ERR_MEM;
}

ERR Animal_build_Str(Str str, Animal ** animal)
{
    Animal  aml = {};

    if (! _parse_base(& str, & aml))        return ERR_PARSE;
    if (SPECIES_is_Pet(aml.species))        return _build_Pet(& str, & aml, animal);
    if (SPECIES_is_Sumpter(aml.species))    return _build_Sumpter(& str, & aml, animal);

    return ERR_LOGIC;
}

ERR Animal_build(const char * cstr, Animal ** animal)
{
    Str str;

    str = Str_ctor(cstr);

    return Animal_build_Str(str, animal);
}