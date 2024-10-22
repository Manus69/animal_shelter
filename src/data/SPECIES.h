#ifndef SPECIES_H
#define SPECIES_H

#include "Cmd.h"

typedef enum
{
    SPECIES_UNDEF,
    SPECIES_DOG,
    SPECIES_CAT,
    SPECIES_HAMSTER,
    SPECIES_HORSE,
    SPECIES_CAMEL,
    SPECIES_ASS,
    SPECIES_COUNT,
}   SPECIES;

char *  SPECIES_name(SPECIES species);
char *  SPECIES_sound(SPECIES species);
Cmd     SPECIES_commands(SPECIES species);
bool    SPECIES_can_be_taught(SPECIES species, CMD cmd);
int     SPECIES_parse(const char * cstr, SPECIES * species);
bool    SPECIES_parse_Str(Str str, SPECIES * species);

#endif