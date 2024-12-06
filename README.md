
## SilverChain a Universal Import Model for C

SilverChain is a unified import model for C, it allows you to import modules and use their functions and variables in a more organized and efficient way.

[video explanation](https://www.youtube.com/watch?v=mU4QbZATKfo)

## Build
for building the project you can just type the following command (note that you must have a gcc compiler for it)
```bash
curl -L https://github.com/OUIsolutions/SilverChain/releases/download/v0.07/SilverChain.c -o SilverChain.c &&
gcc SilverChain.c -o SilverChain.o
```




##  Usage
this will generate a folder called "imports" with all the imports and their dependencies, and a main.c file with the main function and the imports.

```bash
./SilverChain.o -src <src_folder> -tags <tag1> <tag2> <tag3> ... <tagN>
```

## Flags

| Flag | Description | Default |
|------|-------------|---------|
| -s, --src | The project folder (required) | - |
| -i, --importdir | The directory to be used for saving imports | imports |
| -t, --tags | The tags to be used (required) | - |
| -p, --project_short_cut | The project shortcut to be used in #ifndef properties | silverchain |
| -m, --implement_main | true or false to implement the main function | false |
| -n, --main_name | The name of the main function | main.c or main.cpp |
| -p, --main_path | The path of the main function | undefined |
| -h, --help | Shows the help message | - |
| -w, --watch | Watch the project files and rebuild if they change | - |
| -s, --sleep_time | The time to sleep between each check (default: 0) | - |

## How it works
basicly it makes a imports dir , giving visualization of the project modules tag after tag, lets pick the self project build comand:


```bash
./silverchain.out -src src -tags dependencies consts types globals func_declaration func_definition
```
the first tag its "dependencies" so all the files that starts with "dependencies." will be imported, after that it will see that the next tag its "consts" so all the files that starts with "consts." will be imported, and so on, the same proccess will ocurry for the types, globals, func_declaration and func_definition tags, but in this case the files need to starts with the same name of the tag but in lowercase
### The Tags Vision
each tag can visualize the all the ancestors tags, for example:

```bash
./SilverChain.o -src src -tags dependencies consts types globals func_declaration func_definition
```

in this case the "func_declaration" and "func_definition" tags will see the "dependencies" and "consts" .
