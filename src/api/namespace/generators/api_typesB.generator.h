
//silver_chain_scope_start
//mannaged by silver chain
#include "../../../imports/imports.api_types.h"
//silver_chain_scope_end

typedef struct SilverChainGeneratorNamespace{

    SilverChainError * (*generate_code)(
        const char *src,
        const char *import_dir,
        const char *project_short_cut,
        SilverChainStringArray * tags,
        bool implement_main,
        char *main_name,
        const char *main_path
        );

    void (*generate_code_in_watch_mode)(
            const char *src,
            const char *import_dir,
            const char *project_short_cut,
            SilverChainStringArray *tags,
            bool implement_main,
            char *main_name,
            const char *main_path,
            int sleep_time
    );

} SilverChainGeneratorNamespace;
