#ifndef PROGRAM_H
#define PROGRAM_H

#include "db/IDB.h"

#define PROG_BSIZE (1 << 10)
typedef struct
{
    char    buff[PROG_BSIZE];
    DB *    db;
    ERR     err;
    bool    runs;
}   Program;


ERR Program_init(Program * prog);
void Program_del(Program * prog);
bool Program_run(Program * prog);
ERR Program_status(const Program * prog);

#endif