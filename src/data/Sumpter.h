#ifndef SUMPTER_H
#define SUMPTER_H

#include "ISumpter.h"
#include "Animal.h"

struct Sumpter
{
    Animal  animal;
    int     capacity;
};

Sumpter Sumpter_ctor(SPECIES species, const char * name, int age, Cmd cmds, int capacity);

#endif