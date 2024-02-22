#pragma once

#include <stdbool.h>

#define MAX_PATH_LEN 256

typedef struct active_flags
{
    bool _l, _s, _d, _f, _is_any_flag_set; 
} active_flags;

typedef enum flags
{
    _SYMBOL_LINK = 'l',
    _DIRECTORY = 'd',
    _FILE = 'f',
    _SORT = 's'
} flags;

const char* get_path(const int argc, const char* argv[]);
void get_flags(const int argc, const char* argv[], active_flags* flags);
void dirwalk(const char* path, const active_flags flags);
