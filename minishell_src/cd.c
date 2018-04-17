#include "minishell.h"

void    ft_pwd(t_libft_chained_list **env, char *path, char **command)
{
    ft_putendl(path);
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

void    ft_cd(t_libft_chained_list **env, char *path, char **command)
{
    char *new_path;
    int status;
    t_search searched;
    t_env params;

    if (countarguments(command) == 1 || ft_strcmp(command[1], "~") == 0)
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
		if (ft_strcmp(command[1], "-") == 0)
		{
			searched.searched = "OLDPWD";
        	searched.result = NULL;
			function_on_chained_list(env, search, &searched);
			if (!searched.result)
				return;
			new_path = searched.result;
		}
		else
        	new_path = create_path(path, command[1]);
    }
    status = chdir(new_path);
    if (status == -1)
	{
		if (access(new_path, F_OK) == -1)
			ft_putstr("cd: no such file or directory\n");
		else if (access(new_path, R_OK) == -1)
			ft_putstr("cd: permission denied\n");
		else
			ft_putstr("cd: not a directory\n");
	}
    else
    {
        params.found = 0;
        params.envname = "OLDPWD";
        params.newenv = create_env_parameter("OLDPWD", new_path);
		searched.searched = "OLDPWD";
        searched.result = NULL;
        function_on_chained_list(env, search, &searched);
		if (searched.result)
        	function_on_chained_list(env, update_env, &params);
		else
			add_back_maillon(env, params.newenv);
    }

}