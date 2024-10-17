#ifndef CMD_H
#define CMD_H

#include "../master.h"

typedef unsigned int Cmd;

typedef enum
{
    CMD_NONE,
    CMD_SPEAK,
    CMD_RUN,
    CMD_CARRY,
    CMD_CUDDLE,
    CMD_FETCH,
    CMD_SPIT,
    CMD_COUNT,
}   CMD;

static inline Cmd Cmd_add(Cmd * cmds, CMD cmd)
{
    return (* cmds |= (1 << cmd));
}

static inline bool Cmd_has(const Cmd * cmds, CMD cmd)
{
    return * cmds & (1 << cmd);
}

#endif