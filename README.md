Description:
------------
This program is console application which generates dictionaries for brute-force/dictionary attacks using multithreading. 
Output can be saving to file or printing to standart output, where it can be use by other program.

Compilation:
------------
For compilation use C++17 standart and with -pthread flag:
g++ -std=c++17 -pthread *.cpp

Usage:
------
<set name> - definition of set.
"chars" - definition of string.

insert <set name> <{"chars", ...}> - For adding new set.
delete <set name> - For removing added set.
pattern <<set name>> - For adding pattern.
file <path_to_file or NULL> - For adding alternative output. If empty, keys will be printing in standard output - NULL for clear path.
threads <threads amount> - For specify amount of using threads in key generating.
size - For checking amount of keys which will created on current pattern.
data - For informations about added data.
clear - For clearing all data.
run - For starting key generating.
exit - For closing program.
help - For program instructions.
