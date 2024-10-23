#include "IAnimal.h"
#include "ISumpter.h"
#include "IPet.h"
#include "Animal.h"

#include <stdio.h>

static void _refuse(const Animal * aml, CMD cmd)
{
    printf("%s can't %s\n", Animal_name(aml), CMD_name(cmd));
}

static void _generic_cmd(const Animal * aml, CMD cmd)
{
    if (Animal_can_perform(aml, cmd))
    {
        printf("%s %ss\n", Animal_name(aml), CMD_name(cmd));
    }
    else
    {
        _refuse(aml, cmd);
    }
}

static void _obj_cmd(const Animal * aml, CMD cmd, const char * preposition, Str str)
{
    if (Animal_can_perform(aml, cmd))
    {
        printf("%s %ss %s %.*s\n", Animal_name(aml), CMD_name(cmd), preposition, str.len, str.cstr);
    }
    else
    {
        _refuse(aml, cmd);
    }
}

bool Animal_learn(Animal * aml, CMD cmd)
{
    if (SPECIES_can_be_taught(aml->species, cmd))
    {
        return (aml->cmd = Cmd_add(& aml->cmd, cmd));
    }

    return false;
}

void Animal_speak(const Animal * aml)
{
    if (Animal_can_perform(aml, CMD_SPEAK))
    {
        printf("%s %ss\n", Animal_name(aml), SPECIES_sound(aml->species));
    }
    else _refuse(aml, CMD_SPEAK);
}

void Animal_cuddle(const Animal * aml, Str str)
{
    _obj_cmd(aml, CMD_CUDDLE, "with", str);
}

void Animal_fetch(const Animal * aml, Str str)
{
    if (Animal_can_perform(aml, CMD_FETCH))
    {
        printf("%s fetches %.*s\n", Animal_name(aml), str.len, str.cstr);
    }
    else _refuse(aml, CMD_FETCH);
}

void Animal_carry(const Animal * aml, int weight)
{
    if (Animal_is_Sumpter(aml)) return Sumpter_carry((Sumpter *) aml, weight);
    else _refuse(aml, CMD_CARRY);
}

void Animal_run(const Animal * aml)
{
    _generic_cmd(aml, CMD_RUN);
}

void Animal_jump(const Animal * aml)
{
    _generic_cmd(aml, CMD_JUMP);
}

void Animal_spit(const Animal * aml, Str str)
{
    _obj_cmd(aml, CMD_SPIT, "at", str);
}