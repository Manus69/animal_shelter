#ifndef IDB_H
#define IDB_H

#include "../data/Err.h"
#include "../data/IAnimal.h"

typedef struct DB DB;

ERR DB_init(DB ** db);
ERR DB_deinit(DB * db);
ERR DB_put(DB * db, const Animal * aml);
ERR DB_get(DB * db, int id, Animal ** aml);
ERR DB_print(DB * db);

//
ERR DB_print1(DB * db);
ERR DB_test(DB * db);


#endif