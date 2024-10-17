#ifndef ISUMPTER_H
#define ISUMPTER_H

#include "IAnimal.h"

typedef struct Sumpter Sumpter;

bool        SPECIES_is_Sumpter(SPECIES species);
Sumpter *   Sumpter_new(SPECIES species, const char * name, int age, Cmd cmds, int capacity);
void        Sumpter_del(Sumpter * sr);
int         Sumpter_capacity(const Sumpter * sr);


#endif