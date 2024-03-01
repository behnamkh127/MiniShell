/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bekhodad <bekhodad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 12:09:12 by mfeshara          #+#    #+#             */
/*   Updated: 2024/02/08 11:58:25 by bekhodad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	is_space(char temp)
{
	if ((temp == ' ') || (temp == '\t') || (temp == '\v')
		|| (temp == '\n') || (temp == '\r'))
		return (1);
	return (0);
}

char	*make_small(char *arg)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		if (arg[i] >= 'A' && arg[i] <= 'Z')
			arg[i] += 32;
		i++;
	}
	return (arg);
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i])
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		i++;
	}
	return (s1[i] - s2[i]);
}
