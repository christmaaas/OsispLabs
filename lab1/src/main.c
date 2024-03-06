#include "dirwalk.h"

int main(int argc, const char **argv)
{
    flag_t flags;

    get_flags(argc, argv, &flags);

    dirwalk(get_path(argc, argv), flags);

    return 0;
}