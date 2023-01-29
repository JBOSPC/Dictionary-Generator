<set name> - definition of set.
"chars" - definition of string.

insert <set name> <{"chars", ...}> - For adding new set. For example insert ex_set_name {"r_chars", "r_chars2"}
delete <set name> - For removing added set. For example delete ex_set_name;
pattern <<set name>> - For adding pattern. For example <ex_set_name1> <ex_set_name2>
file <path_to_file or NULL> - For adding alternative output. If empty, keys will be printing in standard output - NULL for clear path. For example file /home/example.
threads <threads amount> - For changing amount of using threads in key generating. For example threads 4.
load <file_path> - For loading commands directly from file. Also works if passed to argv (./Dictionary_Generator <file_path1> <file_path2>...).
size - For checking amount of keys which will created on current pattern.
data - For informations about added data.
clear - For clearing all data.
run - For starting key generating.
exit - For closing program.
help - For program instructions.
