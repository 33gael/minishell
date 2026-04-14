/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_builtins.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeducas <gaeducas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/02 17:04:52 by thbosvie          #+#    #+#             */
/*   Updated: 2026/04/05 17:29:57 by thbosvie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtins(t_cmd *cmd, t_shell *shell, t_token *token)
{
	if (ft_strcmp("cd", cmd->args[0]) == 0)
		g_signal = ft_cd(cmd->args, shell->env);
	else if (ft_strcmp("pwd", cmd->args[0]) == 0)
		ft_pwd();
	else if (ft_strcmp("env", cmd->args[0]) == 0)
		g_signal = ft_env(shell->env);
	else if (ft_strcmp("exit", cmd->args[0]) == 0)
		g_signal = ft_exit(cmd, token, shell);
	else if (ft_strcmp("export", cmd->args[0]) == 0)
		g_signal = ft_export(&shell->env, cmd->args);
	else if (ft_strcmp("unset", cmd->args[0]) == 0)
		g_signal = ft_unset(&shell->env, cmd->args);
	else if (ft_strcmp("echo", cmd->args[0]) == 0)
		g_signal = ft_echo(cmd->args);
	else
		return (0);
	return (1);
}
