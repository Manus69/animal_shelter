#include "master.h"
#include "data/IPet.h"
#include "data/ISumpter.h"
#include "data/IAnimal.h"
#include "data/Err.h"

#include <stdio.h>

ERR Animal_build(const char * cstr, Animal ** animal);

int main()
{
    char buff[1 << 10] = {};
    Animal * aml;

    if (Animal_build("cat cock 69 [run]", & aml)) return printf("fuck");

    Animal_cstr(aml, buff);
    printf("%s\n", buff);

    Animal_del(aml);

    return 0;
}