/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_redir_out.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeducas <gaeducas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 20:30:49 by thbosvie          #+#    #+#             */
/*   Updated: 2026/04/12 00:09:53 by thbosvie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*check_size_out(int *i, t_token *first, t_token *token)
{
	int	size;

	size = how_c_in_row(first->content + *i, '>');
	if (size > 2)
	{
		g_signal = 2;
		ft_putstr_fd("minishell : syntax error near unexpected token '>'\n", 2);
		return (NULL);
	}
	*i = *i + size;
	if (size == 1)
		token = create_token(">", token, 0);
	else
		token = create_token(">>", token, 0);
	return (token);
}

t_token	*token_loop_out(t_token *token, int *i, int *start, t_token **link)
{
	t_token	*tmp;
	t_token	*first;
	char	*str;
	int		is_link;

	is_link = 0;
	tmp = NULL;
	first = token;
	while (token->next)
		token = token->next;
	if (first->content != token->content)
		tmp = token;
	str = ft_substr(first->content, *start, *i - *start);
	is_link = to_link_redir(i, str, &token, link);
	token = check_size_out(i, first, token);
	if (!token)
		return (NULL);
	if (*link && *i != 0 && is_link == 0)
		(*link)->next = token;
	*link = token;
	if (first->content[*i] != '\0')
		token = create_token(first->content + *i, token, 0);
	*start = *i;
	free_tmp(tmp);
	return (first);
}
