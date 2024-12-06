
//silver_chain_scope_start
//mannaged by silver chain
#include "../../imports/imports.api_declare.h"
//silver_chain_scope_end


private_SilverChain_TagList *private_SilverChain_newTagList(){
    private_SilverChain_TagList *self = (private_SilverChain_TagList*)malloc(sizeof(private_SilverChain_TagList));
    *self = (private_SilverChain_TagList){0};
    self->tags = (private_SilverChain_Tag**)malloc(0);
    return self;
}
private_SilverChain_Tag * private_SilverChain_TagList_find_tag_element(private_SilverChain_TagList *self,const char *tag){
    for(int i = 0; i < self->size;i++){
        private_SilverChain_Tag *current = self->tags[i];
        if(strcmp(current->name, tag) == 0){
            return current;
        }
    }
    return NULL;
}

void private_SilverChain_TagList_add_item(private_SilverChain_TagList *self, const char *tag,const char *path,int priority){
    private_SilverChain_Tag *tag_to_add = private_SilverChain_TagList_find_tag_element(self,tag);
    if(tag_to_add == NULL){
        tag_to_add = private_SilverChain_newTag(tag,priority);
        self->tags = (private_SilverChain_Tag**)realloc(self->tags, (self->size +1) * sizeof(private_SilverChain_Tag**));
        self->tags[self->size] = tag_to_add;
        self->size+=1;
    }
    private_SilverChain_Tag_add_file(tag_to_add,path);

}

int private_SilverChain_TagList_ordanate_tag_by_priority(const void *tag1,const void *tag2){
    private_SilverChain_Tag *t1 = *(private_SilverChain_Tag**)tag1;
    private_SilverChain_Tag *t2 = *(private_SilverChain_Tag**)tag2;
    if(t1->priority > t2->priority){
        return 1;
    }
    if(t1->priority < t2->priority){
        return -1;
    }
    //printf("%s | %s\n",t1->name,t2->name);;
    //ordenate by alphabet
    return strcmp(t1->name,t2->name);
}
SilverChainError *   private_SilverChain_TagList_implement(private_SilverChain_TagList *self,const char *point,const char *project_short_cut){


    qsort(self->tags, self->size, sizeof(private_SilverChain_Tag*), private_SilverChain_TagList_ordanate_tag_by_priority);

    for(int i = 0; i < self->size;i++){
        private_SilverChain_Tag *current = self->tags[i];
        char *prev = NULL;
        if(i > 0){
            prev = self->tags[i-1]->name;
        }

        SilverChainError * error = private_SilverChain_Tag_implement(current,point,project_short_cut,prev);
        if(error){
            return error;
        }
    }
    return NULL;
}

void private_SilverChain_TagList_free(private_SilverChain_TagList *self){
    for(int i = 0; i < self->size;i++){
        private_SilverChain_Tag *current = self->tags[i];
        private_SilverChain_Tag_free(current);
    }
    free(self->tags);
    free(self);
}
