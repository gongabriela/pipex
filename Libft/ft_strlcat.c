/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggoncalv <ggoncalv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 14:19:54 by ggoncalv          #+#    #+#             */
/*   Updated: 2024/11/13 17:13:21 by ggoncalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	src_length;
	size_t	dst_length;

	src_length = ft_strlen(src);
	dst_length = ft_strlen(dst);
	i = dstsize - dst_length - 1;
	if (dstsize <= dst_length)
		return (src_length + dstsize);
	dst = dst + dst_length;
	while (*src != '\0' && i > 0)
	{
		*dst++ = *src++;
		i--;
	}
	*dst = '\0';
	return (src_length + dst_length);
}
