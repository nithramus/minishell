#include "minishell.h"

void    ft_pwd(t_libft_chained_list **env, char **path, char **command)
{
    ft_putendl(*path);
    do_nothing((void*)env);
        do_nothing((void*)command);

}
char    *create_path(char *name, char *value)
{
    char *tmp;
    char *final;

    tmp = ft_strjoin(name, "/");
    final = ft_strjoin(tmp, value);
    return final;
}

void    ft_cd(t_libft_chained_list **env, char **path, char **command)
{
    char *new_path;
    int status;
    t_search searched;
    t_env params;

    
    if (countarguments(command) == 1)   
    {
        searched.searched = "HOME";
        searched.result = NULL;
        function_on_chained_list(env, search, &searched);
        if (!searched.result)
            return;
        new_path = searched.result;
    }
    else
    {
        new_path = create_path(*path, command[1]);
    }
    status = chdir(new_path);
    if (status == -1)
        ft_putendl("No such file or directory");
    else
    {
        params.found = 0;
        params.envname = command[1];
        params.newenv = create_env_parameter(command[1], command[2]);
        function_on_chained_list(env, update_env, &params);
    }

}