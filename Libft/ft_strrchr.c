/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggoncalv <ggoncalv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 16:17:25 by ggoncalv          #+#    #+#             */
/*   Updated: 2024/11/14 17:30:53 by ggoncalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	chr;
	int		i;

	chr = (char)c;
	i = 0;
	while (s[i] != '\0')
		i++;
	if (s[i] == chr)
		return ((char *)&s[i]);
	while (i >= 0)
	{
		if (chr == s[i])
			return ((char *)&s[i]);
		i--;
	}
	return (NULL);
}
