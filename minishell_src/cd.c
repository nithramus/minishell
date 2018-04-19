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

    if (!(tmp = ft_strjoin(name, "/")))
		return (NULL);
    if (!(final = ft_strjoin(tmp, value)))
		return (NULL);
	free(tmp);
    return final;
}

void    ft_cd(t_libft_chained_list **env, char *path, char **command)
{
    char *new_path;
    int status;
    t_search searched;
    t_env params;
	int new_path_free;

	new_path_free = 0;
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
		else if (command[1][0] == '/')
		{
			new_path = command[1];
		}
		else
		{
        	if (!(new_path = create_path(path, command[1])))
				return;
			new_path_free = 1;
		}
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
		if (new_path_free)
			free(new_path);
	}
    else
    {
        params.found = 0;
        params.envname = "OLDPWD";
        params.newenv = create_env_parameter("OLDPWD", path);
		searched.searched = "OLDPWD";
        searched.result = NULL;
        function_on_chained_list(env, search, &searched);
		if (searched.result)
        	function_on_chained_list(env, update_env, &params);
		else
			add_back_maillon(env, params.newenv);
    }

}