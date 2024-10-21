#include "DB.h"

#include "../master.h"
#include "../data/IAnimal.h"

#include <stdio.h>

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

#define _TBL_NAME           "animals"
#define _TBL_SPECIES        "species"
#define _TBL_NAME_FLD       "name"
#define _TBL_AGE            "age"
#define _TBL_CMDS           "commands"
#define _TBL_OWNER          "owner"
#define _TBL_CAPACITY       "capacity"
#define _SQL_TBL_CREATE     "create table if not exists " \
                            _TBL_NAME " (id integer primary key not null," \
                            _TBL_SPECIES " int," \
                            _TBL_NAME_FLD " text," \
                            _TBL_AGE " int," \
                            _TBL_CMDS " int," \
                            _TBL_OWNER " text," \
                            _TBL_CAPACITY " int);"

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

ERR DB_init(DB ** db)
{
    int rst;

    if ((* db = calloc(1, sizeof(* db))))
    {
        rst = sqlite3_open(DB_PATH, & (* db)->db);
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

ERR DB_print(DB * db)
{

}

static Dto _row_Dto(Stmt * stmt)
{
    Dto dto = {};

    dto.id = sqlite3_column_int(stmt, TBL_COL_ID);
    dto.species = sqlite3_column_int(stmt, TBL_COL_SPECIES);
    dto.name = sqlite3_column_text(stmt, TBL_COL_NAME);
    dto.age = sqlite3_column_int(stmt, TBL_COL_AGE);
    dto.cmds = sqlite3_column_int(stmt, TBL_COL_CMDS);
    dto.owner = sqlite3_column_text(stmt, TBL_COL_OWNER);
    dto.capacity = sqlite3_column_int(stmt, TBL_COL_CAPACITY);

    return dto;
}

static void _Dto_bind(Stmt * stmt, Dto dto)
{
    sqlite3_bind_int(stmt, TBL_COL_SPECIES, dto.species);
    sqlite3_bind_text(stmt, TBL_COL_NAME, dto.name, -1, SQLITE_STATIC);
    sqlite3_bind_int(stmt, TBL_COL_AGE, dto.age);
    

}

ERR DB_get_by_id(DB * db, int id, Animal ** aml)
{
    const char * sql = "select * from " _TBL_NAME " where id=?;";
    Stmt *  stmt;
    Dto     dto;

    * aml = 0;
    if (sqlite3_prepare_v2(db->db, sql, -1, & stmt, 0)) return ERR_SQL;

    sqlite3_bind_int(stmt, 1, id);
    if (sqlite3_step(stmt) != SQLITE_ROW) return ERR_DB;

    dto = _row_Dto(stmt);
    * aml = Dto_Animal(dto);

    return ERR_NONE;
}

ERR DB_get_by_name(DB * db, const char * name, Animal ** aml)
{
    char * sql = "select * from " _TBL_NAME " where name=?;";
    Stmt * stmt;

    * aml = 0;
    if (sqlite3_prepare_v2(db->db, sql, -1, & stmt, 0)) return ERR_SQL;

    sqlite3_bind_text(stmt, 1, name, -1, SQLITE_STATIC);
    if (sqlite3_step(stmt) != SQLITE_ROW) return ERR_DB;

    * aml = Dto_Animal(_row_Dto(stmt));

    return ERR_NONE;
}

ERR DB_insert(DB * db, const Animal * aml)
{
    char * sql = "insert into " _TBL_NAME " (" \
    _TBL_SPECIES ", " \
    _TBL_NAME_FLD ", " \
    _TBL_AGE ", " \
    _TBL_CMDS ", " \
    _TBL_OWNER ", " \
    _TBL_CAPACITY ")" \
    " values (?, ?, ?, ?, ?, ?);";
}

ERR DB_update(DB * db, int id, Dto dto)
{

}

ERR DB_remove_by_id(DB * db, int id, Animal ** aml)
{

}

ERR DB_purge(DB * db, SPECIES species)
{

}