#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

#include "../libs/DynamicString.h"

#define UNUSED(x) do { (void) x; } while(false)

int main(int argc, char** argv)
{
    DS args[argc - 1];
    for (uint64_t i = 1; i < (uint64_t) argc; i++) {
        args[i - 1] = DS_from_cstr(argv[i]);
    }

    // TODO FIX: basename "/etc/portage/" should return "portage", not an empty string
    for (uint64_t i = 0; i < (uint64_t) argc - 1; i++) {
        DS tail = DS_tail(&args[i], DS_find_last_ch(&args[i], '/') + 1);
        printf("%s\n", DS_as_cstr(&tail));
    }
    return 0;
}
