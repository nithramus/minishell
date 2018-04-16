#include "minishell.h"

extern char **environ;

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

void quit_clean() 
{
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
            quit_clean();   
        ft_strcpy(envvariable, environ[i]);
        add_back_maillon(env, envvariable);
        i++;
    }
        // simple_function_on_chained_list(env, ft_putendl);

}

int     testcommand(char **command, t_libft_chained_list **env, char **path)
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



int main() {
    char **command;
    char buff[500];
    char path[PATH_MAX];
    t_libft_chained_list *env;
    int line_return;

    env = NULL;
    if (!getcwd(path, PATH_MAX))
        return 1;
    init(environ, &env);
    while (1)
    {
        ft_putstr("$>");
        if (!(getcwd(path, PATH_MAX)))
            return 1;
        line_return = read(0,buff, 499);
        buff[line_return - 1] = '\0';
        if (line_return != 0)
        {
            ft_strreplace(buff, '\t', ' ');
            command = ft_strsplit(buff, ' ');
            // if (command && command[0])
            //     if (!testcommand(command, &env, (char**)&(path)))
            //     {
            //         // execute_binary(&env, command);
            //     }
            ft_bzero(buff, 500);
            freechartab(command);
            delete_chained_list(&env, free);
            exit(0);
        }
    }
}