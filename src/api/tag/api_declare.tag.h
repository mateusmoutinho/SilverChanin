
//silver_chain_scope_start
//mannaged by silver chain
#include "../../imports/imports.api_typeB.h"
//silver_chain_scope_end


Tag *newTag(const char *name,int priority);


void Tag_add_file(Tag *self,const char *file);

void Tag_create_module_file(
    Tag *self,
    CTextStack *final_text_path,
    const char *prev_module,
    const char *project_short_cut
);

void replace_import_file(const char *current_file_path,const char *module_path);

void Tag_replace_import_in_files(
    Tag *self,
    const char *module_dir,
    const char *prev
);



void Tag_implement(
    Tag *self,
    const char *module_dir,
    const char *project_short_cut,
    const char *prev
);



void Tag_free(Tag *self);
