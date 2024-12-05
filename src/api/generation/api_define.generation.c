
//silver_chain_scope_start
//mannaged by silver chain
#include "../../imports/imports.api_declare.h"
//silver_chain_scope_end

char *get_main_path(DtwStringArray *src_listage,char *main_name){
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

    CTextStack *module_path = newCTextStack_string_empty();
    UniversalGarbage_add(garbage,CTextStack_free,module_path);

    CTextStack_format(module_path,"%s/%s.%s.h",import_dir,IMPORT_NAME,prev);
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


    dtw_remove_any(import_dir);
    UniversalGarbage *garbage = newUniversalGarbage();
    DtwStringArray *src_listage = dtw_list_files_recursively(src,true);
    //grants previsbility
    DtwStringArray_sort(src_listage);

    UniversalGarbage_add(garbage,DtwStringArray_free,src_listage);

    DtwPath *path =NULL;
    UniversalGarbage_add(garbage,DtwPath_free,path);

    CTextStack *name_stack = NULL;
    UniversalGarbage_add(garbage,CTextStack_free,name_stack);

    TagList *itens = newTagList();
    UniversalGarbage_add(garbage,TagList_free,itens);

    for(int i = 0; i <src_listage->size;i++){
        char *current = src_listage->strings[i];
        path = newDtwPath(current);
        UniversalGarbage_resset(garbage,path);

        char *name = DtwPath_get_name(path);
        name_stack = newCTextStack_string(name);
        UniversalGarbage_resset(garbage,name_stack);

        int first_dot = CTextStack_index_of_char(name_stack,'.');
        CTextStack_self_substr(name_stack,0,first_dot);

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


void generate_code_in_watch_mode(
    const char *src,
    const char *import_dir,
    const char *project_short_cut,
    DtwStringArray *tags,
    bool implement_main,
    char *main_name,
    const char *main_path,
    int sleep_time,
    const char *whatch_message,
    const char *remaking_message,

){
    char *first = NULL;
    generate_code(src,import_dir,project_short_cut,tags,implement_main,main_name,main_path);
    if(whatch_message){
        printf("%s\n",whatch_message);
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
            if(remaking_message){
                printf("%s\n",remaking_message);
            }

            generate_code(src,import_dir,project_short_cut,tags,implement_main,main_name,main_path);
            if(whatch_message){
                printf("%s\n",whatch_message);
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
