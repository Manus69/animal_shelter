#include "DB.h"

#include "../master.h"
#include "../data/IAnimal.h"

#include <stdio.h>

static const char * _sql[] =
{
    [_SQL_CREATE] = "create table if not exists animals (id integer primary key not null, "\
    "species int, name text, age int, commands int, owner text, capacity int);",

    [_SQL_SEL_ID] = "select * from animals where id=?;",

    [_SQL_SEL_SPECIES] = "select * from animals where species=?;",

    [_SQL_SEL_AGE] = "select * from animals where age=?;",

    [_SQL_INS] = "insert into animals (species, name, age, commands, owner, capacity) values "\
    "(?, ?, ?, ?, ?, ?);",

    [_SQL_UPD_CMD] = "update animals set commands=? where id=?;",
    
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
        if ((res = sqlite3_prepare_v2(db->db, _sql[k], -1, & db->stmts + k, 0))) return res;
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

        printf("id : %3d | ");
        Animal_dbg(aml);
        Animal_del(aml);
    }

    return res == SQLITE_DONE ? ERR_NONE : ERR_DB;
}

ERR DB_select_id(DB * db, int id)
{
    sqlite3_bind_int(db->stmts[_SQL_SEL_ID], 1, id);

    return _print_rows(db->stmts[_SQL_SEL_ID]);
}

ERR DB_select_age(DB * db, int age)
{
    sqlite3_bind_int(db->stmts[_SQL_SEL_AGE], 1, age);

    return _print_rows(db->stmts[_SQL_SEL_AGE]);
}

ERR DB_select_species(DB * db, SPECIES species)
{
    sqlite3_bind_int(db->stmts[_SQL_SEL_SPECIES], 1, species);

    return _print_rows(db->stmts[_SQL_SEL_SPECIES]);
}

ERR DB_insert(DB * db, const Animal * aml)
{

}

ERR DB_update_cmds(DB * db, int id, Cmd cmd)
{
    sqlite3_bind_int(db->stmts[_SQL_UPD_CMD], 1, cmd);
    sqlite3_bind_int(db->stmts[_SQL_UPD_CMD], 2, id);

    return sqlite3_step(db->stmts[_SQL_UPD_CMD]) == SQLITE_DONE ? ERR_NONE : ERR_DB;
}

ERR DB_init(DB ** db)
{
    int rst;

    if ((* db = calloc(1, sizeof(* db))))
    {
        if ((rst = sqlite3_open(DB_PATH, & (* db)->db)))
        {
            free(db);

            return ERR_IO;
        }
        
        return _create(* db) ? ERR_SQL : ERR_NONE;
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

