
//silver_chain_scope_start
//mannaged by silver chain
#include "../../../imports/imports.api_declare.h"
//silver_chain_scope_end

SilverChainStringArrayNamespace newSilverChainStringArrayNamespace(){
    SilverChainStringArrayNamespace self = {0};
    self.create  = newSilverChainStringArray;
    self.append = SilverChainStringArray_append;
    self.free =SilverChainStringArray_free;
    return  self;
}
