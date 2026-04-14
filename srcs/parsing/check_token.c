/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeducas <gaeducas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/16 16:21:58 by thbosvie          #+#    #+#             */
/*   Updated: 2026/04/09 20:56:00 by thbosvie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	how_c_in_row(char *start, char c)
{
	int	i;

	i = 0;
	while (start[i] == c)
		i++;
	return (i);
}

void	free_tmp(t_token *tmp)
{
	if (tmp)
	{
		free(tmp->content);
		free(tmp);
	}
}

int	to_link_redir(int *i, char *str, t_token **token, t_token **link)
{
	int		is_link;
	t_token	*tmp;

	tmp = *token;
	is_link = 0;
	if (*i != 0 && str[0] != '\0')
		*token = create_token(str, *token, 0);
	if (*link && *i != 0 && str[0] != '\0')
	{
		is_link = 1;
		(*link)->next = *token;
	}
	if (str)
		free(str);
	return (is_link);
}

t_token	*create_more_token(t_token *token, t_token *link)
{
	int	i;
	int	start;

	i = 0;
	start = 0;
	while (token->content[i])
	{
		if (token->content[i] == '<')
		{
			token = token_loop_in(token, &i, &start, &link);
			if (!token)
				return (NULL);
		}
		else if (token->content[i] == '>')
		{
			token = token_loop_out(token, &i, &start, &link);
			if (!token)
				return (NULL);
		}
		else if (token->content[i] == '|')
			token = token_loop_pipe(token, &i, &start, &link);
		else
			i++;
	}
	return (token);
}

t_token	*check_token(t_token *token, t_token *link)
{
	t_token	*new;

	if (token->type != 0)
		return (token);
	if ((ft_strchr(token->content, '<') != NULL || (ft_strchr(token->content,
					'>') != NULL) || (ft_strchr(token->content, '|') != NULL))
		&& token->quote == 0)
		new = create_more_token(token, link);
	else
		return (token);
	if (!new)
		return (NULL);
	new = new->next;
	free(token->content);
	free(token);
	return (new);
}
