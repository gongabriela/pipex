/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggoncalv <ggoncalv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 16:04:38 by ggoncalv          #+#    #+#             */
/*   Updated: 2024/11/13 18:24:03 by ggoncalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	i;
	size_t	k;
	size_t	j;

	i = 0;
	j = 0;
	while (set[j] != '\0')
	{
		j = 0;
		while (s1[i] != set[j] && set[j] != '\0')
			j++;
		if (s1[i] == set[j])
			i++;
	}
	k = ft_strlen(s1) - 1;
	j = 0;
	while (set[j] != '\0')
	{
		j = 0;
		while (s1[k] != set[j] && set[j] != '\0')
			j++;
		if (s1[k] == set[j])
			k--;
	}
	return (ft_substr(s1, i, k - i + 1));
}
