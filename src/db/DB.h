#ifndef DB_H
#define DB_H

#include "IDB.h"
#include "../sqlite/sqlite3.h"
#include <unistd.h>

#define DB_PATH ".db"

struct DB
{
    sqlite3 * db;
};

#endif