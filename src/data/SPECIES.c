#include "SPECIES.h"

#include <string.h>

static const char * _names[SPECIES_COUNT] = 
{
    [SPECIES_ASS] = "ass",
    [SPECIES_CAMEL] = "camel",
    [SPECIES_CAT] = "cat",
    [SPECIES_DOG] = "dog",
    [SPECIES_HAMSTER] = "hamster",
    [SPECIES_HORSE] = "horse",
};

static const char * _sounds[SPECIES_COUNT] = 
{
    [SPECIES_ASS] = "bray",
    [SPECIES_CAT] = "meow",
    [SPECIES_DOG] = "bark",
    [SPECIES_HORSE] = "neigh",
};

static const Cmd _cmds[SPECIES_COUNT] = 
{
    [SPECIES_ASS] = (1 << CMD_CARRY) | (1 << CMD_SPEAK),
    [SPECIES_CAMEL] = (1 << CMD_CARRY) | (1 << CMD_SPIT),
    [SPECIES_CAT] = (1 << CMD_SPEAK) | (1 << CMD_CUDDLE) | (1 << CMD_RUN) | (1 << CMD_JUMP),
    [SPECIES_DOG] = (1 << CMD_SPEAK) | (1 << CMD_CUDDLE) | (1 << CMD_FETCH) | (1 << CMD_RUN),
    [SPECIES_HAMSTER] = 0,
    [SPECIES_HORSE] = (1 << CMD_RUN) | (1 << CMD_CARRY) | (1 << CMD_SPEAK) | (1 << CMD_JUMP),
};

char * SPECIES_name(SPECIES species)
{
    return (char *) _names[species];
}

char * SPECIES_sound(SPECIES species)
{
    return (char *) _sounds[species];
}

Cmd SPECIES_commands(SPECIES species)
{
    return _cmds[species];
}

bool SPECIES_can_be_taught(SPECIES species, CMD cmd)
{
    return SPECIES_commands(species) & cmd;
}

int SPECIES_parse(const char * cstr, SPECIES * species)
{
    int len;

    for (int k = 1; k < SPECIES_COUNT; k ++)
    {
        if ((len = lib_match_prefix(cstr, SPECIES_name(k))))
        {
            * species = k;

            return len;
        }
    }

    return 0;
}

bool SPECIES_parse_Str(Str str, SPECIES * species)
{
    for (int k = 1; k < SPECIES_COUNT; k ++)
    {
        if (Str_eq(str, SPECIES_name(k)))
        {
            * species = k;

            return true;
        }
    }

    return false;
}