#include "Animal.h"
#include "IAnimal.h"
#include "../master.h"

#include <string.h>
#include <stdio.h>

Animal Animal_ctor_nl(SPECIES species, const char * name, int nlen, int age, Cmd cmds)
{
    Animal aml;

    aml = (Animal)
    {
        .species = species,
        .age = age,
        .cmd = cmds,
    };

    Animal_set_name_len(& aml, name, nlen);

    return aml;
}

Animal Animal_ctor(SPECIES species, const char * name, int age, Cmd cmds)
{
    return Animal_ctor_nl(species, name, strlen(name), age, cmds);
}

void Animal_del(Animal * animal)
{
    free(animal);
}

char * Animal_name(const Animal * animal)
{
    return (char *) animal->name;
}

void Animal_set_name_len(Animal * animal, const char * name, int len)
{
    len = $min(len, ANIMAL_NBSIZE - 1);
    strncpy(animal->name, name, len);
}

void Animal_set_name(Animal * animal, const char * name)
{
    Animal_set_name_len(animal, name, strlen(name));
}

int Animal_age(const Animal * animal)
{
    return animal->age;
}

Cmd Animal_Cmd(const Animal * animal)
{
    return animal->cmd;
}

int Animal_cstr(const Animal * animal, char * buff)
{
    int len;

    len = 0;
    len += sprintf(buff, "species : %s ", SPECIES_name(animal->species));
    len += sprintf(buff + len, "name : %s ", animal->name);
    len += sprintf(buff + len, "age : %d ", animal->age);
    len += sprintf(buff + len, "commands : ");
    len += Cmd_cstr(animal->cmd, buff + len);

    return len;
}