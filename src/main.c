#include "master.h"
#include "data/IPet.h"
#include "data/ISumpter.h"
#include "data/IAnimal.h"
#include "data/Err.h"

#include <stdio.h>

ERR Animal_from_cstr(const char * cstr, Animal ** animal);

int main()
{
    char buff[1 << 10] = {};

    // Pet * pet = Pet_new(SPECIES_ASS, "cock", 10, 0, "ass");

    // // printf("%s\n%s\n%d\n", Animal_name((Animal *) pet), Pet_owner(pet), Animal_age((Animal *) pet));
    // // Animal_cstr((Animal *) pet, buff);
    // Pet_cstr(pet, buff);
    // printf("%s\n", buff);

    // int x;

    // int len = lib_parse_int("  \t-1", & x);
    // printf("%d %d\n", x, len);

    // Pet_del(pet);

    Animal * animal;

    if (Animal_from_cstr("cat cock 69 xx", & animal)) return printf("fucked\n");

    Animal_cstr(animal, buff);
    printf("%s\n", buff);

    Animal_del(animal);    

    return 0;
}