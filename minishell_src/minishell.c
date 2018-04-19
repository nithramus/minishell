#include "minishell.h"

extern char **environ;
int PID;

static const t_command list_command[] = {
    { "setenv", ft_setenv },
    { "env", ft_env },
    { "unsetenv", ft_unsetenv },
    { "cd", ft_cd },
    { "pwd", ft_pwd },
    { "echo", ft_echo },
    { "exit", ft_exit }
};

void    ft_strreplace(char *string, char searched, char replace) 
{
    int i;

    i = 0;
    while (string[i])
    {
        if (string[i] == searched)
        {
            string[i] = replace;
        }
        i++;
    }
}

void quit_clean(t_libft_chained_list **env) 
{
	delete_chained_list(env, free);
    exit(0);
}

void    init(char **environ, t_libft_chained_list **env)
{
    int i;
    char *envvariable;

    i = 0;
    *env = NULL;
    while (environ[i])
    {
        if(!(envvariable = (char*)malloc(ft_strlen(environ[i]) + 1)))
            quit_clean(env);   
        ft_strcpy(envvariable, environ[i]);
        add_back_maillon(env, envvariable);
        i++;
    }

}

int     testcommand(char **command, t_libft_chained_list **env, char *path)
{
    int i;

    i = 0;
    while (i < 7)
    {
        if (ft_strcmp(command[0], list_command[i].name) == 0)
        {
            list_command[i].shell_function(env, path, command);
            return 1;
        }
        i++;
    }
    return 0;
}

void sig_handler(int signo)
{
	signo += 1-1;
	if (PID > 0)
	{
		kill(PID,SIGINT );
		PID = 0;
		ft_putendl("");
	}
	else
		ft_putstr("\nUse exit to quit\n$>");
}

int main() {
    char **command;
    char buff[500];
    char path[4097];
    t_libft_chained_list *env;
    int line_return;

	signal(SIGINT, sig_handler);
    env = NULL;
    if (!getcwd(path, 4096))
        return 1;
    init(environ, &env);
    while (1)
    {
        
        if (!getcwd(path, 4096))
            return 1;
		ft_putstr(path);
		ft_putstr(" $>");
        line_return = read(0,buff, 499);
        if (line_return != 0)
        {
        	buff[line_return - 1] = '\0';
            ft_strreplace(buff, '\t', ' ');
            command = ft_strsplit(buff, ' ');
            if (command && command[0])
                if (!testcommand(command, &env, path))
                {
                    execute_binary(&env, command);
                }
			if (!command)
				ft_exit(&env, path, command);
            ft_bzero(buff, 500);
			freechartab(command);
        }
    }
}