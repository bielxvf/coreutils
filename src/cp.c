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

    return 0;
}
