#include "Program.h"
#include "master.h"

#include <stdio.h>


ERR Program_init(Program * prog)
{
    * prog = (Program) {};

    if (DB_init(& prog->db)) return ERR_DB;
    prog->runs = true;

    return ERR_NONE;
}

void Program_del(Program * prog)
{
    DB_deinit(prog->db);
}

ERR Program_status(const Program * prog)
{
    return prog->err;
}


bool Program_run(Program * prog)
{
    prog->err = 0;

    Program_process_input(prog);

    if (prog->err) printf("%s\n", Err_cstr(prog->err));   

    return prog->runs;
}