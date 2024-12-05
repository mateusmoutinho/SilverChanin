
//silver_chain_scope_start
//mannaged by silver chain
#include "../../imports/imports.api_types.h"
//silver_chain_scope_end


private_SilverChain_TagList *private_SilverChain_newTagList();

private_SilverChain_Tag * private_SilverChain_TagList_find_tag_element(private_SilverChain_TagList *self,const char *tag);


int private_SilverChain_TagList_ordanate_tag_by_priority(const void *tag1,const void *tag2);

void private_SilverChain_TagList_add_item(private_SilverChain_TagList *self, const char *tag,const char *path,int priority);

void private_SilverChain_TagList_implement(private_SilverChain_TagList *self,const char *point,const char *project_short_cut);

void private_SilverChain_TagList_free(private_SilverChain_TagList *self);
