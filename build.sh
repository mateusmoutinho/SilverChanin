rm -rf release
mkdir release
./silverchain.o --tags api_dependencies  api_const  api_type api_declare api_define cli_dependencies cli_consts cli_type cli_globals  cli_declare cli_define --src src --project_short_cut  SilverChain
./CAmalgamator.o --file   src/cli/main.c -o release/SilverChain.c
./CAmalgamator.o --file src/imports/imports.api_define.h  -o release/SilverChainApiOne.h
./CAmalgamator.o --file  src/imports/imports.api_define.h  -o release/CSilverChainApiNoDependenciesIncluded.h \
--noinclude  dependencies
