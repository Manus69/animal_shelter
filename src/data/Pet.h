#ifndef PET_H
#define PET_H

#include "IPet.h"
#include "Animal.h"

#define PET_NOBSIZE (1 << 4)

struct Pet
{
    Animal  animal;
    char    owner[PET_NOBSIZE];
};

Pet Pet_ctor(SPECIES species, const char * name, int age, Cmd cmds, const char * owner);

#endif