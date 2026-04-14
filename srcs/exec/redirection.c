/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeducas <gaeducas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/20 13:09:33 by gaeducas          #+#    #+#             */
/*   Updated: 2026/04/10 11:07:07 by gaeducas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_redir_out(char *file)
{
	int	fd;

	if (!file)
		return (1);
	fd = open(file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd < 0)
	{
		ft_putstr_fd(file, 2);
		ft_putstr_fd(": Permission denied\n", 2);
		return (1);
	}
	dup2(fd, 1);
	close(fd);
	return (0);
}

int	ft_redir_in(char *file)
{
	int	fd;

	if (!file)
		return (1);
	fd = open(file, O_RDONLY);
	if (fd < 0)
	{
		ft_putstr_fd(file, 2);
		ft_putstr_fd(": Permission denied\n", 2);
		return (1);
	}
	dup2(fd, 0);
	close(fd);
	return (0);
}

int	ft_append(char *file)
{
	int	fd;

	if (!file)
		return (1);
	fd = open(file, O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (fd < 0)
	{
		ft_putstr_fd(file, 2);
		ft_putstr_fd(": Permission denied\n", 2);
		return (1);
	}
	dup2(fd, 1);
	close(fd);
	return (0);
}
