/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeducas <gaeducas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 16:54:16 by gaeducas          #+#    #+#             */
/*   Updated: 2025/10/24 16:24:01 by gaeducas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*dst;
	unsigned char	*source;

	if (!src && !dest)
		return (NULL);
	dst = (unsigned char *)dest;
	source = (unsigned char *)src;
	i = 0;
	while (i != n)
	{
		dst[i] = source[i];
		i++;
	}
	return (dest);
}
