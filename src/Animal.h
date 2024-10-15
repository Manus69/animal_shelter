#ifndef ANIMAL_H
#define ANIMAL_H

#include "AnimalInterface.h"

#define NLEN (1 << 4)

typedef struct
{
    idx         id;
    ANIMAL_TYPE type;
    cmd_code    commands;
    char        name[NLEN];
}   Animal;

#endif