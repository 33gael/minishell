/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thbosvie <marvin@d42.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 13:07:41 by thbosvie          #+#    #+#             */
/*   Updated: 2026/04/08 14:09:12 by thbosvie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_syntax(t_token *token)
{
	t_token	*first;
	t_token	*last;

	first = token;
	last = token;
	while (last->next)
		last = last->next;
	if (first->type == PIPE || last->type == PIPE)
		return (1);
	while (token)
	{
		if (token->next && token->type == PIPE && token->next->type == PIPE)
			return (1);
		if (token->type != PIPE && token->type != WORD && (!token->next
				|| token->next->type != WORD))
			return (1);
		token = token->next;
	}
	return (0);
}

t_cmd	*ft_parsing(t_token *token)
{
	t_cmd	*cmd;
	t_cmd	*next;

	if (check_syntax(token))
	{
		ft_putstr_fd("syntax error: near unexpected token\n", 2);
		g_signal = 2;
		return (NULL);
	}
	cmd = create_cmd(&token, NULL);
	while (token)
	{
		next = create_cmd(&token, cmd);
		if (token && token->next)
			token = token->next;
	}
	return (cmd);
}
