/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_mod.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thbosvie <marvin@d42.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/05 11:24:28 by thbosvie          #+#    #+#             */
/*   Updated: 2026/04/05 11:35:30 by thbosvie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	count_words_mod(char const *s, char c, char other_c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		while (s[i] == c || s[i] == other_c)
			i++;
		if (s[i] != '\0')
			count++;
		while (s[i] && (s[i] != c && s[i] != other_c))
			i++;
	}
	return (count);
}

static void	*free_all(char **dest, int j)
{
	int	i;

	i = 0;
	while (i < j)
	{
		if (dest[i] == NULL)
		{
			while (j > 0)
			{
				j--;
				free(dest[j]);
			}
			free(dest);
			return (NULL);
		}
		i++;
	}
	return (dest);
}

char	**ft_split_mod(char const *s, char c, char other_c)
{
	char	**dest;
	int		i;
	int		j;

	j = 0;
	if (!s)
		return (NULL);
	dest = malloc(sizeof(char *) * (count_words_mod(s, c, other_c) + 1));
	if (!dest)
		return (NULL);
	while (*s)
	{
		i = 0;
		while (s[i] && (s[i] != c && s[i] != other_c))
			i++;
		if (i)
			dest[j++] = ft_substr(s, 0, i);
		while (s[i] && (s[i] == c || s[i] == other_c))
			i++;
		s += i;
	}
	dest[j] = NULL;
	dest = free_all(dest, j);
	return (dest);
}
