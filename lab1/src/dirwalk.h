#pragma once

#include <stdbool.h>

#define MAX_PATH_LEN 512

typedef struct active_flags
{
    bool _l, 
         _s, 
         _d, 
         _f,
         _is_any_flag_set; 
} flag_t;

typedef enum application_flags
{
    _SYMBOL_LINK = 'l',
    _DIRECTORY = 'd',
    _FILE = 'f',
    _SORT = 's'
} appflags_t;

const char* get_path(const int argc, const char* argv[]);
void get_flags(const int argc, const char* argv[], flag_t* flags);
void dirwalk(const char* path, const flag_t flags);
