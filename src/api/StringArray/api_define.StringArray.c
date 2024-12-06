
//silver_chain_scope_start
//mannaged by silver chain
#include "../../imports/imports.api_declare.h"
//silver_chain_scope_end

SilverChainStringArray * newSilverChainStringArray(){
    return newDtwStringArray();
}
void SilverChainStringArray_append(SilverChainStringArray *self,const char *value){
    DtwStringArray_append(self,value);
}

void SilverChainStringArray_free(SilverChainStringArray *self){
    DtwStringArray_free(self);
}
