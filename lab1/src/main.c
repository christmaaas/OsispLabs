#include "dirwalk.h"

#include <stdio.h>

int main(int argc, char *argv[])
{
    active_flags flags;

    const char* path = get_path(argc, argv);

    get_flags(argc, argv, &flags);

    dirwalk(path, flags);

    return 0;
}