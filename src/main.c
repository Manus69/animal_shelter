#include "master.h"
#include "data/IPet.h"
#include "data/ISumpter.h"
#include "data/IAnimal.h"
#include "db/IDB.h"

#include <stdio.h>

ERR Animal_build(const char * cstr, Animal ** animal);
ERR Animal_build_Str(Str str, Animal ** animal);

//simgle quotes for name\owner?
//db path is all fucked up

int main()
{
    // char buff[1 << 10] = {};
    // Animal * aml;

    // if (Animal_build("dog cock 69 -1 ", & aml)) return printf("fuck");

    // Animal_cstr(aml, buff);
    // printf("%s\n", buff);

    // Animal_del(aml);

    DB * db;

    if (! DB_init(& db))
    {
        Animal * aml;
        if (Animal_build("dog fag 10", & aml)) return printf("err");
        if (DB_insert(db, aml)) return printf("err");

        DB_deinit(db);
        Animal_del(aml);
    }

    return 0;
}