#include "ISumpter.h"
#include "Sumpter.h"

#include <stdlib.h>
#include <stdio.h>

bool SPECIES_is_Sumpter(SPECIES species)
{
    return species >= SPECIES_HORSE;
}

Sumpter Sumpter_ctor(SPECIES species, const char * name, int age, Cmd cmds, int capacity)
{
    return (Sumpter)
    {
        .animal = Animal_ctor(species, name, age, cmds),
        .capacity = capacity,
    };
}

Sumpter * Sumpter_new(SPECIES species, const char * name, int age, Cmd cmds, int capacity)
{
    Sumpter * sr;

    if ((sr = calloc(1, sizeof(* sr))))
    {
        * sr = Sumpter_ctor(species, name, age, cmds, capacity);

        return sr;
    }

    return NULL;
}

void Sumpter_del(Sumpter * sr)
{
    free(sr);
}

int Sumpter_capacity(const Sumpter * sr)
{
    return sr->capacity;
}

int Sumpter_cstr(const Sumpter * sr, char * buff)
{
    int len;

    len = Animal_cstr((Animal *) sr, buff);
    len += sprintf(buff + len, "capacity : %d ", sr->capacity);

    return len;
}