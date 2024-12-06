
//silver_chain_scope_start
//mannaged by silver chain
#include "../../imports/imports.api_typesC.h"
//silver_chain_scope_end


SilverChainStringArray * newSilverChainStringArray();

void SilverChainStringArray_append(SilverChainStringArray *self,const char *value);

void SilverChainStringArray_free(SilverChainStringArray *self);
