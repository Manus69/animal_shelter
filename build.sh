#!/bin/sh

files=$(find . -type f -name "*.c" -not -path "*/sqlite/*")
# echo "$files"
obj=src/sqlite/sqlite3.o

echo "gcc -Wall -Wextra -g3 $files $obj"
gcc -Wall -Wextra -g3 $files $obj

# echo "gcc -Wall -Wextra -g3 -fsanitize=address $files $obj"
# gcc -Wall -Wextra -g3 -fsanitize=address $files $obj