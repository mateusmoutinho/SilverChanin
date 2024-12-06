
//silver_chain_scope_start
//mannaged by silver chain
#include "../../imports/imports.api_declare.h"
//silver_chain_scope_end


SilverChainError *private_SilverChain_newSilverChainError(int error_code,const char *error_path, char *error_msg,...){
    SilverChainError *self = (SilverChainError*)malloc(sizeof(SilverChainError));
    *self = (SilverChainError){0};
    self->error_code = error_code;
    va_list args;
    va_start(args, error_msg);
    self->error_msg = private_dtw_format_vaarg(error_msg,args);
    va_end(args);

    if(error_path){
        self->error_path = strdup(error_path);
    }
    return self;
}

void SilverChainError_free(SilverChainError *self){
    free(self->error_msg);
    if(self->error_path){
        free(self->error_path);
    }
    free(self);
}
