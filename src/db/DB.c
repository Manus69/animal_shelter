#include "DB.h"

#include "../master.h"
#include "../data/IAnimal.h"

#include <stdio.h>

static const char * _sql[] =
{
    [_SQL_CREATE] = "create table if not exists animals (id integer primary key not null, "\
    "species int, name text, age int, commands int, owner text, capacity int);",

    [_SQL_SEL_ALL] = "select * from animals;",

    [_SQL_SEL_ID] = "select * from animals where id=?;",

    [_SQL_SEL_SPECIES] = "select * from animals where species=?;",

    [_SQL_SEL_AGE] = "select * from animals where age=?;",

    [_SQL_INS] = "insert into animals (species, name, age, commands, owner, capacity) values "\
    "(?, ?, ?, ?, ?, ?);",

    [_SQL_UPD_CMD] = "update animals set commands=? where id=?;",

    [_SQL_UPD_ALL] = "update animals set species=?, name=?, age=?, commands=?, owner=?, capacity=? where id=?;",
    
    [_SQL_DEL_ID] = "delete from animals where id=?;",
    
    [_SQL_DEL_SPECIES] = "delete from animals where species=?;",
    
    [_SQL_DEL_AGE] = "delete from animals where age=?;",

    NULL,
};

static int _stmt_init(DB * db)
{
    int res;

    for (int k = 0; k < _SQL_COUNT; k ++)
    {
        if ((res = sqlite3_prepare_v2(db->db, _sql[k], -1, & (db->stmts[k]), 0))) return res;
    }

    return 0;
}

static int _create(DB * db)
{
    return sqlite3_step(db->stmts[_SQL_CREATE]);
}

static ERR _print_rows(Stmt * stmt)
{
    Animal *    aml;
    Dto         dto;
    int         res;

    while ((res = sqlite3_step(stmt)) == SQLITE_ROW)
    {
        dto = row_Dto(stmt);
        aml = Dto_Animal(dto);

        printf("id : %3d | ", dto.id);
        Animal_dbg(aml);
        Animal_del(aml);
    }

    return res == SQLITE_DONE ? ERR_NONE : ERR_DB;
}

ERR DB_print_all(DB * db)
{
    return _print_rows(db->stmts[_SQL_SEL_ALL]);
}

ERR DB_print_age(DB * db, int age)
{
    sqlite3_reset(db->stmts[_SQL_SEL_AGE]);
    sqlite3_bind_int(db->stmts[_SQL_SEL_AGE], 1, age);

    return _print_rows(db->stmts[_SQL_SEL_AGE]);
}

ERR DB_print_species(DB * db, SPECIES species)
{
    sqlite3_reset(db->stmts[_SQL_SEL_SPECIES]);
    sqlite3_bind_int(db->stmts[_SQL_SEL_SPECIES], 1, species);

    return _print_rows(db->stmts[_SQL_SEL_SPECIES]);
}

ERR DB_get_by_id(DB * db, int id, Animal ** aml)
{
    int res;

    sqlite3_reset(db->stmts[_SQL_SEL_ID]);
    sqlite3_bind_int(db->stmts[_SQL_SEL_ID], 1, id);

    * aml = 0;
    if ((res = sqlite3_step(db->stmts[_SQL_SEL_ID])) == SQLITE_ROW)
    {
        * aml = Dto_Animal(row_Dto(db->stmts[_SQL_SEL_ID]));
    }

    return res == SQLITE_ROW || res == SQLITE_DONE ? ERR_NONE : ERR_DB;
}

static ERR _step(Stmt * stmt)
{
    return sqlite3_step(stmt) == SQLITE_DONE ? ERR_NONE : ERR_DB;
}

ERR DB_insert(DB * db, const Animal * aml)
{
    Dto dto;

    dto = Animal_Dto(aml);
    Stmt_Dto_bind(db->stmts[_SQL_INS], dto);

    return _step(db->stmts[_SQL_INS]);
}

ERR DB_update_cmds(DB * db, int id, Cmd cmd)
{
    sqlite3_bind_int(db->stmts[_SQL_UPD_CMD], 1, cmd);
    sqlite3_bind_int(db->stmts[_SQL_UPD_CMD], 2, id);

    return _step(db->stmts[_SQL_UPD_CMD]);
}

ERR DB_update(DB * db, int id, const Animal * aml)
{
    Dto dto;

    dto = Animal_Dto(aml);
    Stmt_Dto_bind(db->stmts[_SQL_UPD_ALL], dto);
    sqlite3_bind_int(db->stmts[_SQL_UPD_ALL], TBL_COL_COUNT, id);

    return _step(db->stmts[_SQL_UPD_ALL]);
}

static ERR _del_int(Stmt * stmt, int x)
{
    sqlite3_reset(stmt);
    sqlite3_bind_int(stmt, 1, x);

    return _step(stmt);
}

ERR DB_del_id(DB * db, int id)
{
    return _del_int(db->stmts[_SQL_DEL_ID], id);
}

ERR DB_del_age(DB * db, int age)
{
    return _del_int(db->stmts[_SQL_DEL_AGE], age);
}

ERR DB_del_species(DB * db, SPECIES species)
{
    return _del_int(db->stmts[_SQL_DEL_SPECIES], species);
}

ERR DB_init(DB ** db)
{
    int res;

    if ((* db = calloc(1, sizeof(DB))))
    {
        if ((res = sqlite3_open(DB_PATH, & (* db)->db)))
        {
            free(* db);

            return ERR_IO;
        }

        if ((res = _stmt_init(* db)))
        {
            free(* db);

            return ERR_SQL;
        }
        
        return _create(* db) == SQLITE_DONE ? ERR_NONE : ERR_DB;
    }

    return ERR_MEM;
}


ERR DB_deinit(DB * db)
{
    int val;

    for (int k = 0; k < _SQL_COUNT; k ++)
    {
        sqlite3_finalize(db->stmts[k]);
    }

    val = sqlite3_close(db->db);
    free(db);

    return val == SQLITE_OK ? ERR_NONE : ERR_DB;
}

