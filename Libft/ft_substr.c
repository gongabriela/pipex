/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggoncalv <ggoncalv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 15:55:10 by ggoncalv          #+#    #+#             */
/*   Updated: 2024/10/31 18:09:24 by ggoncalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char				*substring;
	size_t				s_size;
	size_t				i;

	s_size = ft_strlen(s);
	if (!s)
		return (NULL);
	if (s_size <= start)
		return (ft_strdup(""));
	else if (start + len > s_size)
		len = s_size - start;
	substring = (char *)malloc((len + 1) * sizeof(char));
	if (substring == NULL)
		return (NULL);
	i = 0;
	while (i < len)
		substring[i++] = s[start++];
	substring[i] = '\0';
	return (substring);
}
