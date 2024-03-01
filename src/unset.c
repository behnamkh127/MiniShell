/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfeshara <mfeshara@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 15:24:50 by bekhodad          #+#    #+#             */
/*   Updated: 2024/01/24 15:25:19 by mfeshara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	unset(t_mini **mini, int i)
{
	while ((*mini)->args[i])
	{
		find_del_var(mini, ft_strdup((*mini)->args[i]));
		find_del_env(&(*mini)->env, ft_strdup((*mini)->args[i]));
		find_del_exp(&(*mini)->export, ft_strdup((*mini)->args[i]));
		i++;
	}
}

void	find_del_var(t_mini **mini, char *str)
{
	t_variable	*current;
	t_variable	*previous;
	char		*aux;

	aux = quat_handle(str, 0);
	current = (*mini)->var;
	while (current)
	{
		if (ft_strcmp(aux, current->name) == 0)
		{
			if (current == (*mini)->var)
				(*mini)->var = current->next;
			else
				previous->next = current->next;
			free (current->name);
			free (current->value);
			free (current);
			break ;
		}
		previous = current;
		current = current->next;
	}
	free (aux);
}

void	find_del_env(t_node **root, char *str)
{
	t_node	*current;
	t_node	*previous;
	char	*aux;
	char	*temp;

	aux = quat_handle(str, 0);
	temp = ft_strjoin(aux, "=");
	current = *root;
	while (current)
	{
		if (ft_strncmp(temp, current->str, ft_strlen(temp)) == 0)
		{
			if (current == *root)
				*root = current->next;
			else
				previous->next = current->next;
			free (current->str);
			free (current);
			break ;
		}
		previous = current;
		current = current->next;
	}
	free (aux);
	free (temp);
}

void	find_del_exp(t_node **root, char *str)
{
	t_node	*current;
	t_node	*previous;
	char	*aux;

	aux = quat_handle(str, 0);
	current = *root;
	while (current)
	{
		if (ft_strcmp(current->str, aux) == 0)
		{
			if (current == *root)
				*root = current->next;
			else
				previous->next = current->next;
			free (current->str);
			free (current);
			break ;
		}
		previous = current;
		current = current->next;
	}
	free (aux);
}
