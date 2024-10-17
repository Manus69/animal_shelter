#ifndef IANIMAL_H
#define IANIMAL_H

#include "../master.h"
#include "SPECIES.h"


typedef struct Animal Animal;

void        Animal_del(Animal * animal);
int         Animal_age(const Animal * animal);
char *      Animal_name(const Animal * animal);


#endif