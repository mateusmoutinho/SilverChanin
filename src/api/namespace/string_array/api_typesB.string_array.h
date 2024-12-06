
//silver_chain_scope_start
//mannaged by silver chain
#include "../../../imports/imports.api_types.h"
//silver_chain_scope_end

typedef struct SilverChainStringArrayNamespace{
    SilverChainStringArray * (*create)();
    void (*append)(SilverChainStringArray *self,const char *value);
    void (*free)(SilverChainStringArray *self);

} SilverChainStringArrayNamespace;
