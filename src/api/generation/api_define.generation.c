
//silver_chain_scope_start
//mannaged by silver chain
#include "../../imports/imports.api_declare.h"
//silver_chain_scope_end

char *private_SilverChain_get_main_path(DtwStringArray *src_listage,const char *main_name){
    UniversalGarbage *garbage = newUniversalGarbage();
     DtwPath *path = NULL;
     UniversalGarbage_add(garbage,DtwPath_free,path);
    for(int i = 0; i < src_listage->size;i++){
        char *current = src_listage->strings[i];

        path = newDtwPath(current);
        UniversalGarbage_resset(garbage,path);

        char *current_name = DtwPath_get_full_name(path);
        if(main_name != NULL){
            if(strcmp(current_name,main_name) == 0){
                UniversalGarbage_free(garbage);
                return current;
            }
        }
        if(main_name == NULL){
            if(strcmp(current_name,DEFAULT_MAIN_C_NAME) == 0){
                UniversalGarbage_free(garbage);
                return current;
            }
            if(strcmp(current_name,DEFAULT_MAIN_CPP_NAME) == 0){
                UniversalGarbage_free(garbage);
                return current;
            }
        }
    }
    UniversalGarbage_free(garbage);
    return NULL;
}
SilverChainError * private_SilverChain_generate_main(
    DtwStringArray *src_listage,
    const char *import_dir,
    private_SilverChain_TagList *itens,
   const  char *main_name,
    const char *main_path

){
    const char *found_main_path = main_path;
    if(main_path == NULL){
        found_main_path = private_SilverChain_get_main_path(src_listage,main_name);
    }

    if(found_main_path == NULL){
        return NULL;
    }

    UniversalGarbage *garbage = newUniversalGarbage();
    private_SilverChain_Tag *last_tag = itens->tags[itens->size - 1];
    char *prev = last_tag->name;

    CTextStack *module_path = newCTextStack_string_empty();
    UniversalGarbage_add(garbage,CTextStack_free,module_path);

    CTextStack_format(module_path,"%s/%s.%s.h",import_dir,IMPORT_NAME,prev);
    SilverChainError *error = private_SilverChain_replace_import_file(found_main_path,module_path->rendered_text);
    UniversalGarbage_free(garbage);
    return error;
}

SilverChainError * SilverChain_generate_code(
    const char *src,
    const char *import_dir,
    const char *project_short_cut,
    SilverChainStringArray * tags,
    bool implement_main,
    const char *main_name,
    const char *main_path
    ){

    if(dtw_entity_type(src) != DTW_FOLDER_TYPE){
        return private_SilverChain_newSilverChainError(SILVER_CHAIN_SRC_NOT_A_DIR,NULL,SILVER_CHAIN_SRC_NOT_A_DIR_MESSAGE,src);
    }


    UniversalGarbage *garbage = newUniversalGarbage();
    DtwStringArray *src_listage = dtw_list_files_recursively(src,true);
    //grants previsbility
    DtwStringArray_sort(src_listage);

    UniversalGarbage_add(garbage,DtwStringArray_free,src_listage);

    DtwPath *path =NULL;
    UniversalGarbage_add(garbage,DtwPath_free,path);

    CTextStack *name_stack = NULL;
    UniversalGarbage_add(garbage,CTextStack_free,name_stack);

    private_SilverChain_TagList *itens = private_SilverChain_newTagList();
    UniversalGarbage_add(garbage,private_SilverChain_TagList_free,itens);

    for(int i = 0; i <src_listage->size;i++){
        char *current = src_listage->strings[i];
        path = newDtwPath(current);
        UniversalGarbage_resset(garbage,path);

        char *name = DtwPath_get_name(path);
        name_stack = newCTextStack_string(name);
        UniversalGarbage_resset(garbage,name_stack);

        int first_dot = CTextStack_index_of_char(name_stack,'.');
        CTextStack_self_substr(name_stack,0,first_dot);

        int tag_index = private_SilverChain_get_tag_index((DtwStringArray*)tags,name_stack->rendered_text);
        if(tag_index != SILVER_CHAIN_NOT_FOUND){
            private_SilverChain_TagList_add_item(itens,name_stack->rendered_text,current,tag_index);
        }

    }

    SilverChainError *error =  private_SilverChain_TagList_implement(itens,import_dir,project_short_cut);
    if(error){
        UniversalGarbage_free(garbage);
        return error;
    }
    if(implement_main){
      error =  private_SilverChain_generate_main(src_listage,import_dir,itens,main_name,main_path);
    }




    DtwStringArray * import_files = dtw_list_files_recursively(import_dir, DTW_CONCAT_PATH);
    UniversalGarbage_add(garbage, DtwStringArray_free, import_files);

    for(int i = 0; i < import_files->size;i++){
        UniversalGarbage *internal_garbage = newUniversalGarbage();
        char *current_file = import_files->strings[i];
        DtwPath *current_path = newDtwPath(current_file);
        UniversalGarbage_add(internal_garbage, DtwPath_free, current_path);

        char *full_name = DtwPath_get_full_name(current_path);

        if(!dtw_starts_with(full_name, "imports.")){
            dtw_remove_any(current_file);
            UniversalGarbage_free(internal_garbage);
            continue;
        }
        CTextArray * itens = CTextArray_split(full_name,".");
        UniversalGarbage_add(internal_garbage, CTextArray_free, itens);
        if(itens->size != 3){
            dtw_remove_any(current_file);
            UniversalGarbage_free(internal_garbage);
            continue;
        }

        bool tag_valid = private_SilverChain_get_tag_index(tags,itens->stacks[1]->rendered_text) != -1;
        if(!tag_valid){
            dtw_remove_any(current_file);
        }
        UniversalGarbage_free(internal_garbage);
    }



    UniversalGarbage_free(garbage);
    return error;
}


void  SilverChain_generate_code_in_watch_mode(
    const char *src,
    const char *import_dir,
    const char *project_short_cut,
    SilverChainStringArray *tags,
    bool implement_main,
    const char *main_name,
    const char *main_path,
    int sleep_time

){
    char *first = NULL;
    SilverChain_generate_code(src,import_dir,project_short_cut,tags,implement_main,main_name,main_path);
    if(SILVER_CHAIN_WATCHING_FILES_MESSAGE){
        printf("%s\n",SILVER_CHAIN_WATCHING_FILES_MESSAGE);
    }

    while (true) {
        DtwHash *hash =newDtwHash();
        DtwHash_digest_folder_by_content(hash,src);
        if(first == NULL){
            first = strdup(hash->hash);
            DtwHash_free(hash);
            continue;
        }

        if(strcmp(hash->hash,first) != 0){
            if(SILVER_CHAIN_REMAKING_PROJECT_MESSAGE){
                printf("%s\n",SILVER_CHAIN_REMAKING_PROJECT_MESSAGE);
            }

            SilverChainError * error =  SilverChain_generate_code(src,import_dir,project_short_cut,tags,implement_main,main_name,main_path);
            if(error){
                printf("%s\n",error->error_msg);
                SilverChainError_free(error);
                continue;
            }
            if(SILVER_CHAIN_WATCHING_FILES_MESSAGE){
                printf("%s\n",SILVER_CHAIN_WATCHING_FILES_MESSAGE);
            }

            free(first);
            first = NULL;
        }
        DtwHash_free(hash);
        if(sleep_time > 0){
            sleep(sleep_time);
        }
    }

    if(first != NULL){
        free(first);
    }

}
