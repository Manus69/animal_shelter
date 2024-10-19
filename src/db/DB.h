#ifndef DB_H
#define DB_H

#include "IDB.h"
#include "../sqlite/sqlite3.h"
#include "../data/IAnimal.h"

#define DB_PATH ".db"
#define Stmt    sqlite3_stmt

struct DB
{
    sqlite3 * db;
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
Animal *    Dto_Animal(const Dto * dto);


#endif