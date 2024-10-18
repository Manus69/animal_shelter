#ifndef ANIMAL_H
#define ANIMAL_H

#include "IAnimal.h"

#define ANIMAL_NBSIZE (1 << 4)

struct Animal
{
    SPECIES species;
    int     age;
    Cmd     cmd;
    char    name[ANIMAL_NBSIZE];
};

Animal  Animal_ctor_nl(SPECIES species, const char * name, int nlen, int age, Cmd cmds);
Animal  Animal_ctor(SPECIES species, const char * name, int age, Cmd cmds);
int     Animal_cstr_base(const Animal * animal, char * buff);

#endif