
//silver_chain_scope_start
//mannaged by silver chain
#include "../../../imports/imports.api_declare.h"
//silver_chain_scope_end

SilverChainErrorNamespace newSilverChainErrorNamespace(){
    SilverChainErrorNamespace self ={0};
    self.free = SilverChainError_free;
    return self;
}
