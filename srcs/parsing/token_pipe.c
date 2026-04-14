/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thbosvie <marvin@d42.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 20:26:18 by thbosvie          #+#    #+#             */
/*   Updated: 2026/04/07 11:27:44 by thbosvie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_token	*token_pipe(t_token *token, t_token **link, int *i, char *str)
{
	int	is_link;

	is_link = 0;
	if (*i != 0 && str[0] != '\0')
		token = create_token(str, token, 0);
	if (*link && *i != 0 && str[0] != '\0')
	{
		(*link)->next = token;
		is_link = 1;
	}
	if (str)
		free(str);
	*i = *i + 1;
	token = create_token("|", token, 0);
	if (*link && *i != 0 && is_link == 0)
		(*link)->next = token;
	*link = token;
	return (token);
}

t_token	*token_loop_pipe(t_token *token, int *i, int *start, t_token **link)
{
	t_token	*tmp;
	t_token	*first;
	char	*str;

	tmp = NULL;
	first = token;
	while (token->next)
		token = token->next;
	str = ft_substr(first->content, *start, *i - *start);
	if (first->content != token->content)
		tmp = token;
	token = token_pipe(token, link, i, str);
	if (first->content[*i] != '\0')
		token = create_token(first->content + *i, token, 0);
	*start = *i;
	free_tmp(tmp);
	return (first);
}
