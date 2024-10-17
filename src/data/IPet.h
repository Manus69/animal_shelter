#ifndef IPET_H
#define IPET_H

#include "IAnimal.h"

typedef struct Pet Pet;

Pet *   Pet_new(SPECIES species, const char * name, int age, int cmds, const char * owner);
void    Pet_del(Pet * pet);
char *  Pet_owner(const Pet * pet);


#endif