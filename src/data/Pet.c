#include "IPet.h"
#include "Pet.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

bool SPECIES_is_Pet(SPECIES species)
{
    return species >= SPECIES_DOG && species < SPECIES_HORSE;
}

Pet Pet_ctor(SPECIES species, const char * name, int age, Cmd cmds, const char * owner)
{
    Pet pet;

    pet = (Pet)
    {
        .animal = Animal_ctor(species, name, age, cmds),
    };

    strncpy(pet.owner, owner, PET_NOBSIZE - 1);

    return pet;
}

Pet * Pet_new(SPECIES species, const char * name, int age, Cmd cmds, const char * owner)
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

void Pet_set_owner_len(Pet * pet, const char * owner, int len)
{
    len = $min(len, PET_NOBSIZE - 1);
    strncpy(pet->owner, owner, len);
}

void Pet_set_owner(Pet * pet, const char * owner)
{
    Pet_set_owner_len(pet, owner, strlen(owner));
}

int Pet_cstr(const Pet * pet, char * buff)
{
    int len;

    len = Animal_cstr((Animal *) pet, buff);
    len += sprintf(buff + len, " owner : %s ", pet->owner);

    return len;
}