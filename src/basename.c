#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

#include "../libs/DynamicString.h"

#define PROGRAM "basename"

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
    memmove(args->data + index, args->data + index + 1, args->count - index - 1);
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
        for (uint64_t j = 0 ; j < args->count; j++) {
            if (DS_compare_ds(&args->data[j], &options[i].l) || DS_compare_ds(&args->data[j], &options[i].s)) {
                options[i].is_set = true;
                if (options[i].type != ARG_NONE && j + 1 >= args->count) return; // Ignore if flag needs argument and we dont have it

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
        fprintf(stderr, PROGRAM": missing operand\n");
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
    };
    Args args;
    Args_parse_args(&args, (const uint64_t) argc, (const char**) argv, program_options, 2);

    if (program_options[0].is_set) {
        printf("Help was called\n");
        return 1;
    }

    return 0;
    // DS args[argc];
    // for (uint64_t i = 0; i < (uint64_t) argc; i++) {
    //     args[i] = DS_from_cstr(argv[i]);
    // }
    // TODO FIX: basename "/etc/portage/" should return "portage", not an empty string
    // for (uint64_t i = 1; i < (uint64_t) argc; i++) {
    //     DS tail = DS_tail(&args[i], DS_find_last_ch(&args[i], '/') + 1);
    //     printf("%s\n", DS_as_cstr(&tail));
    // }
    // return 0;
}
