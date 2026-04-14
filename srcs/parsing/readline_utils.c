/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thbosvie <marvin@d42.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 02:51:39 by thbosvie          #+#    #+#             */
/*   Updated: 2026/04/09 02:53:27 by thbosvie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	check_error_builtin(int in, int out)
{
	if (in != -1)
	{
		dup2(in, STDIN_FILENO);
		close(in);
	}
	if (out != -1)
	{
		dup2(out, STDOUT_FILENO);
		close(out);
	}
}

static void	exec_parent_builtin(t_cmd *cmd, t_shell *shell, t_token *token)
{
	int	in;
	int	out;

	in = dup(STDIN_FILENO);
	out = dup(STDOUT_FILENO);
	if ((!cmd->infile || ft_redir_in(cmd->infile) == 0) && (!cmd->outfile
			|| ft_redir_out(cmd->outfile) == 0) && (!cmd->append
			|| ft_append(cmd->append) == 0) && (!cmd->heredoc
			|| ft_redir_in("/tmp/tempfile") == 0))
	{
		if (ft_strcmp(cmd->args[0], "exit") == 0)
		{
			close(in);
			close(out);
		}
		is_builtins(cmd, shell, token);
	}
	check_error_builtin(in, out);
}

void	run_minishell(t_cmd *cmd_list, t_token *token, t_shell *shell)
{
	if (!cmd_list)
		return ;
	if (prepare_all_heredocs(cmd_list, token, shell) == 1)
		return ;
	if (cmd_list->next == NULL && is_builtin_name(cmd_list->args[0]))
		exec_parent_builtin(cmd_list, shell, token);
	else
		execute_pipeline(cmd_list, shell, token);
	unlink("/tmp/tempfile");
}
