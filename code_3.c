#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_INPUT_SIZE 1024

/**
 * main - Entry point of the shell program
 *
 * Return: Always 0 (Success)
 */
int main(void)
{
    char *input;
    size_t bufsize = MAX_INPUT_SIZE;

    while (1)
    {
        
        write(STDOUT_FILENO, ":) ", 3);

        
        input = (char *)malloc(bufsize * sizeof(char));
        if (!input)
        {
            perror("malloc failed");
            exit(EXIT_FAILURE);
        }

        if (getline(&input, &bufsize, stdin) == EOF)
        {
            
            write(STDOUT_FILENO, "\n", 1);
            free(input);
            exit(EXIT_SUCCESS);
        }

        
        input[strlen(input) - 1] = '\0';

        
        char *token = strtok(input, " ");
        char *args[MAX_INPUT_SIZE];
        int i = 0;

        while (token != NULL)
        {
            args[i++] = token;
            token = strtok(NULL, " ");
        }

        args[i] = NULL;

        
        pid_t pid = fork();

        if (pid == -1)
        {
            perror("fork failed");
            exit(EXIT_FAILURE);
        }
        else if (pid == 0)
        {
           
            if (execvp(args[0], args) == -1)
            {
                
                perror("execvp failed");
                exit(EXIT_FAILURE);
            }
        }
        else
        {
            
            wait(NULL); // Wait for the child to finish
        }

        free(input);
    }

    return 0;
}

