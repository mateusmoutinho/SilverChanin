
//silver_chain_scope_start
//mannaged by silver chain
#include "../../imports/imports.api_typeB.h"
//silver_chain_scope_end


private_SilverChain_Tag *private_SilverChain_newTag(const char *name,int priority);


void private_SilverChain_Tag_add_file(private_SilverChain_Tag *self,const char *file);

void private_SilverChain_Tag_create_module_file(
    private_SilverChain_Tag *self,
    CTextStack *final_text_path,
    const char *prev_module,
    const char *project_short_cut
);

int  private_SilverChain_replace_import_file(const char *current_file_path,const char *module_path);

void private_SilverChain_Tag_replace_import_in_files(
    private_SilverChain_Tag *self,
    const char *module_dir,
    const char *prev
);



void private_SilverChain_Tag_implement(
    private_SilverChain_Tag *self,
    const char *module_dir,
    const char *project_short_cut,
    const char *prev
);



void private_SilverChain_Tag_free(private_SilverChain_Tag *self);
