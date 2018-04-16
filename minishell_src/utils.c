#include "minishell.h"

void freechartab(char **tab)
{
    int i;

    i = 0;
    if (!tab)
        return;
    while (tab[i])
    {
        free(tab[i]);
        i++;
    }
    free(tab);
}

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