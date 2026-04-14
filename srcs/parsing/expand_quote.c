/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_quote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeducas <gaeducas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/01 13:33:48 by thbosvie          #+#    #+#             */
/*   Updated: 2026/04/08 20:12:40 by thbosvie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	can_expand(char to_check)
{
	if (ft_isalnum(to_check) || to_check == '_' || to_check == '?')
		return (1);
	else
		return (0);
}

static int	size_before_expand(char *input, int i, int quote)
{
	int	size;

	size = 0;
	while (input[i] && ((input[i] != ' ' && input[i] != '\t') || quote != 0)
		&& (!is_operator(input[i]) || quote != 0))
	{
		if (input[i] == '\'' && quote == 0)
			quote = 1;
		else if (input[i] == '\'' && quote == 1)
			quote = 0;
		else if (input[i] == '"' && quote == 0)
			quote = 2;
		else if (input[i] == '"' && quote == 2)
			quote = 0;
		else if (((quote == 0 && input[i] != ' ' && input[i] != '\t')
				|| (quote == 1 && input[i] != '\'') || (quote == 2
					&& input[i] != '"')))
			size++;
		i += 1;
	}
	return (size);
}

static int	size_expand_quote(int size_before_expand, int size_result,
		int size_str, char *result)
{
	int	size;

	size = 0;
	if (result)
		size = size_before_expand + size_result + size_str;
	else
		size = size_before_expand + size_str;
	return (size);
}

static char	*get_result_expand(char *tmp, char *str, int size)
{
	int		j;
	char	*join;
	char	*result;

	result = malloc(sizeof(char) * (size + 1));
	join = ft_strjoin(str, tmp);
	j = 0;
	while (join[j])
	{
		result[j] = join[j];
		j++;
	}
	result[j] = '\0';
	free(join);
	free(str);
	return (result);
}

int	expand_in_quote(char *input, char **str, int *i, t_shell *shell)
{
	char	*result;
	int		size_result;
	int		size;
	int		tmp_size;
	char	*tmp;

	size_result = 0;
	*i += 1;
	tmp_size = size_expand(input, *i);
	tmp = ft_substr(input, *i, tmp_size);
	result = ft_get_env(shell->env, tmp);
	if (result)
		size_result = ft_strlen(result);
	size = size_expand_quote(size_before_expand(input, *i + ft_strlen(tmp),
				shell->quote), size_result, ft_strlen(*str), result);
	*i += tmp_size - 1;
	free(tmp);
	if (!result)
		return (ft_strlen(*str));
	*str = get_result_expand(result, *str, size);
	free(result);
	return (ft_strlen(*str));
}
