#include "prog/Program.h"

#include <stdio.h>

static ERR _err_and_die(const Program * prog)
{
    ERR err;

    err = Program_status(prog);
    printf("%s\n", Err_cstr(err));

    return err;
}

//simgle quotes for name\owner?

int main()
{
    Program prog;

    if (Program_init(& prog)) return _err_and_die(& prog);

    while (Program_run(& prog)) {}

    // int x;

    // DB_count(prog.db, & x);
    // printf("%d\n", x);

    Program_del(& prog);

    return 0;
}