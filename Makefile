# Source code paths:
HeaderLibsPath = Libs/Headers
LibsPath = Libs
Headers = ${HeaderLibsPath}/Exponential_notation.h ${HeaderLibsPath}/Generation_functions.h ${HeaderLibsPath}/Generation_worker.h
Libs = ${LibsPath}/Generation_worker.cpp ${LibsPath}/Generation_functions.cpp ${LibsPath}/Exponential_notation.cpp
MainFiles = Dictionary_Generator.cpp 
# Verification files paths:
SHAFile = SHA512SUMS
GPGKeyFile = public_key.gpg
GPGFile = SHA512SUMS.asc
# Compilation arguments:
STD = c++17
CC = g++
Flags = -pthread
OutputName = Dictionary_Generator

# Compilation:
${OutputName}: ${Headers} ${Libs} ${MainFiles}
	${CC} --std=${STD} ${Flags} ${MainFiles} ${Libs} -o ${OutputName}

# Running program:
run: ${OutputName}
	./${OutputName}

# SHA verification:
sha-verification: ${SHAFile}
	sha512sum --ignore-missing --check ${SHAFile}

# GPG signature verification with adding key:
gpg-verification: ${GPGFile} ${GPGKeyFile} ${SHAFile}
	gpg --import ${GPGKeyFile}
	gpg --verify ${GPGFile} ${SHAFile}
