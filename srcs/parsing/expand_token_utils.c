/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_token_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeducas <gaeducas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/01 13:15:12 by thbosvie          #+#    #+#             */
/*   Updated: 2026/04/10 11:00:23 by gaeducas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_expand(char *str, char *tmp, char *join)
{
	if (str)
		free(str);
	if (tmp)
		free(tmp);
	if (join)
		free(join);
}

int	size_expand(char *input, int i)
{
	int	size;

	size = 0;
	if (input[i] == '?')
		size++;
	while (input[i + size] == '_' || ft_isalnum(input[i + size]))
		size++;
	return (size);
}

int	check_dollar(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
			return (1);
		i++;
	}
	return (0);
}

t_token	*check_expand_token(t_token *token, t_shell *shell)
{
	t_token	*first;

	first = token;
	while (token)
	{
		if (token->quote == 0 && token->type == WORD
			&& check_dollar(token->content))
			token->content = expand_token(token->content, shell);
		else if (token->next && token->type == HEREDOC
			&& check_dollar(token->next->content))
			token = token->next;
		else if (token->next && token->type != WORD && token->type != PIPE
			&& token->type != HEREDOC && token->next->type == WORD
			&& check_dollar(token->next->content) && token->next->content[1])
		{
			ft_putstr_fd("Ambigus redirect\n", 2);
			g_signal = 2;
			free_token(first);
			return (NULL);
		}
		token = token->next;
	}
	return (first);
}
