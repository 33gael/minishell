/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_process_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thbosvie <marvin@d42.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 20:43:38 by thbosvie          #+#    #+#             */
/*   Updated: 2026/04/10 23:57:30 by thbosvie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_input(t_cmd *cmd)
{
	if (cmd->heredoc)
	{
		if (ft_redir_in("/tmp/tempfile") == 1)
			return (1);
	}
	else if (cmd->infile)
	{
		if (ft_redir_in(cmd->infile) == 1)
			return (1);
	}
	return (0);
}

int	handle_output(t_cmd *cmd)
{
	if (cmd->append)
	{
		if (ft_append(cmd->append) == 1)
			return (1);
	}
	else if (cmd->outfile)
	{
		if (ft_redir_out(cmd->outfile) == 1)
			return (1);
	}
	return (0);
}

void	setup_child_pipes(t_cmd *cmd, int prev_fd, int pipefd[2])
{
	if (prev_fd != STDIN_FILENO)
	{
		dup2(prev_fd, STDIN_FILENO);
		close(prev_fd);
	}
	if (cmd->next != NULL)
	{
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[1]);
		close(pipefd[0]);
	}
}

void	free_child_resources(t_exec *exec, t_shell *shell, t_token *token)
{
	free_cmd(exec->first);
	free(exec);
	free_env(shell->env);
	if (token)
		free_token(token);
	rl_clear_history();
}
