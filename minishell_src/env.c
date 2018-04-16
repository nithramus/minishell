#include "minishell.h"

typedef struct s_env {
    int found;
    char *envname;
    char *newenv;
}           t_env;

void update_env(t_libft_chained_list **env, t_libft_chained_list *maillon, void *params)
{
    t_env *param;

    param = (t_env*)params;
    if (ft_strncmp(maillon->data, param->envname, ft_strlen(param->envname)) == 0)
    {
        free(maillon->data);
        maillon->data = param->newenv;
        param->found = 1;
    }
}

char    *create_env_parameter(char *name, char *value)
{
    char *tmp;
    char *final;

    tmp = ft_strjoin(name, "=");
    final = ft_strjoin(tmp, value);
    return final;

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
        add_back_maillon(env, "TEST DU PROG TMTC");
    }

}

// void unsetenv()
// {

// }

void ft_env(t_libft_chained_list **env, char **path, char **command)
{
    ft_putendl("couou");
    simple_function_on_chained_list(env, ft_putendl);
}