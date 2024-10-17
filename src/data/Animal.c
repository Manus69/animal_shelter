#include "Animal.h"
#include "IAnimal.h"
#include "../master.h"

#include <string.h>

Animal Animal_ctor(SPECIES species, const char * name, int age, int cmds)
{
    Animal aml;

    aml = (Animal)
    {
        .species = species,
        .age = age,
        .cmd = cmds,
    };

    strncpy(aml.name, name, ANIMAL_NBSIZE - 1);

    return aml;
}

void Animal_del(Animal * animal)
{
    free(animal);
}

char * Animal_name(const Animal * animal)
{
    return (char *) animal->name;
}

int Animal_age(const Animal * animal)
{
    return animal->age;
}