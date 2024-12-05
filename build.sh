rm -rf release
mkdir release
gcc src/cli/main.c -o CAmalgamator.o
./CAmalgamator.o --file   src/cli/main.c -o release/SilverChain.c
./CAmalgamator.o --file src/imports/imports.api_define.h  -o release/SilverChainApiOne.h
./CAmalgamator.o --file  src/imports/imports.api_define.h  -o release/CSilverChainApiNoDependenciesIncluded.h \
--noinclude  dependencies