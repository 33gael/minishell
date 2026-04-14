/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_token.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeducas <gaeducas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/22 16:04:38 by thbosvie          #+#    #+#             */
/*   Updated: 2026/04/07 13:48:01 by gaeducas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	type_check(char *str, int quote)
{
	if (quote != 0)
		return (WORD);
	if ((ft_strncmp(str, "|", 2)) == 0)
		return (PIPE);
	else if ((ft_strncmp(str, "<", 2)) == 0)
		return (REDIR_IN);
	else if ((ft_strncmp(str, ">", 2)) == 0)
		return (REDIR_OUT);
	else if ((ft_strncmp(str, ">>", 3)) == 0)
		return (APPEND);
	else if ((ft_strncmp(str, "<<", 3)) == 0)
		return (HEREDOC);
	return (WORD);
}

static void	add_back_token(t_token *token, t_token *node)
{
	while (token->next)
		token = token->next;
	token->next = node;
}

static t_token	*token_fill(char *str, int quote)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->quote = quote;
	token->content = ft_strdup(str);
	token->type = type_check(str, quote);
	token->next = NULL;
	return (token);
}

t_token	*create_token(char *str, t_token *token, int quote)
{
	t_token	*next;

	next = token_fill(str, quote);
	if (token != NULL)
		add_back_token(token, next);
	return (next);
}
