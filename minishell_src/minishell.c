#include "minishell.h"

extern char **environ;

static const t_command list_command[] = {
    { "setenv", ft_setenv },
    { "env", ft_env },
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

void print_tab(char **tab)
{
    int i;

    i = 0;
    while (tab[i])
    {
        ft_putendl(tab[i]);
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
        if(!(envvariable = (char*)malloc(ft_strlen(environ[i]))))
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
    while (i < 2)
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

int main(int argc, char **argv) {
    char *line;
    char **command;
    char buff[500];
    t_libft_chained_list *env;
    line = NULL;
    argc +=1;
    char *path;
    int line_return;

    argv++;
    env = NULL;
    path = malloc(PATH_MAX);
    path = getcwd(path, PATH_MAX);
    init(environ, &env);
    while (1)
    {
        line_return = read(0,buff, 499);
        buff[line_return - 1] = '\0';
        line = buff;
        ft_putendl(line);
        ft_putendl("command");  
        if (line_return != 0)
        {
            ft_printf("%d\n", line_return);
            if (!line)
                ft_putendl("NULL line");
            else
            {
                ft_strreplace(line, '\t', ' ');
                command = ft_strsplit(line, ' ');
                print_tab(command);
                if (command && command[0])
                    testcommand(command, &env, &path);
                    // execute_binary(line, argv);
            }
        }
    }
}