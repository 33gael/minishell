/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_other_type.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeducas <gaeducas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/08 14:12:00 by thbosvie          #+#    #+#             */
/*   Updated: 2026/04/10 10:58:21 by gaeducas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_redir_in(t_token **token, t_cmd **cmd)
{
	int	fd;

	if ((*cmd)->infile)
	{
		fd = open((*cmd)->infile, O_RDONLY);
		if (fd >= 0)
		{
			close(fd);
			free((*cmd)->infile);
			(*cmd)->infile = ft_strdup((*token)->next->content);
		}
	}
	else
		(*cmd)->infile = ft_strdup((*token)->next->content);
}

static void	handle_redir_out(t_token **token, t_cmd **cmd)
{
	int	fd;

	if ((*cmd)->outfile)
	{
		fd = open((*cmd)->outfile, O_CREAT | O_WRONLY | O_TRUNC, 0644);
		if (fd >= 0)
		{
			close(fd);
			free((*cmd)->outfile);
			(*cmd)->outfile = ft_strdup((*token)->next->content);
		}
	}
	else
		(*cmd)->outfile = ft_strdup((*token)->next->content);
}

static void	handle_append(t_token **token, t_cmd **cmd)
{
	int	fd;

	if ((*cmd)->append)
	{
		fd = open((*cmd)->append, O_CREAT | O_WRONLY | O_APPEND, 0644);
		if (fd >= 0)
		{
			close(fd);
			free((*cmd)->append);
			(*cmd)->append = ft_strdup((*token)->next->content);
		}
	}
	else
		(*cmd)->append = ft_strdup((*token)->next->content);
}

void	cmd_other_type(t_token **token, t_cmd **cmd)
{
	if ((*token)->type == REDIR_OUT)
		handle_redir_out(token, cmd);
	else if ((*token)->type == APPEND)
		handle_append(token, cmd);
	else if ((*token)->type == REDIR_IN)
		handle_redir_in(token, cmd);
	else if ((*token)->type == HEREDOC)
	{
		if ((*cmd)->heredoc)
			free((*cmd)->heredoc);
		(*cmd)->heredoc = ft_strdup((*token)->next->content);
	}
	*token = (*token)->next->next;
}
