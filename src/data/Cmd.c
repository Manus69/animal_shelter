#include "Cmd.h"

#include <stdio.h>

static const char * _cmd_cstr[CMD_COUNT] = 
{
    [CMD_CARRY] =   CMD_STR_CARRY,
    [CMD_CUDDLE] =  CMD_STR_CUDDLE,
    [CMD_FETCH] =   CMD_STR_FETCH,
    [CMD_JUMP] =    CMD_STR_JUMP,
    [CMD_RUN] =     CMD_STR_RUN,
    [CMD_SPEAK] =   CMD_STR_SPEAK,
    [CMD_SPIT] =    CMD_STR_SPIT,
};

Cmd Cmd_add(Cmd * cmds, CMD cmd)
{
    return (* cmds |= (1 << cmd));
}

bool Cmd_has(Cmd cmds, CMD cmd)
{
    return (cmds) & (1 << cmd);
}

char * CMD_name(CMD cmd)
{
    return (char *) _cmd_cstr[cmd];
}

static int _CMD_cstr(CMD cmd, char * buff)
{
    return sprintf(buff, "%s ", CMD_name(cmd));
}

int Cmd_cstr(Cmd cmd, char * buff)
{
    int len;

    len = 0;
    len += sprintf(buff, "[");

    for (int k = 0; k < CMD_COUNT; k ++)
    {
        if (Cmd_has(cmd, k))
        {
            len += _CMD_cstr(k, buff + len);
        }
    }

    len += sprintf(buff + len, "] ");

    return len;
}

int CMD_parse(const char * cstr, CMD * cmd)
{
    int len;

    for (int k = 1; k < CMD_COUNT; k ++)
    {
        if ((len = lib_match_prefix(cstr, CMD_name(k))))
        {
            * cmd = k;

            return len;
        }
    }

    return 0;
}

bool CMD_parse_Str(Str str, CMD * cmd)
{
    for (int k = 1; k < CMD_COUNT; k ++)
    {
        if (Str_eq(str, CMD_name(k)))
        {
            * cmd = k;

            return true;
        }
    }

    return false;
}