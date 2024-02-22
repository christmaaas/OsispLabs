#include "dirwalk.h"

int main(int argc, char *argv[])
{
    active_flags flags;

    get_flags(argc, argv, &flags);

    dirwalk(get_path(argc, argv), flags);

    return 0;
}