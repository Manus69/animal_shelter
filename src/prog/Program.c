#include "Program.h"
#include "../lib/lib.h"

#include <stdio.h>

ERR Program_init(Program * prog)
{
    * prog = (Program) {};

    if ((prog->err = DB_init(& prog->db))) return prog->err;

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

void Program_help_msg(const Program * prog)
{
    (void) prog;

    printf("Usage: enter commands into the termial\n" \
            "Commands: \n" \
            "\t`" PROG_CMD_HELP "` - display the help message\n"
            "\t`" PROG_CMD_PRINT "` (species) - print table\n" \
            "\t`" PROG_CMD_ADD "` species name age ([commands]) (owner) (capacity) - add an animal\n"\
            "\t`" PROG_CMD_GET "` id - get an animal with the id and go into interactive mode\n" \
            "\t`" PROG_CMD_REM "` id | species - remove an animal or the whole species\n"\
            "\t`" PROG_CMD_QUIT "` - quit\n");
}

void Program_help_inter_msg(const Program * prog)
{
    (void) prog;

    printf("Interactive mode:\n"\
            "Enter the command you want the animal to perform or `" PROG_CMD_TEACH \
            "` to teach a new command\n"\
            "\t`"PROG_CMD_INFO "` - display info\n"\
            "\t`"PROG_CMD_DONE "` - exit interactive mode\n");
}