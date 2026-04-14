/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeducas <gaeducas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 11:58:29 by gaeducas          #+#    #+#             */
/*   Updated: 2025/10/17 12:33:28 by gaeducas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char	*destination;
	unsigned char	*source;

	if (!dest && !src)
		return (NULL);
	source = (unsigned char *)src;
	destination = (unsigned char *)dest;
	if (destination < source)
	{
		ft_memcpy(destination, source, n);
	}
	else
	{
		while (n-- > 0)
			destination[n] = source[n];
	}
	return (dest);
}
