
//silver_chain_scope_start
//mannaged by silver chain
#include "../../imports/imports.api_types.h"
//silver_chain_scope_end

typedef  struct StringArray SilverChainStringArray ;

SilverChainStringArray * newSilverChainStringArray();

void SilverChainStringArray_append(SilverChainStringArray *self,const char *value);

void SilverChainStringArray_free(SilverChainStringArray *self);
