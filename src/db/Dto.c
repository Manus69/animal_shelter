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

Animal * Dto_Animal(Dto dto)
{
    if (SPECIES_is_Pet(dto.species))
    {
        return (Animal *) Pet_new(dto.species, dto.name, dto.age, dto.cmds, dto.owner);
    }
    if (SPECIES_is_Sumpter(dto.species))
    {
        return (Animal *) Sumpter_new(dto.species, dto.name, dto.age, dto.cmds, dto.capacity);
    }

    assert(0);
}

Dto row_Dto(Stmt * stmt)
{
    Dto dto = {};

    dto.id = sqlite3_column_int(stmt, TBL_COL_ID);
    dto.species = sqlite3_column_int(stmt, TBL_COL_SPECIES);
    dto.name = (char *) sqlite3_column_text(stmt, TBL_COL_NAME);
    dto.age = sqlite3_column_int(stmt, TBL_COL_AGE);
    dto.cmds = sqlite3_column_int(stmt, TBL_COL_CMDS);
    dto.owner = (char *) sqlite3_column_text(stmt, TBL_COL_OWNER);
    dto.capacity = sqlite3_column_int(stmt, TBL_COL_CAPACITY);

    return dto;
}

void Stmt_Dto_bind(Stmt * stmt, Dto dto)
{
    sqlite3_bind_int(stmt, TBL_COL_SPECIES, dto.species);
    sqlite3_bind_text(stmt, TBL_COL_NAME, dto.name, -1, SQLITE_STATIC);
    sqlite3_bind_int(stmt, TBL_COL_AGE, dto.age);
    sqlite3_bind_int(stmt, TBL_COL_CMDS, dto.cmds);
    sqlite3_bind_text(stmt, TBL_COL_OWNER, dto.owner, -1, SQLITE_STATIC);
    sqlite3_bind_int(stmt, TBL_COL_CAPACITY, dto.capacity);
}