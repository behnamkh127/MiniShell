/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bekhodad <bekhodad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 10:39:31 by bekhodad          #+#    #+#             */
/*   Updated: 2023/06/12 10:39:31 by bekhodad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*string;
	unsigned char	a;

	i = 0;
	string = (unsigned char *) s;
	a = (unsigned char) c;
	while (i < n)
	{
		if (*string == a)
			return (string);
		string++;
		i++;
	}
	return (NULL);
}
