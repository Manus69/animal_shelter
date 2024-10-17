#include "SPECIES.h"

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
    [SPECIES_CAT] = (1 << CMD_SPEAK) | (1 << CMD_CUDDLE) | (1 << CMD_RUN),
    [SPECIES_DOG] = (1 << CMD_SPEAK) | (1 << CMD_CUDDLE) | (1 << CMD_FETCH) | (1 << CMD_RUN),
    [SPECIES_HAMSTER] = 0,
    [SPECIES_HORSE] = (1 << CMD_RUN) | (1 << CMD_CARRY) | (1 << CMD_SPEAK),
};

char * SPECIES_name(SPECIES species)
{
    return _names[species];
}

char * SPECIES_sound(SPECIES species)
{
    return _sounds[species];
}

Cmd SPECIES_commands(SPECIES species)
{
    return _cmds[species];
}
