#include "prog/Program.h"

#include <stdio.h>

static ERR _err_and_die(const Program * prog)
{
    ERR err;

    err = Program_status(prog);
    printf("%s\n", Err_cstr(err));

    return err;
}

int main()
{
    Program prog;

    if (Program_init(& prog)) return _err_and_die(& prog);

    Program_help_msg(& prog);
    Program_help_inter_msg(& prog);
    
    while (Program_run(& prog)) {}

    Program_del(& prog);

    return 0;
}