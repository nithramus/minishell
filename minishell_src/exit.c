/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bandre <bandre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/02 20:13:32 by bandre            #+#    #+#             */
/*   Updated: 2018/05/02 20:13:42 by bandre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exit(t_libft_chained_list **env, char *path, char **command)
{
	freechartab(command);
	delete_chained_list(env, free);
	do_nothing((void*)path);
	exit(0);
}
