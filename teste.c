

void parse_upper(char *value);

void convert_non_assci(char *value);

void format_str(char *str){
    parse_upper(str);
    convert_non_assci(str);
}
