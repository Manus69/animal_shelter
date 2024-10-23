#include "Program.h"

#include <stdio.h>

static ERR _err_and_die(const Program * prog)
{
    ERR err;

    err = Program_status(prog);
    printf("%s\n", Err_cstr(err));

    return err;
}

//simgle quotes for name\owner?
//db path is all fucked up
//compile all statements at intit, bind when necessary?

int main()
{
    Program prog;

    if (Program_init(& prog)) return _err_and_die(& prog);

    while (Program_run(& prog)) {}
    
    // Cmd cmd = 0;
    // Cmd_add(& cmd, CMD_RUN);
    // Cmd_add(& cmd, CMD_JUMP);
    
    // char buff[1000] = {};
    // Cmd_cstr(cmd, buff);
    // printf("%s\n", buff);

    Program_del(& prog);

    return 0;
}