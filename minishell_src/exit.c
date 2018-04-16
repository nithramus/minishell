#include "minishell.h"

void ft_exit(t_libft_chained_list **env, char **path, char **command)
{
    freechartab(command);
    delete_chained_list(env, free);
    do_nothing((void*)path);
    exit(0);
}