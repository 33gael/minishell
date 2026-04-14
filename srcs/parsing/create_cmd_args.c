/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_cmd_args.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeducas <gaeducas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/01 18:20:07 by thbosvie          #+#    #+#             */
/*   Updated: 2026/04/07 18:29:01 by thbosvie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	count_args_expand(char *to_check)
{
	int	size;
	int	i;

	size = 0;
	i = 0;
	while (to_check[i])
	{
		if (to_check[i] == ' ' || to_check[i] == '\t')
			size++;
		i++;
	}
	return (size + 1);
}

int	check_space_tab(char *to_check)
{
	int	i;

	i = 0;
	while (to_check[i])
	{
		if (to_check[i] == ' ' || to_check[i] == '\t')
			return (1);
		i++;
	}
	return (0);
}

char	**cmd_args_init(t_token *token)
{
	char	**args;
	int		size;

	size = 0;
	if (token->next && token->type == PIPE)
		token = token->next;
	while (token && (token)->type != PIPE)
	{
		if (token->type == WORD && check_space_tab(token->content)
			&& token->quote == 0)
			size += count_args_expand(token->content);
		else if (token->type != WORD && token->next->type == WORD)
			size--;
		else if (token->type == WORD)
			size++;
		(token) = (token)->next;
	}
	args = ft_calloc(size + 1, sizeof(char *));
	return (args);
}

char	*create_cmd_arg(t_token **token, int *i)
{
	char	*arg;

	arg = NULL;
	if ((*token)->type == WORD)
	{
		arg = ft_strdup((*token)->content);
		(*token) = (*token)->next;
		*i += 1;
	}
	return (arg);
}

char	**create_cmd_expand(t_token **token, int *i, char **args)
{
	char	**tmp;
	int		j;

	j = 0;
	*i += 1;
	tmp = ft_split_mod((*token)->content, ' ', '\t');
	while (tmp[j])
	{
		args[*i] = ft_strdup(tmp[j]);
		j++;
		*i += 1;
	}
	free_array(tmp);
	(*token) = (*token)->next;
	*i -= 1;
	return (args);
}
