#include "Input.h"

#include <stdio.h>

#define MSG_HELP "fuck you!" 

int io_msg_print(const char * msg, int rval)
{
    printf("%s\n", msg);

    return rval;
}

int io_msg_help(void)
{
    io_msg_print(MSG_HELP, 1);
}

CMD io_parse_cmd(const char * cstr)
{
    
}