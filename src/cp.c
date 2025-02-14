#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdint.h>

#include "../libs/Args.h"

#define PROGRAM "cp"
#define VERSION "0.0.1"

void print_help()
{
    assert(false && "print_help not implemented");
}

int main(int argc, char** argv)
{
    Option program_options[] =
    {
        {
            .l = DS_from_cstr("--help"),
            .s = DS_from_cstr("-h"),
            .type = ARG_NONE,
            .is_set = false,
        },
        {
            .l = DS_from_cstr("--version"),
            .s = DS_from_cstr(""),
            .type = ARG_NONE,
            .is_set = false,
        },
        {
            .l = DS_from_cstr("--recursive"),
            .s = DS_from_cstr("-r"),
            .type = ARG_NONE,
            .is_set = false,
        },
        {
            .l = DS_from_cstr("--interactive"),
            .s = DS_from_cstr("-i"),
            .type = ARG_NONE,
            .is_set = false,
        },
    };

    Args args;
    Args_parse_args(&args, (const uint64_t) argc, (const char**) argv, program_options, sizeof(program_options)/sizeof(program_options[0]));

    if (program_options[0].is_set) {
        assert(false && "Help not implemented");
        return 0;
    }

    if (program_options[1].is_set) {
        assert(false && "Version not implemented");
        return 0;
    }

    switch(args.count) {
    case 0: {
        fprintf(stderr, PROGRAM": No arguments\n");
        print_help();
        return 1;
    } break;
    case 1: {
        fprintf(stderr, PROGRAM": Missing source and destination\n");
        print_help();
        return 1;
    } break;
    case 2: {
        fprintf(stderr, PROGRAM": Missing destination for '%s'\n", DS_to_cstr(&args.data[1]));
        print_help();
        return 1;
    } break;
    }

    struct stat path_stat;
    stat(DS_to_cstr(&args.data[args.count - 1]), &path_stat);
    if (S_ISDIR(path_stat.st_mode)) {
        // @TODO
        // copy everything from args.data[1] to args.data[args.count - 2] to
        // directory args.data[args.count - 1]
        return 0;
    }

    if (program_options[3].is_set) {
        struct stat out_stat;
        stat(DS_to_cstr(&args.data[args.count - 1], &out_stat);
        if (S_ISREG(out_stat.st_mode)) {
            // @TODO
            // Check file exists
            // Prompt the user accordingly
            return 0;
        } else if (S_ISDIR(out_stat.st_mode)) {
            // @TODO
            // Check file exists in the dir
            // Prompt the user accordingly
            return 0;
        } else {
            fptintf(stderr, PROGRAM": Destination appears not to be a regular file or directory\n");
            return 1;
        }
    }

    FILE* input_file = fopen(DS_to_cstr(&args.data[1]), "rb");
    fseek(input_file, 0, SEEK_END);
    size_t input_file_size = ftell(input_file);
    rewind(input_file);

    char* buffer = (char*) malloc(input_file_size + 1);
    fread(buffer, input_file_size, 1, input_file);
    fclose(input_file);

    FILE* output_file = fopen(DS_to_cstr(&args.data[2]), "wb");
    fwrite(buffer, input_file_size, 1, output_file); 
    fclose(output_file);
    
    return 0;
}
