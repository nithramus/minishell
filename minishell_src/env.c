#include "minishell.h"

void update_env(t_libft_chained_list **env, t_libft_chained_list *maillon, void *params)
{
    t_env *param;

    param = (t_env*)params;
    if (ft_strncmp(maillon->data, param->envname, ft_strlen(param->envname)) == 0)
    {
        if (((char*)maillon->data)[ft_strlen(param->envname)] == '=')
        {
            free(maillon->data);
            maillon->data = param->newenv;
            param->found = 1;
        }
    }
    do_nothing(env);
}

char    *create_env_parameter(char *name, char *value)
{
    char *tmp;
    char *final;

    tmp = ft_strjoin(name, "=");
    final = ft_strjoin(tmp, value);
    free(tmp);
    return final;
}

void delete_env_parameter(t_libft_chained_list **env, t_libft_chained_list *maillon, void *params)
{
    t_env *param;

    param = (t_env*)params;
    if (ft_strncmp(maillon->data, param->envname, ft_strlen(param->envname)) == 0)
    {
        if (((char*)maillon->data)[ft_strlen(param->envname)] == '=')
            remove_maillon(env, maillon, free);
    }
}

void ft_setenv(t_libft_chained_list **env, char **path, char **command)
{
    t_env params;
    if (countarguments(command) != 3)
    {
        ft_putendl("3 argument required");
        return;
    }
    params.found = 0;
    params.envname = command[1];
    params.newenv = create_env_parameter(command[1], command[2]);
    function_on_chained_list(env, update_env, &params);
    if (!params.found)
    {
        add_back_maillon(env, params.newenv);
    }
    do_nothing((void*)path);

}

void ft_unsetenv(t_libft_chained_list **env, char **path, char **command)
{
    t_env params;

    if (countarguments(command) != 2)
    {
        return;
    }
    params.envname = command[1];
    function_on_chained_list(env, delete_env_parameter, &params);
    do_nothing((void*)path);

}

void ft_env(t_libft_chained_list **env, char **path, char **command)
{
    simple_function_on_chained_list(env, (void (*)(void *))ft_putendl);
    do_nothing((void*)path);
    do_nothing((void*)command);

}