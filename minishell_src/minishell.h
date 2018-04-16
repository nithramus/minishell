#ifndef MINISHELL
#define MINISHELL

#include <sys/types.h>
#include <sys/wait.h>
#include "../libft/libft/libft.h"
#include "../libft_chained_list/libft_chained_list_src/libft_chained_list.h"

typedef struct s_command 
{
    char *name;
    void (*shell_function)(t_libft_chained_list **env, char **path, char **command);
}               t_command;

void execute_binary(char *command, char **env);
int countarguments(char **tab);
void ft_setenv(t_libft_chained_list **env, char **path, char **command);
void ft_env(t_libft_chained_list **env, char **path, char **command);



#endif