

int  get_tag_index(DtwStringArray *tags,const char *name);

double get_tag_priority(DtwStringArray *tags,const char *name);

int count_path_levels(const char *path);


CTextStack * make_relative_path(
    const char *current_file,
    const char *dest_file
);


FlagColision flag_collides(DtwStringArray *flags);
