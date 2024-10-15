#ifndef INPUT_H
#define INPUT_H

//ansh get | add | remove | purge
// add-cmd remove-cmd info perform cmd

typedef enum
{
    CMD_GET,
    CMD_REM,
    CMD_PURGE,
    CMD_HELP,
    CMD_COUNT,
}   CMD;

typedef struct
{
    char *  cstr;
    char *  arg;
    CMD     cmd;
}   Input;

#endif