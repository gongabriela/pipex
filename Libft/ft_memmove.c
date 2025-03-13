/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggoncalv <ggoncalv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 16:43:39 by ggoncalv          #+#    #+#             */
/*   Updated: 2024/11/13 17:06:48 by ggoncalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char	*s;
	unsigned char	*d;
	size_t			i;

	if (src == NULL && dest == NULL)
		return (NULL);
	s = (unsigned char *)src;
	d = (unsigned char *)dest;
	if (d > s)
	{
		s = s + n - 1;
		d = d + n - 1;
		while (n-- > 0)
			*d-- = *s--;
	}
	else
	{
		i = 0;
		while (i++ < n)
			*d++ = *s++;
	}
	return (dest);
}
