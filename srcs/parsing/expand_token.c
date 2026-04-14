/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_token.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeducas <gaeducas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/01 13:15:30 by thbosvie          #+#    #+#             */
/*   Updated: 2026/04/06 18:12:51 by gaeducas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*join_first_expand(char *input, int i, char *env_value)
{
	char	*tmp;
	char	*str;
	char	*join;
	char	*result;

	tmp = NULL;
	str = ft_substr(input, 0, i - 1);
	join = ft_substr(input, i + size_expand(input, i), ft_strlen(input) - i);
	if (!env_value)
		result = ft_strjoin(str, join);
	else
	{
		tmp = ft_strjoin(str, env_value);
		result = ft_strjoin(tmp, join);
	}
	free_expand(str, tmp, join);
	return (result);
}

static char	*first_expand_token(char *input, t_shell *shell, int i)
{
	char	*tmp;
	char	*result;
	char	*env_value;

	if (size_expand(input, i) == 0)
		env_value = ft_strdup("$");
	else
	{
		tmp = ft_substr(input, i, size_expand(input, i));
		env_value = ft_get_env(shell->env, tmp);
		free(tmp);
	}
	result = join_first_expand(input, i, env_value);
	if (env_value)
		free(env_value);
	return (result);
}

static char	*join_other_expand(char *input, int i, char *join, char *env_value)
{
	char	*str2;
	char	*str;
	char	*result;
	char	*tmp;

	tmp = NULL;
	str2 = ft_substr(input, i + size_expand(input, i), ft_strlen(input) - i);
	str = ft_substr(join, 0, ft_strlen(join) - ft_strlen(str2)
			- size_expand(input, i) - 1);
	if (!env_value)
		result = ft_strjoin(str, str2);
	else
	{
		tmp = ft_strjoin(str, env_value);
		result = ft_strjoin(tmp, str2);
	}
	free_expand(str, tmp, str2);
	return (result);
}

static char	*other_expand_token(char *input, char *join, int i, t_shell *shell)
{
	char	*tmp;
	char	*result;
	char	*env_value;

	if (size_expand(input, i) == 0)
		env_value = ft_strdup("$");
	else
	{
		tmp = ft_substr(input, i, size_expand(input, i));
		env_value = ft_get_env(shell->env, tmp);
		free(tmp);
	}
	result = join_other_expand(input, i, join, env_value);
	if (env_value)
		free(env_value);
	free(join);
	return (result);
}

char	*expand_token(char *input, t_shell *shell)
{
	int		i;
	char	*join;

	i = 0;
	join = NULL;
	while (input[i])
	{
		if (input[i] == '$' && join)
		{
			i++;
			join = other_expand_token(input, join, i, shell);
		}
		else if (input[i] == '$')
		{
			i++;
			join = first_expand_token(input, shell, i);
		}
		if (input[i])
			i++;
	}
	if (input)
		free(input);
	return (join);
}
