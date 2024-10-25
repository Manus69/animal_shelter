#ifndef PROGRAM_H
#define PROGRAM_H

#include "../db/IDB.h"

#define PROG_BSIZE      (1 << 10)
#define PROG_CMD_QUIT   "quit"
#define PROG_CMD_PRINT  "print"
#define PROG_CMD_ADD    "add"
#define PROG_CMD_GET    "get"
#define PROG_CMD_REM    "remove"
#define PROG_CMD_TEACH  "teach"
#define PROG_CMD_DONE   "done"
#define PROG_CMD_INFO   "info"
#define PROG_CMD_HELP   "help"

typedef struct
{
    char    buff[PROG_BSIZE];
    DB *    db;
    ERR     err;
    bool    runs;
}   Program;


ERR     Program_init(Program * prog);
void    Program_del(Program * prog);
bool    Program_run(Program * prog);
ERR     Program_status(const Program * prog);
ERR     Program_process_input(Program * prog);
void    Program_help_msg(const Program * prog);
void    Program_help_inter_msg(const Program * prog);

#endif