/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bekhodad <bekhodad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 10:44:52 by bekhodad          #+#    #+#             */
/*   Updated: 2023/06/12 10:44:52 by bekhodad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include <stdio.h>
#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t				i;
	const unsigned char	*t1;
	const unsigned char	*t2;

	i = 0;
	t1 = s1;
	t2 = s2;
	while (i < n)
	{
		if (*t1 != *t2)
			return (*t1 - *t2);
		t1++;
		t2++;
		i++;
	}
	return (0);
}
