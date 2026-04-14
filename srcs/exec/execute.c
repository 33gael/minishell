/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeducas <gaeducas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 20:40:49 by thbosvie          #+#    #+#             */
/*   Updated: 2026/04/10 10:58:40 by gaeducas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	exec_parent(t_cmd *cmd, int *prev_fd, int pipefd[2])
{
	if (*prev_fd != STDIN_FILENO)
		close(*prev_fd);
	if (cmd->next != NULL)
	{
		close(pipefd[1]);
		*prev_fd = pipefd[0];
	}
}

static void	wait_pipeline(pid_t last_pid)
{
	int		status;
	pid_t	wait_ret;

	wait_ret = waitpid(-1, &status, 0);
	while (wait_ret > 0)
	{
		if (wait_ret == last_pid)
		{
			if (WIFEXITED(status))
				g_signal = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
			{
				g_signal = 128 + WTERMSIG(status);
				if (WTERMSIG(status) == SIGQUIT)
					printf("Quit\n");
				else if (WTERMSIG(status) == SIGINT)
					printf("\n");
			}
		}
		wait_ret = waitpid(-1, &status, 0);
	}
}

static t_exec	*exec_init(t_cmd *cmd_list)
{
	t_exec	*exec;

	exec = malloc(sizeof(t_exec));
	if (!exec)
		return (NULL);
	exec->pid = -1;
	exec->prev_fd = STDIN_FILENO;
	exec->first = cmd_list;
	return (exec);
}

void	execute_pipeline(t_cmd *cmd_list, t_shell *shell, t_token *token)
{
	t_cmd	*curr;
	t_exec	*exec;

	exec = exec_init(cmd_list);
	if (!exec)
		return ;
	curr = cmd_list;
	ignore_signals_execution();
	while (curr)
	{
		if (curr->next != NULL && pipe(exec->pipefd) == -1)
			exit(EXIT_FAILURE);
		exec->pid = fork();
		if (exec->pid == -1)
			exit(EXIT_FAILURE);
		if (exec->pid == 0)
			exec_child(curr, exec, shell, token);
		else
			exec_parent(curr, &(exec->prev_fd), exec->pipefd);
		curr = curr->next;
	}
	if (exec->pid != -1)
		wait_pipeline(exec->pid);
	free(exec);
}
