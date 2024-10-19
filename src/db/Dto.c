#include "../master.h"
#include "../data/IAnimal.h"
#include "../data/IPet.h"
#include "../data/ISumpter.h"
#include "DB.h"

Dto Animal_Dto(const Animal * aml)
{
    Dto dto = {};

    dto.species = Animal_species(aml);
    dto.name = Animal_name(aml);
    dto.age = Animal_age(aml);
    dto.cmds = Animal_Cmd(aml);

    if (Animal_is_Pet(aml)) dto.owner = Pet_owner((Pet *) aml);
    if (Animal_is_Sumpter(aml)) dto.capacity = Sumpter_capacity((Sumpter *) aml);

    return dto;
}

Animal * Dto_Animal(const Dto * dto)
{
    if (SPECIES_is_Pet(dto->species))
    {
        return (Animal *) Pet_new(dto->species, dto->name, dto->age, dto->cmds, dto->owner);
    }
    if (SPECIES_is_Sumpter(dto->species))
    {
        return (Animal *) Sumpter_new(dto->species, dto->name, dto->age, dto->cmds, dto->capacity);
    }

    assert(0);
}
