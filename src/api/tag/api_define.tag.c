
//silver_chain_scope_start
//mannaged by silver chain
#include "../../imports/imports.api_declare.h"
//silver_chain_scope_end

private_SilverChain_Tag *private_SilverChain_newTag(const char *name,int priority){
    private_SilverChain_Tag *self = (private_SilverChain_Tag*)malloc(sizeof(private_SilverChain_Tag));
    *self = (private_SilverChain_Tag){0};
    self->name = strdup(name);
    self->priority = priority;
    self->itens = newDtwStringArray();
    return self;
}

void private_SilverChain_Tag_add_file(private_SilverChain_Tag *self,const char *file){
    DtwStringArray_append(self->itens,file);
}

void private_SilverChain_Tag_create_module_file(
    private_SilverChain_Tag *self,
    CTextStack *final_text_path,
    const char *prev_module,
    const char *project_short_cut
){

    UniversalGarbage *garbage = newUniversalGarbage();
    CTextStack *final_text = newCTextStack_string_empty();
    UniversalGarbage_add(garbage,CTextStack_free,final_text);

    if(prev_module != NULL){
            CTextStack_format(final_text,"#include \"%s.%s.h\"\n",IMPORT_NAME, prev_module);
    }


    CTextStack_format(final_text,"#ifndef %s_%s\n",project_short_cut,self->name);
    CTextStack_format(final_text,"#define %s_%s\n",project_short_cut,self->name);

   CTextStack *relative_path = NULL;
   UniversalGarbage_add(garbage,CTextStack_free,relative_path);
    for(int i = 0; i < self->itens->size;i++){
        char *current_file = self->itens->strings[i];
        relative_path = private_SilverChain_make_relative_path(final_text_path->rendered_text,current_file);
        UniversalGarbage_resset(garbage,relative_path);
        CTextStack_format(final_text,"#include \"%t\"\n",relative_path);

    }

    CTextStack_format(final_text,"#endif\n");


    private_SilverChain_write_element_if_not_equal(final_text_path->rendered_text,final_text->rendered_text);
    UniversalGarbage_free(garbage);

}
SilverChainError *   private_SilverChain_replace_import_file(const char *current_file_path,const char *module_path){
    UniversalGarbage *garbage = newUniversalGarbage();
    int end_scope_size = (int)strlen(SILVER_CHAIN_END_SCOPE);
    CTextStack *relative_path = private_SilverChain_make_relative_path(current_file_path,module_path);
    UniversalGarbage_add(garbage,CTextStack_free,relative_path);

    CTextStack *text_to_insert = newCTextStack_string(SILVER_CHAIN_START_SCOPE);
    UniversalGarbage_add(garbage,CTextStack_free,text_to_insert);
    CTextStack_format(text_to_insert,"%s",MANAGED_SYSTEM);
    CTextStack_format(text_to_insert,"#include \"%t\"\n",relative_path);
    CTextStack_text(text_to_insert,SILVER_CHAIN_END_SCOPE);


    char *file_content = dtw_load_string_file_content(current_file_path);
    UniversalGarbage_add_simple(garbage,file_content);

    CTextStack *file_content_stack =newCTextStack_string(file_content);
    UniversalGarbage_add(garbage,CTextStack_free,file_content_stack);

    int start_scope_index = CTextStack_index_of(file_content_stack,SILVER_CHAIN_START_SCOPE);

    if(start_scope_index == SILVER_CHAIN_NOT_FOUND){
        CTextStack_self_insert_at(file_content_stack,0,text_to_insert->rendered_text);
        private_SilverChain_write_element_if_not_equal(current_file_path,file_content_stack->rendered_text);
        UniversalGarbage_free(garbage);
        return NULL;
    }

    int end_scope_index = CTextStack_index_of(file_content_stack,SILVER_CHAIN_END_SCOPE);
    if(end_scope_index == -1){
        UniversalGarbage_free(garbage);
        return private_SilverChain_newSilverChainError(
            SILVER_CHAIN_END_SCOPE_NOT_PROVIDED,
            current_file_path,
            SILVER_CHAIN_FILE_NOT_PROVIDED_ERROR_MESSAGE,
            current_file_path
        );
    }

    //replace the content
    CTextStack_self_pop(file_content_stack,start_scope_index,end_scope_index+end_scope_size-1);
    CTextStack_self_insert_at(file_content_stack,start_scope_index,text_to_insert->rendered_text);
    private_SilverChain_write_element_if_not_equal(current_file_path,file_content_stack->rendered_text);
    UniversalGarbage_free(garbage);
    return NULL;
}


 SilverChainError * private_SilverChain_Tag_replace_import_in_files(
    private_SilverChain_Tag *self,
    const char *module_dir,
    const char *prev
){
    if(prev == NULL){
        return NULL;
    }
    UniversalGarbage *garbage = newUniversalGarbage();
    CTextStack *module_path = newCTextStack_string_empty();
    UniversalGarbage_add(garbage,CTextStack_free,module_path);

    CTextStack_format(module_path,"%s/%s.%s.h",module_dir,IMPORT_NAME,prev);
    for(int i = 0; i < self->itens->size;i++){
        char *current_file_path = self->itens->strings[i];
        SilverChainError *error =  private_SilverChain_replace_import_file(current_file_path,module_path->rendered_text);
        if(error){
            UniversalGarbage_free(garbage);
            return error;
        }
    }
    UniversalGarbage_free(garbage);
    return NULL;
}


SilverChainError *  private_SilverChain_Tag_implement(
    private_SilverChain_Tag *self,
    const char *module_dir,
    const char *project_short_cut,
    const char *prev
){
    UniversalGarbage *garbage = newUniversalGarbage();
    CTextStack *import_module_file_path = newCTextStack_string_empty();
    UniversalGarbage_add(garbage,CTextStack_free,import_module_file_path);
    CTextStack_format(import_module_file_path,"%s/%s.%s.h",module_dir,IMPORT_NAME,self->name);

    private_SilverChain_Tag_create_module_file(self,import_module_file_path,prev,project_short_cut);
    SilverChainError *  error =  private_SilverChain_Tag_replace_import_in_files(self,module_dir,prev);
    UniversalGarbage_free(garbage);
    return error;
}


void private_SilverChain_Tag_free(private_SilverChain_Tag *self){
    free(self->name);
    DtwStringArray_free(self->itens);
    free(self);
}
