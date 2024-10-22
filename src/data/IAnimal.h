#ifndef IANIMAL_H
#define IANIMAL_H

#include "../master.h"
#include "SPECIES.h"
#include "Err.h"

typedef struct Animal Animal;

void    Animal_del(Animal * animal);
int     Animal_age(const Animal * animal);
SPECIES Animal_species(const Animal * aml);
char *  Animal_name(const Animal * animal);
void    Animal_set_name_len(Animal * animal, const char * name, int len);
void    Animal_set_name(Animal * animal, const char * name);
Cmd     Animal_Cmd(const Animal * animal);
bool    Animal_can_perform(const Animal * aml, CMD cmd);
bool    Animal_learn(Animal * aml, CMD cmd);
void    Animal_speak(const Animal * aml);
void    Animal_cuddle(const Animal * aml, Str str);
void    Animal_fetch(const Animal * aml, Str str);
void    Animal_carry(const Animal * aml, int weight);
void    Animal_run(const Animal * aml);
void    Animal_jump(const Animal * aml);
void    Animal_spit(const Animal * aml, Str str);
int     Animal_cstr(const Animal * aml, char * buff);
void    Animal_dbg(const Animal * aml);
ERR     Animal_build_Str(Str str, Animal ** animal);

#endif