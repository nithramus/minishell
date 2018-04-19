#include "minishell.h"

extern int PID;

void do_nothing(void *params)
{
    params += 1-1;
}

void count(t_libft_chained_list **env, t_libft_chained_list *maillon, void *params)
{
    int *count;

    count = (int*)params;
    (*count)++;
    do_nothing((void*)env);
    do_nothing((void*)maillon);

}


void search(t_libft_chained_list **env, t_libft_chained_list *maillon, void *params)
{
    t_search *search_struct;

    search_struct = (t_search*)params;
    if (ft_strncmp(maillon->data, search_struct->searched, ft_strlen(search_struct->searched)) == 0)
    {
        if (((char*)maillon->data)[ft_strlen(search_struct->searched)] == '=')
        {
            search_struct->result = maillon->data + ft_strlen(search_struct->searched) + 1;
        }
    }
    do_nothing((void*)env);

}

void complete(t_libft_chained_list **env, t_libft_chained_list *maillon, void *params)
{
    t_complete *elem;

    elem = (t_complete*)params;
    elem->list[elem->count] = maillon->data;
    elem->count += 1;
    do_nothing((void*)env);

}

char **create_env(t_libft_chained_list **env)
{
    int elems;
    char **env_list;
    t_complete elem;

    elems = 0;
    function_on_chained_list(env, count, &elems);
    env_list = malloc(sizeof(char*) * (elems + 1));
    env_list[elems] = NULL;
    elem.count = 0;
    elem.list = env_list;
    function_on_chained_list(env, complete,&elem);
    return env_list;
}

char *find_valid_path(char **parsedpath, char *command)
{
    int i;
    char *fullpath;

    i = 0;
    while (parsedpath[i])
    {
        fullpath = create_path(parsedpath[i], command);
        if (access(fullpath, X_OK) == 0)
        {
            return (fullpath);
        }
        free(fullpath);
        i++;
    }
    return NULL;
}

char *find_path_to_binary(t_libft_chained_list **env, char **command)   
{
    char **parsed_path;
    t_search    search_struct;
    char *valid_path;

    search_struct.searched = "PATH";
    search_struct.result = NULL;
    
    if (command[0][0] == '/')
    {
        if (access(command[0], X_OK) == 0)
            return (command[0]);
    }
    function_on_chained_list(env, search, &search_struct);
    parsed_path = ft_strsplit(search_struct.result, ':');
    if (parsed_path)
    {
        valid_path = find_valid_path(parsed_path, command[0]);
		freechartab(parsed_path);
        return (valid_path);
    }
    return (NULL);
}

void exec_bin(char *path_to_binary, char **parameters, char **env_list)
{
    int son_pid;
    int status;

    status = 0;
    son_pid = fork();
    if (son_pid > 0)
	{
		PID = son_pid;
        wait(&status);
		PID = 0;
	}
    else
    {
        execve(path_to_binary, parameters, env_list);
    }
}

void execute_binary(t_libft_chained_list **env, char **command)
{
    char **env_list;
    char *path_to_binary;

    env_list = create_env(env);
    path_to_binary = find_path_to_binary(env, command);
    if (path_to_binary)
    {
        exec_bin(path_to_binary, command, env_list);
    }
    else
    {
        ft_printf("minishell: command not found: %s\n", command[0]);
    }
	free(env_list);
	free(path_to_binary);
}