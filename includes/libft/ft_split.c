/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeducas <gaeducas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 13:44:14 by gaeducas          #+#    #+#             */
/*   Updated: 2025/10/23 14:53:30 by gaeducas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_words(char const *s, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		if (s[i] != '\0')
			count++;
		while (s[i] != c && s[i])
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

char	**ft_split(char const *s, char c)
{
	char	**dest;
	int		i;
	int		j;

	j = 0;
	if (!s)
		return (NULL);
	dest = malloc(sizeof(char *) * (count_words(s, c) + 1));
	if (!dest)
		return (NULL);
	while (*s)
	{
		i = 0;
		while (s[i] != c && s[i])
			i++;
		if (i)
			dest[j++] = ft_substr(s, 0, i);
		while (s[i] == c && s[i])
			i++;
		s += i;
	}
	dest[j] = NULL;
	dest = free_all(dest, j);
	return (dest);
}
