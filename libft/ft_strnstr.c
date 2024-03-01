/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bekhodad <bekhodad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 15:17:39 by bekhodad          #+#    #+#             */
/*   Updated: 2023/06/09 15:17:39 by bekhodad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include <stdio.h>
#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;

	if (*little == '\0')
		return ((char *)big);
	i = ft_strlen(little);
	while (*big && i <= len)
	{
		if (*big == *little && ft_strncmp(big, little, i) == 0)
			return ((char *)big);
		++big;
		--len;
	}
	return (NULL);
}
