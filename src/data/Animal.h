#ifndef ANIMAL_H
#define ANIMAL_H

#include "IAnimal.h"

#define ANIMAL_NBSIZE (1 << 4)

struct Animal
{
    SPECIES species;
    int     age;
    int     cmd;
    char    name[ANIMAL_NBSIZE];
};

Animal Animal_ctor(SPECIES species, const char * name, int age, int cmds);

#endif