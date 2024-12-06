
//silver_chain_scope_start
//mannaged by silver chain
#include "../../imports/imports.api_types.h"
//silver_chain_scope_end


char *private_SilverChain_get_main_path(DtwStringArray *src_listage,char *main_name);

SilverChainError * private_SilverChain_generate_main(
    DtwStringArray *src_listage,
    const char *import_dir,
    private_SilverChain_TagList *itens,
    char *main_name,
    const char *main_path

);


SilverChainError * SilverChain_generate_code(
    const char *src,
    const char *import_dir,
    const char *project_short_cut,
    SilverChainStringArray * tags,
    bool implement_main,
    char *main_name,
    const char *main_path
    );

void SilverChain_generate_code_in_watch_mode(
        const char *src,
        const char *import_dir,
        const char *project_short_cut,
        SilverChainStringArray *tags,
        bool implement_main,
        char *main_name,
        const char *main_path,
        int sleep_time
);
