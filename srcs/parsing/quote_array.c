/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_array.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeducas <gaeducas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/01 13:21:37 by thbosvie          #+#    #+#             */
/*   Updated: 2026/04/08 19:09:35 by thbosvie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	*quote_array_init(int size)
{
	int	*quote_array;
	int	i;

	i = 0;
	quote_array = malloc(sizeof(int) * (size - 1));
	while (i < size - 1)
	{
		quote_array[i] = 0;
		i++;
	}
	return (quote_array);
}

static void	asigned_quote_array(char to_check, int **quote_array, int *j)
{
	if (to_check == '\'')
		(*quote_array)[*j] = 1;
	else
		(*quote_array)[*j] = 2;
}

static int	quote_array_loop(int i, int *j, int **quote_array, char *input)
{
	int	q_state;

	if (is_operator(input[i]))
		while (is_operator(input[i]))
			i++;
	else
	{
		q_state = 0;
		while (input[i] && ((input[i] != ' ' && input[i] != '\t')
				|| q_state != 0) && (!is_operator(input[i]) || q_state != 0))
		{
			if ((input[i] == '\'' && (q_state == 0 || q_state == 1))
				|| (input[i] == '"' && (q_state == 0 || q_state == 2)))
			{
				if ((*quote_array)[*j] == 0)
					asigned_quote_array(input[i], quote_array, j);
				q_state = quote_switch(q_state, input[i]);
			}
			i++;
		}
	}
	*j += 1;
	return (i);
}

int	*quote_array_create(char *input, int size)
{
	int	i;
	int	j;
	int	*quote_array;

	i = 0;
	j = 0;
	quote_array = quote_array_init(size);
	while (input[i])
	{
		if (input[i] == ' ' || input[i] == '\t')
			i++;
		else
			i = quote_array_loop(i, &j, &quote_array, input);
	}
	return (quote_array);
}
