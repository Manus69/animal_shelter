#include "Pet.h"
#include "Sumpter.h"
#include <stdio.h>

int Animal_cstr(const Animal * aml, char * buff)
{
    if (Animal_is_Pet(aml))     return Pet_cstr((const Pet *) aml, buff);
    if (Animal_is_Sumpter(aml)) return Sumpter_cstr((const Sumpter *) aml, buff);

    assert(0);
}

void Animal_dbg(const Animal * aml)
{
    char buff[1 << 10] = {};

    Animal_cstr(aml, buff);
    printf("%s\n", buff);
}