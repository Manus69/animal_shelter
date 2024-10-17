#include "master.h"
#include "data/IAnimal.h"
#include "data/Pet.h"

#include <stdio.h>

int main()
{
    Pet * pet = Pet_new(SPECIES_ASS, "cock", 10, 0, "ass");

    printf("%s\n%s\n%d\n", Animal_name((Animal *) pet), Pet_owner(pet), Animal_age((Animal *) pet));

    Pet_del(pet);

    return 0;
}