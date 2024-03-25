#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

extern char **environ;

int main(int argc, char * argv[], char * envp[]) 
{
    printf("\nNAME PROGRAM: %s\n", argv[0]);
    printf("PID PROGRAM: %d\n", getpid());
    printf("PPID PROGRAM: %d\n", getppid());

    const char* filename = argv[1];
    FILE *file = fopen(filename, "r");
    
    if (!file) 
    {
        printf("File open error\n");
        exit(-1);
    }

    char buffer[128];
    while (fgets(buffer, sizeof(buffer), file))
    {
        char* new_line = strchr(buffer, '\n');
        if (new_line)
            *new_line = '\0';

        if (strcmp(argv[2], "+") == 0) 
        {
            char* value = getenv(buffer);
            
            if (value)
                printf("%s=%s\n", buffer, value);
            else
                printf("%s - not found\n", buffer);
        }
        if (strcmp(argv[2], "*") == 0) 
        {
            for (int i = 0; envp[i] != NULL; i++) 
            {
                char* var_value = NULL;
                if (strncmp(envp[i], buffer, strlen(buffer)) == 0)
                {
                    printf("%s\n", envp[i]);
                    break;
                }
            }
        }
        if (strcmp(argv[2], "&") == 0) 
        {
            for (int i = 0; environ[i] != NULL; i++) 
            {
                char* var_value = NULL;
                if (strncmp(environ[i], buffer, strlen(buffer)) == 0)
                {
                    printf("%s\n", environ[i]);
                    break;
                }
            }
        }
    }

    fclose(file);
    
    exit(0);
}