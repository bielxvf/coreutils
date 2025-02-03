#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

#include "../libs/DynamicString.h"

#define UNUSED(x) do { (void) x; } while(false)

int main(int argc, char** argv)
{
    DS args[argc];
    for (uint64_t i = 0; i < (uint64_t) argc; i++) {
        args[i] = DS_from_cstr(argv[i]);
    }
    for (uint64_t i = 0; i < (uint64_t) argc; i++) {
        printf("%lu: %s\n", i, DS_as_cstr(&args[i]));
    }
    return 0;
}
