
//silver_chain_scope_start
//mannaged by silver chain
#include "../../imports/imports.cli_dependencies.h"
//silver_chain_scope_end

#define SRC_FLAG "s | src | source"
#define IMPORT_FLAG "i | i mportdir"
#define TAG_FLAG "t | tags"
#define PROJECT_SHORT_CUT_FLAG "p | project_short_cut"
#define IMPLEMENT_MAIN_FLAG "m | implement_main"
#define MAIN_NAME_FLAG "n | main_name"
#define MAIN_PATH_FLAG "p | main_path"
#define SLEEP_TIME_FLAG "s | sleep_time"
#define WATCH_FLAG "w | watch"
#define HELP_FLAG "h | help"

#define SRC_DESCRIPTION "The folder of the project(required)"
#define IMPORT_DESCRIPTION "The directory to be used to save imports (default: imports)"
#define TAG_DESCRIPTION "The tags to be used (required)"
#define PROJECT_SHORT_CUT_DESCRIPTION "The project short cut to be used in #ifndef props (default: silverchain)"
#define IMPLEMENT_MAIN_DESCRIPTION "true or false to implement the main function (default: false)"
#define MAIN_NAME_DESCRIPTION "The name of the main function (default: main.c or main.cpp)"
#define MAIN_PATH_DESCRIPTION "The path of the main function (default: not set)"
#define HELP_DESCRIPTION "Show the help message"
#define WATCH_DESCRIPTION "Watch the project and generate the code when the project changes"
#define SLEEP_TIME_DESCRIPTION "The time to sleep between each check (default: 0)"
#define HELP_MESSAGE "Usage: silverchain [options]\nOptions:" \
BLUE"\n  -h, --help\t\t\t" GREEN HELP_DESCRIPTION RESET  \
BLUE"\n  -s, --src\t\t\t" GREEN SRC_DESCRIPTION RESET \
BLUE"\n  -i, --importdir\t\t" GREEN IMPORT_DESCRIPTION RESET \
BLUE"\n  -t, --tags\t\t\t" GREEN TAG_DESCRIPTION RESET \
BLUE"\n  -p, --project_short_cut\t" GREEN PROJECT_SHORT_CUT_DESCRIPTION RESET \
BLUE"\n  -m, --implement_main\t\t" GREEN IMPLEMENT_MAIN_DESCRIPTION RESET \
BLUE"\n  -n, --main_name\t\t" GREEN MAIN_NAME_DESCRIPTION RESET \
BLUE"\n  -p, --main_path\t\t" GREEN MAIN_PATH_DESCRIPTION RESET \
BLUE"\n  -w, --watch\t\t\t" GREEN WATCH_DESCRIPTION RESET \
BLUE"\n  -s, --sleep_time\t\t" GREEN SLEEP_TIME_DESCRIPTION RESET \
"\n"
