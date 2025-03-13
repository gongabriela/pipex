/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggoncalv <ggoncalv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 12:08:42 by ggoncalv          #+#    #+#             */
/*   Updated: 2024/11/04 14:40:43 by ggoncalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	h;
	size_t	n;

	if (little[0] == '\0')
		return ((char *)big);
	h = 0;
	while (big[h] != '\0' && h < len)
	{
		n = 0;
		while (big[h + n] == little[n] && big[h + n] != '\0'
			&& h + n < len)
		{
			n++;
			if (little[n] == '\0')
				return ((char *)big + h);
		}
		h++;
	}
	return (NULL);
}
