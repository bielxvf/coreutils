#ifndef ARGS_H
#define ARGS_H

#include <stdint.h>
#include <stdbool.h>

#include "../libs/DynamicString.h"

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
    char* _cstr;
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
            if (DS_eq_cstr(&args->data[j], "--")) {
                i = opt_count;
                j = args->count;
            }

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
                    options[i].val._cstr = malloc(args->data[j + 1].len + 1);
                    for (uint64_t k = 0; k < args->data[j + 1].len + 1; k++) {
                        options[i].val._cstr[k] = args->data[j + 1].data[k];
                    }
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

#endif // ARGS_H
