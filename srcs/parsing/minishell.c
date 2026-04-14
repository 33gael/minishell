/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeducas <gaeducas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/13 20:17:40 by username          #+#    #+#             */
/*   Updated: 2026/04/09 05:11:28 by thbosvie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	if (!s1 || !s2)
		return (1);
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return (s1[i] - s2[i]);
}

int	main(int ac, char **av, char **envp)
{
	t_env	*env;
	t_shell	shell;

	(void)av;
	if (ac != 1)
		return (1);
	env = init_env(envp);
	increment_shlvl(&env);
	init_signals();
	shell.env = env;
	ft_readline(&shell);
	if (shell.env)
		free_env(env);
	return (g_signal);
}
