/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeducas <gaeducas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 13:05:57 by gaeducas          #+#    #+#             */
/*   Updated: 2025/10/24 16:19:18 by gaeducas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	lenght(long int n)
{
	int	len;

	len = 0;
	if (n == 0)
		return (2);
	if (n < 0)
	{
		len++;
		n = n * -1;
	}
	while (n > 0)
	{
		n = n / 10;
		len++;
	}
	return (len + 1);
}

char	*ft_itoa(int n)
{
	char		*str;
	int			len;
	long int	nb;

	nb = (long int)n;
	len = lenght(nb);
	str = malloc(len * sizeof(char));
	if (!str)
		return (NULL);
	if (nb == 0)
		str[0] = '0';
	if (nb < 0)
	{
		nb = nb * -1;
		str[0] = '-';
	}
	str[--len] = '\0';
	while (nb > 0)
	{
		str[--len] = '0' + (nb % 10);
		nb = nb / 10;
	}
	return (str);
}
