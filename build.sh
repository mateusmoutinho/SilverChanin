#./silverchain.out -src src \
#-tags dependencies consts types globals func_declaration func_definition

gcc src/main.c -o silverchain.out
./silverchain.out -src src \
-tags dependencies consts types globals func_declaration func_definition