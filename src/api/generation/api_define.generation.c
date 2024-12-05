
//silver_chain_scope_start
//mannaged by silver chain
#include "../imports/imports.func_declaration.h"
//silver_chain_scope_end

char *get_main_path(DtwStringArray *src_listage,char *main_name){
    UniversalGarbage *garbage = newUniversalGarbage();
     DtwPath *path = NULL;
     UniversalGarbage_add(garbage,dtw.path.free,path);
    for(int i = 0; i < src_listage->size;i++){
        char *current = src_listage->strings[i];

        path = dtw.path.newPath(current);
        UniversalGarbage_resset(garbage,path);

        char *current_name = dtw.path.get_full_name(path);
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
void generate_main(
    DtwStringArray *src_listage,
    const char *import_dir,
    TagList *itens,
    char *main_name,
    const char *main_path

){
    const char *found_main_path = main_path;
    if(main_path == NULL){
        found_main_path = get_main_path(src_listage,main_name);
    }

    if(found_main_path == NULL){
        return;
    }

    UniversalGarbage *garbage = newUniversalGarbage();
    Tag *last_tag = itens->tags[itens->size - 1];
    char *prev = last_tag->name;

    CTextStack *module_path = stack.newStack_string_empty();
    UniversalGarbage_add(garbage,stack.free,module_path);

    stack.format(module_path,"%s/%s.%s.h",import_dir,IMPORT_NAME,prev);
    replace_import_file(found_main_path,module_path->rendered_text);
    UniversalGarbage_free(garbage);

}

void generate_code(
    const char *src,
    const char *import_dir,
    const char *project_short_cut,
    DtwStringArray * tags,
    bool implement_main,
    char *main_name,
    const char *main_path
    ){


    dtw.remove_any(import_dir);
    UniversalGarbage *garbage = newUniversalGarbage();
    DtwStringArray *src_listage = dtw.list_files_recursively(src,true);
    //grants previsbility
    dtw.string_array.sort(src_listage);

    UniversalGarbage_add(garbage,dtw.string_array.free,src_listage);

    DtwPath *path =NULL;
    UniversalGarbage_add(garbage,dtw.path.free,path);

    CTextStack *name_stack = NULL;
    UniversalGarbage_add(garbage,stack.free,name_stack);

    TagList *itens = newTagList();
    UniversalGarbage_add(garbage,TagList_free,itens);

    for(int i = 0; i <src_listage->size;i++){
        char *current = src_listage->strings[i];
        path = dtw.path.newPath(current);
        UniversalGarbage_resset(garbage,path);

        char *name = dtw.path.get_name(path);
        name_stack = stack.newStack_string(name);
        UniversalGarbage_resset(garbage,name_stack);

        int first_dot = stack.index_of_char(name_stack,'.');
        stack.self_substr(name_stack,0,first_dot);

        int tag_index = get_tag_index(tags,name_stack->rendered_text);
        if(tag_index != -1){
            TagList_add_item(itens,name_stack->rendered_text,current,tag_index);
        }

    }

    TagList_implement(itens,import_dir,project_short_cut);
    if(implement_main){
       generate_main(src_listage,import_dir,itens,main_name,main_path);
    }

    UniversalGarbage_free(garbage);
}

void generate_code_in_watch_mode(const char *src,const char *import_dir,const char *project_short_cut,DtwStringArray *tags,bool implement_main,char *main_name,const char *main_path,int sleep_time){
    char *first = NULL;
     printf(MAKING_PROJECT_MESSAGE);
    generate_code(src,import_dir,project_short_cut,tags,implement_main,main_name,main_path);
    printf(WATCHING_FILES_MESSAGE);
    while (true) {
        DtwHash *hash = dtw.hash.newHash();
        dtw.hash.digest_folder_by_content(hash,src);
        if(first == NULL){
            first = strdup(hash->hash);
            dtw.hash.free(hash);
            continue;
        }

        if(strcmp(hash->hash,first) != 0){
            printf(REMAKING_PROJECT_MESSAGE);
            generate_code(src,import_dir,project_short_cut,tags,implement_main,main_name,main_path);
            printf(WATCHING_FILES_MESSAGE);
            free(first);
            first = NULL;
        }
        dtw.hash.free(hash);
        if(sleep_time > 0){
            sleep(sleep_time);
        }
    }
    
    if(first != NULL){
        free(first);
    }

}
