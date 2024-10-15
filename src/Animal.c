#include "AnimalInterface.h"
#include "Animal.h"

#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

static Animal * _Animal_new(int id, ANIMAL_TYPE type, cmd_code cmd, const char * name, int nlen)
{
    Animal * animal;

    if ((animal = calloc(1, sizeof(* animal))))
    {
        * animal = (Animal)
        {
            .id = id,
            .type = type,
            .commands = cmd,
        };

        memcpy(animal->name, name, nlen);

        return animal;
    }

    return NULL;
}

void Animal_del(Animal * animal)
{
    free(animal);
}

void Animal_add_cmd(Animal * animal, ANIMAL_CMD cmd)
{
    animal->commands |= (1 << cmd);
}

void Animal_remove_cmd(Animal * animal, ANIMAL_CMD cmd)
{
    animal->commands &= ~(1 << cmd);
}

bool Animal_has_cmd(const Animal * animal, ANIMAL_CMD cmd)
{
    return animal->commands & (1 << cmd);
}

idx Animal_get_id(const Animal * animal)
{
    return animal->id;
}