#include "IPet.h"
#include "Pet.h"

#include <stdlib.h>
#include <string.h>

Pet Pet_ctor(SPECIES species, const char * name, int age, int cmds, const char * owner)
{
    Pet pet;

    pet = (Pet)
    {
        .animal = Animal_ctor(species, name, age, cmds),
    };

    strncpy(pet.owner, owner, PET_NOBSIZE - 1);

    return pet;
}

Pet * Pet_new(SPECIES species, const char * name, int age, int cmds, const char * owner)
{
    Pet * pet;

    if ((pet = calloc(1, sizeof(* pet))))
    {
        * pet = Pet_ctor(species, name, age, cmds, owner);
        
        return pet;
    }

    return NULL;
}

void Pet_del(Pet * pet)
{
    free(pet);
}

char * Pet_owner(const Pet * pet)
{
    return (char *) pet->owner;
}