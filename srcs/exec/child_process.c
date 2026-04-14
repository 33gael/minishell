/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeducas <gaeducas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 16:23:39 by gaeducas          #+#    #+#             */
/*   Updated: 2026/04/10 23:59:59 by thbosvie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_builtins(t_cmd *cmd, t_shell *shell, t_token *token)
{
	free_cmd(cmd);
	free_env(shell->env);
	if (token)
		free_token(token);
	rl_clear_history();
}

void	free_cmd_exit(t_exec *exec, t_cmd *cmd)
{
	t_cmd	*tmp;

	while (exec->first != cmd)
	{
		tmp = exec->first;
		exec->first = exec->first->next;
		if (tmp->append)
			free(tmp->append);
		if (tmp->outfile)
			free(tmp->outfile);
		if (tmp->heredoc)
			free(tmp->heredoc);
		if (tmp->infile)
			free(tmp->infile);
		if (tmp->args)
			free_array(tmp->args);
		free(tmp);
	}
}

void	exec_child_builtins(t_exec *exec, t_cmd *cmd, t_token *token,
		t_shell *shell)
{
	t_cmd	*tmp;

	if (ft_strcmp(cmd->args[0], "exit") == 0)
	{
		free_cmd_exit(exec, cmd);
		tmp = exec->first;
		free(exec);
		if (is_builtins(tmp, shell, token) == 1)
		{
			free_builtins(tmp, shell, token);
			exit(g_signal);
		}
	}
	if (is_builtins(cmd, shell, token) == 1)
	{
		free_child_resources(exec, shell, token);
		exit(g_signal);
	}
}

void	exec_other_cmd(t_shell *shell, t_cmd *cmd, t_exec *exec, t_token *token)
{
	char	*path;
	char	*cmd_path;
	char	**env_array;

	path = ft_get_env(shell->env, "PATH");
	cmd_path = path_finder(cmd->args[0], path);
	if (!cmd_path)
	{
		ft_putstr_fd(cmd->args[0], 2);
		ft_putstr_fd(": command not found\n", 2);
		free_child_resources(exec, shell, token);
		free(path);
		exit(127);
	}
	env_array = list_to_array(shell->env);
	execve(cmd_path, cmd->args, env_array);
	free_array(env_array);
	free(cmd_path);
	free(path);
}

void	exec_child(t_cmd *cmd, t_exec *exec, t_shell *shell, t_token *token)
{
	restore_default_signals();
	setup_child_pipes(cmd, exec->prev_fd, exec->pipefd);
	if (handle_input(cmd) == 1 || handle_output(cmd) == 1)
	{
		free_child_resources(exec, shell, token);
		exit(1);
	}
	if (!cmd->args || !cmd->args[0])
	{
		free_child_resources(exec, shell, token);
		exit(0);
	}
	exec_child_builtins(exec, cmd, token, shell);
	exec_other_cmd(shell, cmd, exec, token);
	free_child_resources(exec, shell, token);
	exit(126);
}
