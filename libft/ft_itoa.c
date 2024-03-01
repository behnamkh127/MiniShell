/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bekhodad <bekhodad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 16:18:46 by bekhodad          #+#    #+#             */
/*   Updated: 2023/06/09 16:18:46 by bekhodad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include <stdlib.h>
#include "libft.h"

int		num_len(int n);

char	*ft_itoa(int n)
{
	long	len;
	long	nl;
	char	*result;

	len = num_len(n);
	nl = n;
	if (n < 0)
		nl *= -1;
	result = malloc((len + 1) * sizeof(char));
	if (!result)
		return (NULL);
	result[len] = 0;
	if (nl == 0)
		result[0] = '0';
	else
	{
		while (len--, nl != 0)
		{
			result[len] = (nl % 10) + '0';
			nl = nl / 10;
		}
		if (n < 0)
			result[len] = '-';
	}
	return (result);
}

int	num_len(int n)
{
	int	len;

	len = 0;
	if (n == 0)
		return (1);
	if (n < 0)
		len++;
	while (n != 0)
	{
		n /= 10;
		len++;
	}
	return (len);
}
