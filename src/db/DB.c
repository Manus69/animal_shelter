#include "DB.h"

#include "../master.h"

#define _SQL_TBL_CREATE     "create table if not exists animals (id integer primary key not null," \
                            "species int, " \
                            "name text," \
                            "age int," \
                            "commands int," \
                            "owner text," \
                            "capacity int);"

static ERR _create_table(DB * db)
{
    sqlite3_stmt *  stmt;
    int             rst;

    rst = sqlite3_prepare_v2(db->db, _SQL_TBL_CREATE, -1, & stmt, 0);
    if (rst) return ERR_SQL;

    rst = sqlite3_step(stmt);
    if (rst != SQLITE_DONE) return ERR_SQL;

    sqlite3_finalize(stmt);

    return ERR_NONE;
}

#include <stdio.h>
ERR DB_init(DB ** db)
{
    int rst;

    if ((* db = calloc(1, sizeof(* db))))
    {
        rst = sqlite3_open(DB_PATH, & (* db)->db);
        printf("%d\n", rst);
        if (rst) return ({free(* db); ERR_DB;});
        
        return _create_table(* db);
    }

    return ERR_MEM;
}

ERR DB_deinit(DB * db)
{
    int val;

    val = sqlite3_close(db->db);
    free(db);

    return val == SQLITE_OK ? ERR_NONE : ERR_DB;
}

// ERR DB_put(DB * db, const Animal * aml)
// {

// }

// ERR DB_get(DB * db, int id, Animal ** aml)
// {

// }

// ERR DB_update(DB * db, int id, const Animal * aml)
// {

// }

