#ifndef ERR_H
#define ERR_H

typedef enum
{
    ERR_NONE,
    ERR_IO,
    ERR_PARSE,
    ERR_VAL,
    ERR_MEM,
    ERR_SQL,
    ERR_UNDEF,
    ERR_COUNT,
}   ERR;

#endif