#include "./sqlite/sqlite3.h"
#include "io.h"

#include <stdio.h>

const char * stmt = 
"CREATE TABLE ANIMALS(" \
"ID INT PRIMARY KEY NOT NULL," \
"NAME TEXT," \
"AGE INT );";


int main(int argc, char ** argv)
{
    
    if (argc == 1) return io_msg_help();


}