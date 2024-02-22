#include "dirwalk.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>

#define __USE_MISC 
#include <dirent.h>

const char* get_path(const int argc, const char* argv[])
{
    for(int i = 1; i < argc; i++)
    {
        if(argv[i][0] != '-')
            return argv[i];
    }

    return ".";
}

void get_flags(const int argc, const char* argv[], active_flags* flags)
{
    char flag;
    while ((flag = getopt(argc, argv, "ldfs")) != -1)
    {
        switch(flag)
        {
            case _DIRECTORY:
            {
                flags->_d = true;
                flags->_is_any_flag_set = true;
                
                break;
            }
            case _SYMBOL_LINK:
            {
                flags->_l = true;
                flags->_is_any_flag_set = true;
                
                break;
            }
            case _SORT:
            {
                flags->_s = true;
                flags->_is_any_flag_set = true;
                
                break;
            }
            case _FILE:
            {
                flags->_f = true;
                flags->_is_any_flag_set = true;
                
                break;
            }
        }
    }
}

bool comparator(const struct dirent** a, const struct dirent** b) 
{
    return strcoll((*a)->d_name, (*b)->d_name);
}

void dirwalk(const char* path, const active_flags flags)
{
    struct dirent** directories_list;

    int count_of_files;

    char next_directory_path[MAX_PATH_LEN];

    if(flags._s)
        count_of_files = scandir(path, &directories_list, NULL, comparator); 
    else
        count_of_files = scandir(path, &directories_list, NULL, NULL);

    if(count_of_files == -1)
    {
        perror("scnadir");
        return;
    }

    for(int i = 0; i < count_of_files; i++)
    {
        switch (directories_list[i]->d_type)
        {
            case DT_REG:
            {
                if(flags._f || !flags._is_any_flag_set)
                    printf("%s/%s\n", path, directories_list[i]->d_name);

                break;
            }
            case DT_LNK:
            {
                if(flags._l || !flags._is_any_flag_set)
                    printf("%s/%s\n", path, directories_list[i]->d_name);

                break;
            }
            case DT_DIR:
            {
                if(!strcmp(directories_list[i]->d_name, ".") || !strcmp(directories_list[i]->d_name, ".."))
                    break;

                if(flags._d || !flags._is_any_flag_set)
                {
                    printf("%s/%s\n", path, directories_list[i]->d_name);

                    sprintf(next_directory_path, "%s/%s", path, directories_list[i]->d_name);

                    dirwalk(next_directory_path, flags);
                }

                break;    
            }
        }

        free(directories_list[i]);
    }

    free(directories_list);
}