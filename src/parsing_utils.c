/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bekhodad <bekhodad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 12:03:26 by bekhodad          #+#    #+#             */
/*   Updated: 2024/02/08 17:04:02 by bekhodad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	free_args(t_node **args)
{
	t_node	*temp;
	t_node	*next_node;

	next_node = *args;
	while (next_node)
	{
		temp = next_node;
		next_node = next_node->next;
		free(temp->str);
		temp->str = NULL;
		free(temp);
		temp = NULL;
	}
	*args = NULL;
}

int	count_len(t_node **args)
{
	t_node	*temp;
	int		i;
	int		len;

	temp = *args;
	len = 0;
	i = 0;
	while (temp)
	{
		i = 0;
		while (temp->str[i++])
			len++;
		temp = temp->next;
		len++;
	}
	return (len);
}
