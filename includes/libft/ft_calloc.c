/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeducas <gaeducas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 14:54:30 by gaeducas          #+#    #+#             */
/*   Updated: 2025/10/20 22:09:43 by gaeducas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nbrs_elements, size_t size)
{
	void	*dest;

	if (nbrs_elements == 0 || size == 0)
	{
		dest = malloc(0);
		if (!dest)
			return (NULL);
		return (dest);
	}
	dest = malloc(nbrs_elements * size);
	if (!dest)
		return (NULL);
	if (nbrs_elements > (size_t)-1 / size)
		return (NULL);
	ft_bzero(dest, nbrs_elements * size);
	return (dest);
}
