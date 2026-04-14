/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeducas <gaeducas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/16 14:39:21 by thbosvie          #+#    #+#             */
/*   Updated: 2026/04/12 00:09:13 by thbosvie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*get_link(t_token *token, t_token *next, int i)
{
	t_token	*link;

	link = NULL;
	if (i == 1)
	{
		link = token;
		while (link->next)
			link = link->next;
	}
	else
	{
		link = next;
		while (link->next)
			link = link->next;
	}
	return (link);
}

int	get_token_index(t_token *token)
{
	int		token_index;
	t_token	*tmp;

	token_index = 0;
	tmp = token;
	while (tmp->next)
	{
		tmp = tmp->next;
		if (!is_operator(tmp->content[0]))
			token_index++;
	}
	return (token_index + 1);
}

static t_token	*ft_lexer_loop(char **strs, t_token *token, int *quote_array)
{
	int		i;
	t_token	*link;
	t_token	*next;
	t_token	*first;

	i = 1;
	first = token;
	while (strs[i])
	{
		link = get_link(token, next, i);
		next = create_token(strs[i], token, quote_array[i]);
		if (next->quote == 0)
			next = check_token(next, link);
		if (!next)
			return (NULL);
		i++;
	}
	return (first);
}

static t_token	*tokenizer(char **strs, int *quote)
{
	t_token	*token;
	t_token	*tmp;

	token = create_token(strs[0], NULL, quote[0]);
	tmp = token;
	token = check_token(token, NULL);
	if (!token)
	{
		free(quote);
		free_array(strs);
		free_token(tmp);
		return (NULL);
	}
	token = ft_lexer_loop(strs, token, quote);
	if (!token)
	{
		free(quote);
		free_array(strs);
		free_token(tmp);
		return (NULL);
	}
	return (token);
}

t_token	*ft_lexer(char *input, t_shell *shell)
{
	t_token	*token;
	int		size;
	int		*quote;
	char	**strs;

	size = 0;
	strs = input_to_token(input, &size, shell);
	if (!strs)
		return (NULL);
	quote = quote_array_create(input, size);
	token = tokenizer(strs, quote);
	if (!token)
		return (NULL);
	token = check_expand_token(token, shell);
	free_array(strs);
	free(quote);
	return (token);
}
