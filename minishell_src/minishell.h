#ifndef MINISHELL
#define MINISHELL

#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include "../libft/libft/libft.h"
#include "../libft_chained_list/libft_chained_list_src/libft_chained_list.h"

typedef struct s_command 
{
    char *name;
    void (*shell_function)(t_libft_chained_list **env, char *path, char **command);
}               t_command;

typedef struct s_complete
{
    int count;
    char **list;
}               t_complete;

typedef struct s_search
{
    char *searched;
    char *result;
}           t_search;

typedef struct s_env {
    int found;
    char *envname;
    char *newenv;
}           t_env;

void execute_binary(t_libft_chained_list **env, char **command);
int countarguments(char **tab);
void ft_setenv(t_libft_chained_list **env, char *path, char **command);
void ft_env(t_libft_chained_list **env, char *path, char **command);
void ft_unsetenv(t_libft_chained_list **env, char *path, char **command);
void    ft_cd(t_libft_chained_list **env, char *path, char **command);
void    ft_pwd(t_libft_chained_list **env, char *path, char **command);
void ft_echo(t_libft_chained_list **env, char *path, char **command);
void print_tab(char **tab);
char    *create_path(char *name, char *value);
void search(t_libft_chained_list **env, t_libft_chained_list *maillon, void *params);
void do_nothing(void *params);
void update_env(t_libft_chained_list **env, t_libft_chained_list *maillon, void *params);
char    *create_env_parameter(char *name, char *value);
void freechartab(char **tab);
void ft_exit(t_libft_chained_list **env, char *path, char **command);


#endif