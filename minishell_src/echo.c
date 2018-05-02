/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bandre <bandre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/02 20:03:29 by bandre            #+#    #+#             */
/*   Updated: 2018/05/02 20:03:42 by bandre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_tab(char **tab)
{
	int i;

	i = 1;
	while (tab[i])
	{
		ft_printf("%s ", tab[i]);
		i++;
	}
	ft_putendl("");
}

void	ft_echo(t_libft_chained_list **env, char *path, char **command)
{
	print_tab(command);
	do_nothing((void*)env);
	do_nothing((void*)path);
}
