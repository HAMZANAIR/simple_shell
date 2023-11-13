#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_INPUT_SIZE 1024

/**
 *   main - Entry point of the shell program
 *   
 *   Return: Always 0 (Success)
 **/
 int main(void)
 {
     char *input;
     size_t bufsize = MAX_INPUT_SIZE;

	while (1)
	{
	          //Display prompt
		  write(STDOUT_FILENO, "#cisfun$ ", 9);
	              //Read user input
	              input = (char *)malloc(bufsize * sizeof(char));
                       if (!input)
                             {
                                perror("malloc failed");
                                 exit(EXIT_FAILURE);
			     }
		       if (getline(&input, &bufsize, stdin) == EOF){
					        // Handle end of file (Ctrl+D)
						write(STDOUT_FILENO, "\n", 1);
			                       free(input);
					      exit(EXIT_SUCCESS);
	                                                           }
		       // Remove newline character
		        input[strlen(input) - 1] = '\0';
			// Fork to create a child process
			 pid_t pid = fork();
			 if (pid == -1)
				         {
				           perror("fork failed");
					   exit(EXIT_FAILURE);
				         }
			 else if (pid == 0)
				         {
						   // Child process
						   if (execlp(input, input, (char *)NULL) == -1)
							               {perror("exec failed");
									                       exit(EXIT_FAILURE);
											                   }
					 }
			         else
					         {
							            // Parent process
								        wait(NULL); // Wait for the child to finish
								                   }
				 free(input);
				     }
 return (0);
 }

