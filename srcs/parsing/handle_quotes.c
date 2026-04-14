/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeducas <gaeducas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/22 16:00:41 by thbosvie          #+#    #+#             */
/*   Updated: 2026/04/08 21:43:33 by thbosvie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*operator_with_quote(char *input, int *i, int *j)
{
	char	*str;
	int		x;
	int		size;

	str = NULL;
	x = 0;
	size = 0;
	while (is_operator(input[*i + size]))
		size++;
	str = malloc(sizeof(char) * (size + 1));
	while (x < size)
	{
		str[x] = input[*i];
		*i += 1;
		x++;
	}
	str[x] = '\0';
	*j += 1;
	return (str);
}

static char	*check_quotes(char *input, int *i, int *j, t_shell *shell)
{
	int		x;
	char	*str;
	int		quote;

	x = *i;
	quote = 0;
	while (input[x] && (input[x] != ' ' && input[x] != '\t'))
	{
		if (input[x] == '\'' || input[x] == '"')
			quote = 1;
		x++;
	}
	if (quote == 1 && is_operator(input[*i]))
	{
		str = operator_with_quote(input, i, j);
		return (str);
	}
	else if (quote == 1)
	{
		str = handle_quotes(input, i, j, shell);
		return (str);
	}
	return (NULL);
}

int	quote_result(char to_check, int quote, int x, char *str)
{
	if (((quote == 0 && (to_check != ' ' && to_check != '\t')) || (quote == 1
				&& to_check != '\'') || (quote == 2 && to_check != '"')))
	{
		str[x] = to_check;
		x++;
	}
	return (x);
}

char	*handle_quotes(char *input, int *i, int *j, t_shell *shell)
{
	char	*str;
	int		x;

	shell->quote = 0;
	x = 0;
	str = init_str_quotes(input, *i);
	while (input[*i] && ((input[*i] != ' ' && input[*i] != '\t')
			|| shell->quote != 0) && (!is_operator(input[*i])
			|| shell->quote != 0))
	{
		if ((input[*i] == '\'' && (shell->quote == 0 || shell->quote == 1))
			|| (input[*i] == '"' && (shell->quote == 0
					|| shell->quote == 2)))
			shell->quote = quote_switch(shell->quote, input[*i]);
		else if (input[*i] == '$' && shell->quote != 1 && can_expand(input[*i
					+ 1]))
			x = expand_in_quote(input, &str, i, shell);
		else
			x = quote_result(input[*i], shell->quote, x, str);
		*i += 1;
		str[x] = '\0';
	}
	*j += 1;
	return (str);
}

char	*without_quotes(char *input, int *i, int *j, t_shell *shell)
{
	int		x;
	char	*str;
	int		size;

	x = 0;
	str = check_quotes(input, i, j, shell);
	if (str)
		return (str);
	size = first_occurence(input + *i, ' ', '\t') + 2;
	str = malloc(sizeof(char) * size);
	while (input[*i] && x < size - 2)
	{
		str[x] = input[*i];
		x++;
		*i += 1;
	}
	str[x] = '\0';
	*j += 1;
	return (str);
}
