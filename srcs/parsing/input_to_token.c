/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_to_token.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeducas <gaeducas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/22 16:01:41 by thbosvie          #+#    #+#             */
/*   Updated: 2026/04/08 14:59:27 by thbosvie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**init_strs_token(char *input, int *size)
{
	char	**strs;

	*size = ft_count_token(input) + 1;
	if (*size == 0)
		return (NULL);
	strs = malloc(sizeof(char *) * (*size));
	if (!strs)
		return (NULL);
	return (strs);
}

char	**input_to_token(char *input, int *size, t_shell *shell)
{
	char	**strs;
	int		i;
	int		j;
	int		current_j;

	j = 0;
	i = 0;
	strs = init_strs_token(input, size);
	if (!strs)
		return (NULL);
	while (input[i])
	{
		if (input[i] == ' ' || input[i] == '\t')
			i++;
		else
		{
			current_j = j;
			if (input[i] == '\'' || input[i] == '"')
				strs[current_j] = handle_quotes(input, &i, &j, shell);
			else
				strs[current_j] = without_quotes(input, &i, &j, shell);
		}
	}
	strs[j] = NULL;
	return (strs);
}
