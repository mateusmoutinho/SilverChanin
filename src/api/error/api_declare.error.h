
//silver_chain_scope_start
//mannaged by silver chain
#include "../../imports/imports.api_types.h"
//silver_chain_scope_end


SilverChainError *private_SilverChain_newSilverChainError(int error_code,const char *error_path, char *error_msg,...);

void SilverChainError_free(SilverChainError *self);
