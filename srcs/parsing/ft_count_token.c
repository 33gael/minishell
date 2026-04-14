/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thbosvie <marvin@d42.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/08 14:58:26 by thbosvie          #+#    #+#             */
/*   Updated: 2026/04/08 14:59:36 by thbosvie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	count_quote(char to_check, char another_check, int *quote)
{
	int	size;

	size = 0;
	if (to_check == '\'' && *quote == 0)
	{
		*quote = 1;
		if (another_check && (another_check == ' ' || another_check == '\t'))
			size++;
	}
	else if (to_check == '\'' && *quote == 1)
		*quote = 0;
	if (to_check == '"' && *quote == 0)
	{
		*quote = 2;
		if (another_check && (another_check == ' ' || another_check == '\t'))
			size++;
	}
	else if (to_check == '"' && *quote == 2)
		*quote = 0;
	return (size);
}

static int	count_operator(char *input, int i, int quote)
{
	int	count;
	int	size;

	size = 0;
	count = 0;
	if (is_operator(input[i]) && quote == 0)
		count = 1;
	if (count == 1)
	{
		if (input[i + 1] && (input[i + 1] == '\0' || input[i + 1] == ' '
				|| input[i + 1] == '\t'))
			size++;
		else
			size += 2;
		if (i != 0 && (input[i - 1] == ' ' || input[i - 1] == '\t'))
			size--;
		count = 0;
	}
	return (size);
}

static int	count_space(char *input, int *i, int quote)
{
	int	size;

	size = 0;
	if ((input[*i] == ' ' || input[*i] == '\t') && quote == 0)
	{
		while (input[*i] == ' ' || input[*i] == '\t')
			*i += 1;
		if (input[*i] != '\0' && input[*i] != '\'' && input[*i] != '"'
			&& (input[*i] != ' ' && input[*i] != '\t'))
			size++;
	}
	return (size);
}

void	quote_error(int *size)
{
	*size = -1;
	ft_putstr_fd("syntax error: unclosed quote\n", 2);
	g_signal = 2;
}

int	ft_count_token(char *input)
{
	int	i;
	int	size;
	int	quote;

	size = 0;
	if (input[0] != ' ' && input[0] != '\t')
		size = 1;
	quote = 0;
	i = 0;
	while (input[i])
	{
		size += count_space(input, &i, quote);
		if (i != 0)
			size += count_quote(input[i], input[i - 1], &quote);
		else
			size += count_quote(input[i], input[i], &quote);
		size += count_operator(input, i, quote);
		if (input[i])
			i++;
	}
	if (quote != 0)
		quote_error(&size);
	return (size);
}
