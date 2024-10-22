#ifndef ISUMPTER_H
#define ISUMPTER_H

#include "IAnimal.h"

typedef struct Sumpter Sumpter;

bool        SPECIES_is_Sumpter(SPECIES species);
bool        Animal_is_Sumpter(const Animal * aml);
Sumpter *   Sumpter_new(SPECIES species, const char * name, int age, Cmd cmds, int capacity);
void        Sumpter_del(Sumpter * sr);
void        Sumpter_carry(const Sumpter * sr, int weight);
int         Sumpter_capacity(const Sumpter * sr);
int         Sumpter_cstr(const Sumpter * sr, char * buff);


#endif