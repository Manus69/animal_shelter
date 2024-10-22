#ifndef IDB_H
#define IDB_H

#include "../data/Err.h"
#include "../data/IAnimal.h"

typedef struct DB DB;

ERR DB_init(DB ** db);
ERR DB_deinit(DB * db);
ERR DB_get_by_id(DB * db, int id, Animal ** aml);
ERR DB_get_by_name(DB * db, const char * name, int len, Animal ** aml);
ERR DB_insert(DB * db, const Animal * aml);
ERR DB_remove_by_id(DB * db, int id, Animal ** aml);
ERR DB_update(DB * db, int id, const Animal * aml);
ERR DB_print(DB * db);


#endif