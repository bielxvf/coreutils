#include <stdio.h>
#include <stdlib.h>

#include "../libs/Args.h"

#define PROGRAM "cat"
#define VERSION "0.0.1"

void print_usage()
{

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
            .s = DS_from_cstr("-v"),
            .type = ARG_NONE,
            .is_set = false,
        },
        {
            .l = DS_from_cstr("--show-tabs"),
            .s = DS_from_cstr("-T"),
            .type = ARG_NONE,
            .is_set = false,
        },
        {
            .l = DS_from_cstr("--number"),
            .s = DS_from_cstr("-n"),
            .type = ARG_NONE,
            .is_set = false,
        },
        {
            .l = DS_from_cstr("--show-ends"),
            .s = DS_from_cstr("-E"),
            .type = ARG_NONE,
            .is_set = false,
        },
        {
            .l = DS_from_cstr("--squeeze-blank"),
            .s = DS_from_cstr("-s"),
            .type = ARG_NONE,
            .is_set = false,
        },
    };
    Args args;
    Args_parse_args(&args, (const uint64_t) argc, (const char**) argv, program_options, sizeof(program_options)/sizeof(program_options[0]));

    if (argc < 2) {
        // TODO: Read stdin like GNU's cat does

        return 0;
    }

    if (program_options[0].is_set) {
        print_usage();
        return 0;
    }

    if (program_options[1].is_set) {
        printf(PROGRAM" "VERSION"\n");
    }

    uint64_t n = 1;

    for (uint64_t i = 1; i < args.count; i++) {
        FILE* file = fopen(DS_to_cstr(&args.data[i]), "rb");
        fseek(file, 0, SEEK_END);
        uint64_t file_size = ftell(file);
        rewind(file);

        char* buffer = (char*) malloc(file_size + 1);
        fread(buffer, file_size, 1, file);
        fclose(file);
        buffer[file_size] = '\0';

        bool was_newline = false;
        uint64_t newline_count = 0;
        for (uint64_t j = 0; j < file_size; j++) {
            if (program_options[3].is_set && was_newline) {
                printf("%6lu  ", n);
                was_newline = false;
            }

            if (program_options[5].is_set && buffer[j] == '\n') {
                newline_count++;
                if (newline_count > 2) {
                    continue;
                }
            } else if (program_options[5].is_set) {
                newline_count = 0;
            }

            if (program_options[4].is_set && buffer[j] == '\n') {
                printf("$");
            }

            if (program_options[2].is_set && buffer[j] == '\t') {
                printf("^I");
            } else {
                printf("%c", buffer[j]);
            }

            if (program_options[3].is_set && buffer[j] == '\n') {
                n++;
                was_newline = true;
            }
        }

        free(buffer);
    }

    return 0;
}
