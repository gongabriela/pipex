/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggoncalv <ggoncalv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 16:30:53 by ggoncalv          #+#    #+#             */
/*   Updated: 2024/11/01 16:32:26 by ggoncalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*conc;

	conc = ft_calloc((ft_strlen(s1) + ft_strlen(s2) + 1), sizeof(char));
	if (conc == NULL)
		return (NULL);
	ft_strlcat(conc, s1, ft_strlen(s1) + ft_strlen(s2) + 1);
	ft_strlcat(conc, s2, ft_strlen(s1) + ft_strlen(s2) + 1);
	return (conc);
}
