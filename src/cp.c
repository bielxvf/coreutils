#include <stdio.h>
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
        fprintf(stderr, "Error: No arguments\n");
        print_help();
        return 1;
    } break;
    case 1: {
        fprintf(stderr, "Error: Missing source and destination\n");
        print_help();
        return 1;
    } break;
    case 2: {
        fprintf(stderr, "Error: Missing destination for '%s'\n", DS_to_cstr(&args.data[1]));
        print_help();
        return 1;
    } break;
    }

    // Actual copying

    FILE* input_file = fopen(DS_to_cstr(&args.data[1]), "rb");
    fseek(input_file, 0, SEEK_END);
    size_t input_file_size = ftell(input_file);
    rewind(input_file);

    char* buffer = (char*) malloc(input_file_size + 1);
    fread(buffer, input_file_size, 1, input_file);
    fclose(input_file);

    // @NOTE: This will replace the file, we need to handle options like -i
    FILE* output_file = fopen(DS_to_cstr(&args.data[2]), "wb");
    fwrite(buffer, input_file_size, 1, output_file); 
    fclose(output_file);
    
    return 0;
}
