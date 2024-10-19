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
// leave ? and bind ?
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

    // printf("%s\n", _SQL_TBL_CREATE);
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

static Dto _row_to_dto(sqlite3_stmt * stmt)
{
    Dto dto = {};

    dto.id = sqlite3_column_int(stmt, TBL_COL_ID);
    dto.species = sqlite3_column_int(stmt, TBL_COL_SPECIES);
    dto.name = (char *) sqlite3_column_text(stmt, TBL_COL_NAME);
    dto.age = sqlite3_column_int(stmt, TBL_COL_AGE);
    dto.cmds = sqlite3_column_int(stmt, TBL_COL_CMDS);
    dto.owner = (char *) sqlite3_column_text(stmt, TBL_COL_OWNER);
    dto.capacity = sqlite3_column_int(stmt, TBL_COL_CAPACITY);

    return dto;
}

static void _row_print(sqlite3_stmt * stmt)
{
    Dto         dto;
    Animal *    aml;

    dto = _row_to_dto(stmt);
    aml = Dto_Animal(& dto);

    printf("id = %d ", dto.id);
    Animal_dbg(aml);
    Animal_del(aml);
}

ERR DB_print(DB * db)
{
    const char * _sql = "select * from " _TBL_NAME ";";
    sqlite3_stmt * stmt;

    int rst;

    if (sqlite3_prepare_v2(db->db, _sql, -1, & stmt, 0)) return ERR_SQL;

    while (true)
    {
        rst = sqlite3_step(stmt);
        if (rst != SQLITE_ROW) break;

        _row_print(stmt);
    }

    sqlite3_finalize(stmt);

    return rst == SQLITE_DONE ? ERR_NONE : ERR_DB;
}

ERR DB_put(DB * db, const Animal * aml)
{
    Stmt *  stmt;
    Dto     dto;

    dto = Animal_Dto(aml);
    const char * _sql = "insert into animals (species, name, age, commands, owner, capacity)" \
                        "values (?1, ?2, ?3, ?4, ?5, ?6);";
    
    if (sqlite3_prepare_v2(db->db, _sql, -1, & stmt, 0)) return ERR_SQL;

    sqlite3_bind_int(stmt, 1, dto.species);
    sqlite3_bind_text(stmt, 2, dto.name, -1, SQLITE_STATIC);
    sqlite3_bind_int(stmt, 3, dto.age);
    sqlite3_bind_int(stmt, 4, dto.cmds);
    sqlite3_bind_int(stmt, 6, dto.capacity);

    if  (dto.owner) sqlite3_bind_text(stmt, 5, dto.owner, -1, SQLITE_STATIC);
    else sqlite3_bind_null(stmt, 5);

    if (sqlite3_step(stmt) != SQLITE_DONE) return ERR_DB;

    sqlite3_finalize(stmt);

    return ERR_NONE;
}

ERR DB_get(DB * db, int id, Animal ** aml)
{
    const char * _sql = "select * from animals where id=?1;";
    Stmt * stmt;

    if (sqlite3_prepare_v2(db->db, _sql, -1, & stmt, 0)) return ERR_SQL;

    if (sqlite3_step(stmt) != SQLITE_ROW) return ERR_DB;
    _row_print(stmt);

    sqlite3_finalize(stmt);

    return ERR_NONE;
}

// ERR DB_update(DB * db, int id, const Animal * aml)
// {

// }

