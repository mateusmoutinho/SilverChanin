
//silver_chain_scope_start
//mannaged by silver chain
#include "../../imports/imports.api_typesC.h"
//silver_chain_scope_end


int  private_SilverChain_get_tag_index(DtwStringArray *tags,const char *name);

double private_SilverChain_get_tag_priority(DtwStringArray *tags,const char *name);

int private_SilverChain_count_path_levels(const char *path);


CTextStack * private_SilverChain_make_relative_path(
    const char *current_file,
    const char *dest_file
);
