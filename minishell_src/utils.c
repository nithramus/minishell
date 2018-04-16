#include "minishell.h"



int countarguments(char **tab)
{
    int i;

    i = 0;
    while (tab[i])
    {
        i++;
    }
    return (i);
}