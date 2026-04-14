/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeducas <gaeducas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/27 11:31:57 by gaeducas          #+#    #+#             */
/*   Updated: 2026/04/09 04:35:25 by thbosvie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	get_res_exit_code(char to_check, int *error, unsigned long long *res,
		int sign)
{
	if (*error)
		return ;
	if (*res > 922337203685477580ULL || (*res == 922337203685477580ULL
			&& (unsigned long long)(to_check - '0') > (unsigned long long)(7
		+ (sign == -1))))
	{
		*error = 1;
		return ;
	}
	*res = *res * 10 + (unsigned long long)(to_check - '0');
}

static int	get_simple_exit_code(char *str, int *error)
{
	int					i;
	int					sign;
	unsigned long long	res;

	i = 0;
	sign = 1;
	res = 0;
	*error = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '+' || str[i] == '-')
		sign = ((str[i++] % 43) * -1) + 1;
	if (!(str[i] >= '0' && str[i] <= '9'))
		*error = 1;
	while (str[i] >= '0' && str[i] <= '9')
	{
		get_res_exit_code(str[i], error, &res, sign);
		i++;
	}
	while (str[i++])
		if (str[i - 1] != ' ' && !(str[i - 1] >= 9 && str[i - 1] <= 13))
			*error = 1;
	if (*error == 1)
		return (2);
	return ((int)(((res * sign) % 256 + 256) % 256));
}

void	free_exit(t_cmd *cmd, t_token *token, t_shell *shell, int exit_code)
{
	free_token(token);
	free_env(shell->env);
	free_cmd(cmd);
	exit(exit_code);
}

int	ft_exit(t_cmd *cmd, t_token *token, t_shell *shell)
{
	int	error_flag;
	int	exit_code;

	error_flag = 0;
	ft_putstr_fd("exit\n", 2);
	if (!cmd->args[1])
		free_exit(cmd, token, shell, g_signal);
	exit_code = get_simple_exit_code(cmd->args[1], &error_flag);
	if (error_flag == 1)
	{
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(cmd->args[1], 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		free_exit(cmd, token, shell, 2);
	}
	if (cmd->args[2])
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		return (1);
	}
	free_exit(cmd, token, shell, exit_code);
	exit(exit_code);
}
