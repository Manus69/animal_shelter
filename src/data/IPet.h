#ifndef IPET_H
#define IPET_H

#include "IAnimal.h"

typedef struct Pet Pet;

bool    SPECIES_is_Pet(SPECIES species);
bool    Animal_is_Pet(const Animal * animal);
Pet *   Pet_new(SPECIES species, const char * name, int age, Cmd cmds, const char * owner);
void    Pet_del(Pet * pet);
char *  Pet_owner(const Pet * pet);
bool    Pet_has_owner(const Pet * pet);
void    Pet_set_owner_len(Pet * pet, const char * owner, int len);
void    Pet_set_owner(Pet * pet, const char * owner);
int     Pet_cstr(const Pet * pet, char * buff);

#endif