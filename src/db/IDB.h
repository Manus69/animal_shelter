#ifndef IDB_H
#define IDB_H

#include "../data/Err.h"
#include "../data/IAnimal.h"

typedef struct DB DB;

ERR DB_init(DB ** db);
ERR DB_deinit(DB * db);


#endif