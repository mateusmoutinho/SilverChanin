
//silver_chain_scope_start
//mannaged by silver chain
#include "../../imports/imports.cli_declare.h"
//silver_chain_scope_end

FlagColision flag_collides(SilverChainStringArray *flags_r){
    FlagColision colision = {false,NULL,NULL};
    DtwStringArray *flags = (DtwStringArray*)flags_r;
    for(int i = 0; i < flags->size; i++){
        char *current_flag = flags->strings[i];
        for(int j = 0; j < flags->size; j++){
            if(i == j){
                continue;
            }
            char *current_flag2 = flags->strings[j];
            if(dtw_starts_with(current_flag2,current_flag)){
                colision.collides = true;
                colision.flag_colliding = current_flag;
                colision.flag_colliding_with = current_flag2;
                return colision;
            }
        }
    }
    return colision;
}
