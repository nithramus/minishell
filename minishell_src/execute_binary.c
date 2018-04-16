#include "minishell.h"

void execute_binary(char *command, char **env)
{
    int father;
    int status;
    int execstatus;

    execstatus = 1;
    father = fork();
    if (father > 0)
    {
        ft_putendl("FATHER");
        ft_putendl("FATHER");
        ft_putendl("FATHER");
        ft_putendl("FATHER");
        
        // execstatus = execve(command, env, NULL);
    }
    else {
        wait(&status);
        ft_putendl("finished");
    }
    ft_putendl("only one");
}