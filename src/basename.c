#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

#include "../libs/DynamicString.h"

#include "../libs/Args.h"

#define PROGRAM "basename"
#define VERSION "0.0.1"

#define PATH_SEPARATOR '/'

void DS_remove_suffix(DS* ds, const char* suffix_cstr)
{
    uint64_t suffix_len = DS_cstrlen(suffix_cstr);
    uint64_t index = DS_find_last_cstr(ds, suffix_cstr);
    if (ds->len > index + suffix_len) return; // Substring is not at the end
    ds->len -= suffix_len;
    ds->data[ds->len] = '\0';
}

void perform_basename(DS* ds)
{
    if (ds->data[ds->len - 1] == PATH_SEPARATOR) {
        ds->data[ds->len - 1] = '\0';
        ds->len--;
    }
    DS tail = DS_tail(ds, DS_find_last_ch(ds, PATH_SEPARATOR) + 1);
    DS_free(ds);
    ds->data = tail.data;
    ds->len = tail.len;
}

void print_usage()
{
    printf("Usage: "PROGRAM" [OPTIONS] NAME...\n"
    "Print NAME with any leading directory components removed.\n"
    "If specified, also remove a trailing SUFFIX.\n"
    "\n"
    "Mandatory arguments to long options are mandatory for short options too.\n"
    "  -a, --multiple       support multiple arguments and treat each as a NAME\n"
    "  -s, --suffix SUFFIX  remove a trailing SUFFIX\n"
    "  -z, --zero           end each output line with NUL, not newline\n"
    "  --help        display this help and exit\n"
    "  --version     output version information and exit\n"
    "\n"
    "Examples:\n"
    "  "PROGRAM" /usr/bin/sort          -> \"sort\"\n"
    "  "PROGRAM" include/stdio.h .h     -> \"stdio\"\n"
    "  "PROGRAM" -s .h include/stdio.h  -> \"stdio\"\n"
    "  "PROGRAM" -a any/str1 any/str2   -> \"str1\" followed by \"str2\"\n");
}

int main(int argc, char** argv)
{
    if (argc < 2) {
        print_usage();
        return 1;
    }

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
            .l = DS_from_cstr("--multiple"),
            .s = DS_from_cstr("-a"),
            .type = ARG_NONE,
            .is_set = false,
        },
        {
            .l = DS_from_cstr("--suffix"),
            .s = DS_from_cstr("-s"),
            .type = ARG_CSTR,
            .is_set = false,
        },
        {
            .l = DS_from_cstr("--zero"),
            .s = DS_from_cstr("-z"),
            .type = ARG_NONE,
            .is_set = false,
        },
    };

    Args args;
    Args_parse_args(&args, (const uint64_t) argc, (const char**) argv, program_options, 5);

    if (program_options[0].is_set) {
        print_usage();
        return 0;
    }

    if (program_options[1].is_set) {
        printf(PROGRAM" "VERSION"\n");
        return 0;
    }

    uint64_t n = args.count;
    if (!program_options[2].is_set) n = 2;

    for (uint64_t i = 1; i < n; i++) {
        perform_basename(&args.data[i]);
        if (program_options[3].is_set) {
            DS_remove_suffix(&args.data[i], program_options[3].val._cstr);
        }
        printf("%s", DS_to_cstr(&args.data[i]));
        if (!program_options[4].is_set) {
            printf("\n");
        }
    }

    return 0;
}
