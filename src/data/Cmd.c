#include "Cmd.h"

#include <stdio.h>

static const char * _cmd_cstr[CMD_COUNT] = 
{
    [CMD_CARRY] = "carry",
    [CMD_CUDDLE] = "cuddle",
    [CMD_FETCH] = "fetch",
    [CMD_JUMP] = "jump",
    [CMD_RUN] = "run",
    [CMD_SPEAK] = "speak",
    [CMD_SPIT] = "spit",
};

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
        if (Cmd_has(& cmd, k))
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