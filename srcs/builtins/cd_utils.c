/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thbosvie <marvin@d42.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/08 15:39:54 by thbosvie          #+#    #+#             */
/*   Updated: 2026/04/08 19:43:20 by thbosvie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_arg_cd(int n_arg)
{
	if (n_arg > 2)
	{
		ft_putstr_fd("error: cd: too many arguments\n", 2);
		return (1);
	}
	return (0);
}

int	n_arg_init(char **path)
{
	int	n_arg;

	n_arg = 0;
	while (path[n_arg])
		n_arg++;
	return (n_arg);
}
