/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bekhodad <bekhodad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 12:45:23 by bekhodad          #+#    #+#             */
/*   Updated: 2023/06/12 12:45:23 by bekhodad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include <stdio.h>
#include "libft.h"

void	*ft_memset(void *dest, int c, size_t n)
{
	size_t			i;
	unsigned char	*temp;

	i = 0;
	temp = dest;
	while (i < n)
	{
		temp[i] = (unsigned char) c;
		i++;
	}
	return (dest);
}
