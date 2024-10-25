#ifndef IDB_H
#define IDB_H

#include "../data/Err.h"
#include "../data/IAnimal.h"

typedef struct DB DB;

ERR DB_print_all(DB * db);
ERR DB_get_by_id(DB * db, int id, Animal ** aml);
ERR DB_print_age(DB * db, int age);
ERR DB_print_species(DB * db, SPECIES species);
ERR DB_insert(DB * db, const Animal * aml);
ERR DB_update_cmds(DB * db, int id, Cmd cmd);
ERR DB_update(DB * db, int id, const Animal * aml);
ERR DB_del_id(DB * db, int id);
ERR DB_del_age(DB * db, int age);
ERR DB_del_species(DB * db, SPECIES species);
ERR DB_count(DB * db, int * x);
ERR DB_init(DB ** db);
ERR DB_deinit(DB * db);

#endif