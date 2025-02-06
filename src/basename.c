#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

#include "../libs/DynamicString.h"

#define PROGRAM "basename"
#define VERSION "0.0.1"

typedef _Float64 float64_t;

typedef enum
{
    ARG_NONE,
    ARG_INT64,
    ARG_UINT64,
    ARG_F64,
    ARG_CSTR,
} Type;

typedef union
{
    int64_t _int64;
    uint64_t _uint64;
    const char* _cstr;
    float64_t _float64;
} Value;

typedef struct
{
    DS l;
    DS s;
    Type type;
    Value val;
    bool is_set;
} Option;

typedef struct
{
    DS* data;
    uint64_t count;
} Args;

void Args_remove(Args* args, uint64_t index)
{
    DS_free(args->data + index);
    for (uint64_t i = index; i < args->count; i++) {
        if (i + 1 >= args->count) break;

        args->data[i] = args->data[i + 1];
    }
    args->count--;
}

void Args_parse_args(Args* args, const uint64_t argc, const char** argv, Option options[], uint64_t opt_count)
{
    args->count = (uint64_t) argc;
    args->data = malloc(sizeof(args->data[0]) * args->count);
    for (uint64_t i = 0; i < args->count; i++) {
        args->data[i] = DS_from_cstr(argv[i]);
    }

    for (uint64_t i = 0; i < opt_count; i++) {
        for (uint64_t j = 1; j < args->count; j++) {
            if (DS_eq_ds(&args->data[j], &options[i].l) || DS_eq_ds(&args->data[j], &options[i].s)) {
                options[i].is_set = true;
                if (options[i].type != ARG_NONE && j + 1 >= args->count) {
                    Args_remove(args, j);
                    return;
                }

                switch (options[i].type) {
                case ARG_INT64: {
                    options[i].val._int64 = DS_to_i64(&args->data[j + 1]);
                    Args_remove(args, j + 1);
                } break;
                case ARG_UINT64: {
                    options[i].val._uint64 = DS_to_u64(&args->data[j + 1]);
                    Args_remove(args, j + 1);
                } break;
                case ARG_F64: {
                    options[i].val._float64 = DS_to_f64(&args->data[j + 1]);
                    Args_remove(args, j + 1);
                } break;
                case ARG_CSTR: {
                    options[i].val._cstr = DS_to_cstr(&args->data[j + 1]);
                    Args_remove(args, j + 1);
                } break;
                default: {
                    // ARG_NONE
                } break;
                }
                Args_remove(args, j);
            }
        }
    }
}

int main(int argc, char** argv)
{
    if (argc < 2) {
        fprintf(stderr, PROGRAM": missing operand\n"
                        "Try `"PROGRAM" --help`\n");
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
            .l = DS_from_cstr("--sufix"),
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
        return 1;
    }

    if (program_options[1].is_set) {
        printf(PROGRAM" "VERSION"\n");
        return 0;
    }

    if (program_options[2].is_set) {
        for (uint64_t i = 1; i < args.count; i++) {
            if (args.data[i].data[args.data[i].len - 1] == '/') {
                args.data[i].data[args.data[i].len - 1] = '\0';
                args.data[i].len--;
            }
            DS tail = DS_tail(&args.data[i], DS_find_last_ch(&args.data[i], '/') + 1);
            printf("%s", DS_to_cstr(&tail));
            if (!program_options[4].is_set) {
                printf("\n");
            }
        }
    } else {
        if (args.data[1].data[args.data[1].len - 1] == '/') {
            args.data[1].data[args.data[1].len - 1] = '\0';
            args.data[1].len--;
        }
        DS tail = DS_tail(&args.data[1], DS_find_last_ch(&args.data[1], '/') + 1);
        printf("%s", DS_to_cstr(&tail));
        if (!program_options[4].is_set) {
            printf("\n");
        }
    }

    return 0;
}
