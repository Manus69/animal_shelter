#ifndef IANIMAL_H
#define IANIMAL_H

#include "../master.h"
#include "SPECIES.h"


typedef struct Animal Animal;

void    Animal_del(Animal * animal);
int     Animal_age(const Animal * animal);
SPECIES Animal_species(const Animal * aml);
char *  Animal_name(const Animal * animal);
void    Animal_set_name_len(Animal * animal, const char * name, int len);
void    Animal_set_name(Animal * animal, const char * name);
Cmd     Animal_Cmd(const Animal * animal);
int     Animal_cstr(const Animal * aml, char * buff);
void    Animal_dbg(const Animal * aml);


#endif