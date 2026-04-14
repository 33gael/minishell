/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeducas <gaeducas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/01 20:07:11 by thbosvie          #+#    #+#             */
/*   Updated: 2026/04/10 11:12:16 by gaeducas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_empty_input(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (1);
	while (str[i])
	{
		if (str[i] != ' ' && !(str[i] >= 9 && str[i] <= 13))
			return (0);
		i++;
	}
	return (1);
}

int	is_builtin_name(char *cmd_name)
{
	if (!cmd_name)
		return (0);
	if (ft_strcmp("cd", cmd_name) == 0 || ft_strcmp("pwd", cmd_name) == 0
		|| ft_strcmp("env", cmd_name) == 0 || ft_strcmp("exit", cmd_name) == 0
		|| ft_strcmp("export", cmd_name) == 0 || ft_strcmp("unset",
			cmd_name) == 0 || ft_strcmp("echo", cmd_name) == 0)
		return (1);
	return (0);
}

int	prepare_all_heredocs(t_cmd *cmd_list, t_token *token, t_shell *shell)
{
	(void)cmd_list;
	while (token)
	{
		if (token->type == HEREDOC && token->next)
		{
			if (ft_heredoc(token->next->content, token->next->quote,
					shell) == 1)
				return (1);
		}
		token = token->next;
	}
	return (0);
}

void	inside_minish(char *input, t_shell *shell)
{
	t_token	*token;
	t_cmd	*cmd;

	add_history(input);
	token = ft_lexer(input, shell);
	if (token)
	{
		cmd = ft_parsing(token);
		if (cmd)
		{
			run_minishell(cmd, token, shell);
			free_cmd(cmd);
		}
		free_token(token);
	}
}

int	ft_readline(t_shell *shell)
{
	char	*input;

	rl_outstream = stderr;
	while (1)
	{
		init_signals();
		if (isatty(STDIN_FILENO))
			input = readline("\001\033[1;31m\002Mini_Hell$ \001\033[0m\002");
		else
			input = readline(NULL);
		if (input == NULL)
		{
			if (isatty(STDIN_FILENO))
				ft_putstr_fd("exit\n", 2);
			break ;
		}
		if (is_empty_input(input) == 0)
			inside_minish(input, shell);
		if (input)
			free(input);
	}
	rl_clear_history();
	return (0);
}
