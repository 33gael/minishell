/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quotes_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thbosvie <marvin@d42.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 18:30:17 by thbosvie          #+#    #+#             */
/*   Updated: 2026/04/03 11:54:19 by thbosvie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_operator(char to_check)
{
	if (to_check == '>' || to_check == '<' || to_check == '|')
		return (1);
	return (0);
}

int	quote_switch(int quote, char to_check)
{
	if (to_check == '\'' && quote == 0)
		quote = 1;
	else if (to_check == '\'' && quote == 1)
		quote = 0;
	else if (to_check == '"' && quote == 0)
		quote = 2;
	else if (to_check == '"' && quote == 2)
		quote = 0;
	return (quote);
}

static int	check_quotes_size(char *input, int i)
{
	int	quote;
	int	size;

	size = 0;
	quote = 0;
	while (input[i] && (input[i] != ' ' || input[i] != '\t' || quote != 0)
		&& (!is_operator(input[i]) || quote != 0))
	{
		if ((input[i] == '\'' && (quote == 0 || quote == 1)) || (input[i] == '"'
				&& (quote == 0 || quote == 2)))
			quote = quote_switch(quote, input[i]);
		else if (((quote == 0 && (input[i] != ' ' || input[i] != '\t'))
				|| (quote == 1 && input[i] != '\'') || (quote == 2
					&& input[i] != '"')))
			size++;
		i += 1;
	}
	return (size);
}

char	*init_str_quotes(char *input, int i)
{
	int		size;
	char	*str;

	size = check_quotes_size(input, i);
	str = malloc(sizeof(char) * (size + 1));
	str[0] = '\0';
	return (str);
}

int	first_occurence(char *str, char c, char other_check)
{
	int	i;

	i = 0;
	while (str[i] && (str[i] != c && str[i] != other_check))
		i++;
	return (i);
}
