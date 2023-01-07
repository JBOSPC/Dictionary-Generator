Description:
------------
This program is console application which generates dictionaries for brute-force/dictionary attacks using multithreading. 
Output can be saving to file or printing to standart output, where it can be use by other program.

Before run program check whether your files was downloaded correctly:

SHA hash verification:
----------------------
make sha-verification - For check hash.

GPG signature check:
--------------------
make gpg-verification - For sign verification.
Optionally:
gpg --list-key - For remove key.
gpg --delete-key <key_id> - For remove added key.

Run program:
------------
make - For compilation.
make run or ./Dictionary_Generator - For run program.

