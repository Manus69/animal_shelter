#include "Err.h"

char * Err_cstr(ERR err)
{
    static const char * _strings[ERR_COUNT] = 
    {
        [ERR_NONE] = "Ok",
        [ERR_DB] = "Db error",
        [ERR_IO] = "IO error",
        [ERR_LOGIC] = "Logic error",
        [ERR_MEM] = "Memory error",
        [ERR_PARSE] = "Parse error",
        [ERR_SQL] = "SQL error",
        [ERR_UNDEF] = "Unknown error",
        [ERR_VAL] = "Value error",
    };

    return _strings[err];
}