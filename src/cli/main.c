
//silver_chain_scope_start
//mannaged by silver chain
#include "../imports/imports.cli_globals.h"
//silver_chain_scope_end



int main(int argc,char *argv[]){

    dtw = newDtwNamespace();
    stack = newCTextStackModule();
    cli = newCliNamespace();
    UniversalGarbage *garbage = newUniversalGarbage();

    CliEntry *entry = newCliEntry(argc,argv);
    UniversalGarbage_add(garbage,cli.entry.free,entry);

    CliFlag *help_flag = cli.entry.get_flag(entry,HELP_FLAG,CLI_NOT_CASE_SENSITIVE);
    if(help_flag->exist){
        printf(HELP_MESSAGE);
        UniversalGarbage_free(garbage);
        return 1;
    }

    CliFlag *src_flag = cli.entry.get_flag(entry,SRC_FLAG,CLI_NOT_CASE_SENSITIVE);

    //verify if exist
    if(src_flag->exist == false){
           printf(SRC_FLAG_NOT_PROVIDED);
           UniversalGarbage_free(garbage);
           return 1;
    }

    char *src = cli.flag.get_str(src_flag,0,CLI_CASE_SENSITIVE);
    if(dtw.entity_type(src) != DTW_FOLDER_TYPE){
        printf(SRC_ITS_NOT_A_DIR);
        UniversalGarbage_free(garbage);
        return 1;
    }

    CliFlag *imports_flag = cli.entry.get_flag(entry,IMPORT_FLAG,CLI_NOT_CASE_SENSITIVE);


    char *imports = NULL;
    if(imports_flag->exist){
        imports =cli.flag.get_str(imports_flag,0,CLI_CASE_SENSITIVE);
    }
    if(!imports_flag->exist){
        imports  = dtw.concat_path(src,IMPORT_NAME);
        UniversalGarbage_add_simple(garbage,imports);
    }

    CliFlag *tag_flags = cli.entry.get_flag(entry,TAG_FLAG,CLI_NOT_CASE_SENSITIVE);

    if(!tag_flags->exist){
        printf(TAG_FLAG_NOT_PROVIDED);
        UniversalGarbage_free(garbage);
        return 1;
    }

    if(tag_flags->size == 0){
        printf(AT_LEAST_ONE_TAG_ERROR);
        UniversalGarbage_free(garbage);
        return 1;
    }


    DtwStringArray *tags = newDtwStringArray();
    UniversalGarbage_add(garbage,dtw.string_array.free,tags);

    for(int i = 0; i < tag_flags->size;i++){
        char *tag = cli.flag.get_str(tag_flags,i,CLI_CASE_SENSITIVE);
        dtw.string_array.append(tags,tag);
    }

    FlagColision possible_colision = flag_collides(tags);
    if(possible_colision.collides){
        printf(FLAG_COLLIDES_ERROR,possible_colision.flag_colliding,possible_colision.flag_colliding_with);
        UniversalGarbage_free(garbage);
        return 1;
    }

    CliFlag *project_short_cut_flag = cli.entry.get_flag(entry,PROJECT_SHORT_CUT_FLAG,CLI_NOT_CASE_SENSITIVE);
    const char *project_short_cut = PROJECT_SHORT_CUT_DEFAULT;

    if(project_short_cut_flag->exist){
        project_short_cut = cli.flag.get_str(project_short_cut_flag,0,CLI_CASE_SENSITIVE);
    }
    bool implement_main = true;
    char *main_name = NULL;
    char *main_path = NULL;

    CliFlag *implement_main_flag = cli.entry.get_flag(entry,IMPLEMENT_MAIN_FLAG,CLI_NOT_CASE_SENSITIVE);
    if(implement_main_flag->exist){
        implement_main = cli.flag.get_bool(implement_main_flag,0);
    }
    CliFlag *main_name_flag = cli.entry.get_flag(entry,MAIN_NAME_FLAG,CLI_NOT_CASE_SENSITIVE);
    if(main_name_flag->exist){
        main_name = cli.flag.get_str(main_name_flag,0,CLI_CASE_SENSITIVE);
    }
    CliFlag *main_path_flag = cli.entry.get_flag(entry,MAIN_PATH_FLAG,CLI_NOT_CASE_SENSITIVE);
    if(main_path_flag->exist){
        main_path = cli.flag.get_str(main_path_flag,0,CLI_CASE_SENSITIVE);
    }

    CliFlag *watch_flag = cli.entry.get_flag(entry,WATCH_FLAG,CLI_NOT_CASE_SENSITIVE);
    if(watch_flag->exist){
            CliFlag *sleep_time_flag = cli.entry.get_flag(entry,SLEEP_TIME_FLAG,CLI_NOT_CASE_SENSITIVE);
        int sleep_time = SLEEP_TIME_DEFAULT;
        if(sleep_time_flag->exist){
            sleep_time = cli.flag.get_long(sleep_time_flag,0);
        }
        generate_code_in_watch_mode(src,imports,project_short_cut,tags,implement_main,main_name,main_path,sleep_time,WATCHING_FILES_MESSAGE,REMAKING_PROJECT_MESSAGE);
    }

    if(!watch_flag->exist){
        generate_code(src,imports,project_short_cut,tags,implement_main,main_name,main_path);
    }

    UniversalGarbage_free(garbage);

}
