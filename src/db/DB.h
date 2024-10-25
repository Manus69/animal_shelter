#ifndef DB_H
#define DB_H

#include "IDB.h"
#include "../sqlite/sqlite3.h"
#include "../data/IAnimal.h"

#define DB_PATH ".db"

typedef sqlite3_stmt Stmt;

typedef enum
{
    TBL_COL_ID,
    TBL_COL_SPECIES,
    TBL_COL_NAME,
    TBL_COL_AGE,
    TBL_COL_CMDS,
    TBL_COL_OWNER,
    TBL_COL_CAPACITY,
    TBL_COL_COUNT,
}   TBL_COL;

typedef enum
{
    _SQL_CREATE,
    _SQL_COUNT_ROWS,
    _SQL_SEL_ALL,
    _SQL_SEL_ID,
    _SQL_SEL_SPECIES,
    _SQL_SEL_AGE,
    _SQL_INS,
    _SQL_UPD_CMD,
    _SQL_UPD_ALL,
    _SQL_DEL_ID,
    _SQL_DEL_SPECIES,
    _SQL_DEL_AGE,
    _SQL_COUNT,
}   _SQL;

struct DB
{
    Stmt *      stmts[_SQL_COUNT];
    sqlite3 *   db;
};

typedef struct
{
    char *  name;
    char *  owner;
    int     id;
    int     species;
    int     age;
    int     cmds;
    int     capacity;
}   Dto;

Dto         Animal_Dto(const Animal * aml);
Animal *    Dto_Animal(Dto dto);
Dto         row_Dto(Stmt * stmt);
void        Stmt_Dto_bind(Stmt * stmt, Dto dto);


#endif