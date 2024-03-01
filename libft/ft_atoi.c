/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bekhodad <bekhodad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 15:18:00 by bekhodad          #+#    #+#             */
/*   Updated: 2023/06/09 15:18:00 by bekhodad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_atoi(const char *nb)
{
	int	sign;
	int	result;

	sign = 1;
	result = 0;
	while (*nb == '\t' || *nb == '\n' || *nb == '\v' || *nb == '\f'
		|| *nb == '\r' || *nb == ' ')
		nb++;
	if (*nb == '-')
	{
		sign = -1;
		nb++;
	}
	else if (*nb == '+')
		nb++;
	while (*nb >= '0' && *nb <= '9')
	{
		result = result * 10 + (*nb - '0');
		nb++;
	}
	return (result * sign);
}
