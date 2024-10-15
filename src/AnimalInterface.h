#ifndef ANIMAL_INTERFACE_H
#define ANIMAL_INTERFACE_H

typedef enum
{
    ANIMAL_TYPE_DOG,
    ANIMAL_TYPE_DONKEY,
    ANIMAL_TYPE_CAMEL,
    ANIMAL_TYPE_MONKEY,
}   ANIMAL_TYPE;

typedef int cmd_code;
typedef int idx;

typedef enum
{
    ANIMAL_CMD_SPEAK,
    ANIMAL_CMD_SPIT,
    ANIMAL_CMD_RUN,
}   ANIMAL_CMD;

#endif