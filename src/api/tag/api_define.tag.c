
//silver_chain_scope_start
//mannaged by silver chain
#include "../../imports/imports.api_declare.h"
//silver_chain_scope_end

Tag *newTag(const char *name,int priority){
    Tag *self = (Tag*)malloc(sizeof(Tag));
    *self = (Tag){0};
    self->name = strdup(name);
    self->priority = priority;
    self->itens = newDtwStringArray();
    return self;
}

void Tag_add_file(Tag *self,const char *file){
    DtwStringArray_append(self->itens,file);
}

void Tag_create_module_file(
    Tag *self,
    CTextStack *final_text_path,
    const char *prev_module,
    const char *project_short_cut
){

    UniversalGarbage *garbage = newUniversalGarbage();
    CTextStack *final_text = stack.newStack_string_empty();
    UniversalGarbage_add(garbage,stack.free,final_text);

    if(prev_module != NULL){
            stack.format(final_text,"#include \"%s.%s.h\"\n",IMPORT_NAME, prev_module);
    }


    stack.format(final_text,"#ifndef %s_%s\n",project_short_cut,self->name);
    stack.format(final_text,"#define %s_%s\n",project_short_cut,self->name);

   CTextStack *relative_path = NULL;
   UniversalGarbage_add(garbage,stack.free,relative_path);
    for(int i = 0; i < self->itens->size;i++){
        char *current_file = self->itens->strings[i];
        relative_path = make_relative_path(final_text_path->rendered_text,current_file);
        UniversalGarbage_resset(garbage,relative_path);
        stack.format(final_text,"#include \"%t\"\n",relative_path);

    }

    stack.format(final_text,"#endif\n");


    write_element_if_not_equal(final_text_path->rendered_text,final_text->rendered_text);
    UniversalGarbage_free(garbage);

}
void replace_import_file(const char *current_file_path,const char *module_path){
    UniversalGarbage *garbage = newUniversalGarbage();
    int end_scope_size = (int)strlen(SILVER_CHAIN_END_SCOPE);
    CTextStack *relative_path = make_relative_path(current_file_path,module_path);
    UniversalGarbage_add(garbage,stack.free,relative_path);

    CTextStack *text_to_insert = stack.newStack_string(SILVER_CHAIN_START_SCOPE);
    UniversalGarbage_add(garbage,stack.free,text_to_insert);
    stack.format(text_to_insert,"%s",MANAGED_SYSTEM);
    stack.format(text_to_insert,"#include \"%t\"\n",relative_path);
    stack.text(text_to_insert,SILVER_CHAIN_END_SCOPE);


    char *file_content = dtw.load_string_file_content(current_file_path);
    UniversalGarbage_add_simple(garbage,file_content);

    CTextStack *file_content_stack = stack.newStack_string(file_content);
    UniversalGarbage_add(garbage,stack.free,file_content_stack);

    int start_scope_index = stack.index_of(file_content_stack,SILVER_CHAIN_START_SCOPE);
    if(start_scope_index == -1){
        //means its not implemented
        stack.self_insert_at(file_content_stack,0,text_to_insert->rendered_text);
        write_element_if_not_equal(current_file_path,file_content_stack->rendered_text);
        UniversalGarbage_free(garbage);
        return;;
    }

    int end_scope_index = stack.index_of(file_content_stack,SILVER_CHAIN_END_SCOPE);
    if(end_scope_index == -1){
        printf(FILE_NOT_PROVIDED_ERROR,current_file_path);
        UniversalGarbage_free(garbage);
        return;;
    }

    //replace the content
    stack.self_pop(file_content_stack,start_scope_index,end_scope_index+end_scope_size-1);
    stack.self_insert_at(file_content_stack,start_scope_index,text_to_insert->rendered_text);
    write_element_if_not_equal(current_file_path,file_content_stack->rendered_text);
    UniversalGarbage_free(garbage);
}


void Tag_replace_import_in_files(
    Tag *self,
    const char *module_dir,
    const char *prev
){
    if(prev == NULL){
        return;
    }
    UniversalGarbage *garbage = newUniversalGarbage();
    CTextStack *module_path = stack.newStack_string_empty();
    UniversalGarbage_add(garbage,stack.free,module_path);

    stack.format(module_path,"%s/%s.%s.h",module_dir,IMPORT_NAME,prev);
    for(int i = 0; i < self->itens->size;i++){
        char *current_file_path = self->itens->strings[i];
        replace_import_file(current_file_path,module_path->rendered_text);
    }
    UniversalGarbage_free(garbage);
}


void Tag_implement(
    Tag *self,
    const char *module_dir,
    const char *project_short_cut,
    const char *prev
){
    UniversalGarbage *garbage = newUniversalGarbage();
    CTextStack *import_module_file_path = stack.newStack_string_empty();
    UniversalGarbage_add(garbage,stack.free,import_module_file_path);
    stack.format(import_module_file_path,"%s/%s.%s.h",module_dir,IMPORT_NAME,self->name);

    Tag_create_module_file(self,import_module_file_path,prev,project_short_cut);
    Tag_replace_import_in_files(self,module_dir,prev);
    UniversalGarbage_free(garbage);
}


void Tag_free(Tag *self){
    free(self->name);
    DtwStringArray_free(self->itens);
    free(self);
}
