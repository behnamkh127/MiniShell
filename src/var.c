/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bekhodad <bekhodad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 10:35:10 by bekhodad          #+#    #+#             */
/*   Updated: 2024/02/08 16:52:39 by bekhodad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	var(t_mini	**mini)
{
	char		**arr;
	char		**args;

	args = ft_split((*mini)->line, ' ');
	if ((args) && args[0])
	{
		if ((ft_strchr(args[0], '=')) && (ft_isalpha(args[0][0])))
		{
			arr = ft_split(args[0], '=');
			if (update_var(mini, arr) == 0)
				add_node(mini, arr);
			creat_line(mini, args);
			free_array(args);
			var(mini);
		}
		else
			free_array(args);
	}
	else
	{
		free((*mini)->line);
		read_prompt(mini);
	}
}

int	update_var(t_mini **mini, char **arr)
{
	t_variable	*temp;

	temp = (*mini)->var;
	while (temp)
	{
		if (ft_strcmp(temp->name, arr[0]) == 0)
		{
			free (temp->value);
			temp->value = ft_strdup(arr[1]);
			return (1);
		}
		temp = temp->next;
	}
	return (0);
}

void	add_node(t_mini **mini, char **arr)
{
	t_variable	*new;
	t_variable	*temp;

	temp = (*mini)->var;
	new = (t_variable *)malloc (sizeof(t_variable));
	if (!new)
	{
		(*mini)->error = 1;
		ft_putendl_fd("Alocating error", 2);
	}
	new->name = ft_strdup(arr[0]);
	if (arr[1])
		new->value = ft_strdup(arr[1]);
	else
		new->value = ft_strdup("");
	new->shlvl = (*mini)->shlvl;
	new->next = NULL;
	if (temp)
	{
		while (temp->next)
			temp = temp->next;
		temp->next = new;
	}
	else
		(*mini)->var = new;
}

void	creat_line(t_mini **mini, char **args)
{
	char	*temp;
	char	*new_line;
	int		len;

	len = ft_strlen(args[0]) + 1;
	temp = (*mini)->line;
	new_line = ft_strtrim(temp, " \t\r\v");
	(*mini)->line = ft_substr(new_line, len, ft_strlen(new_line));
	free (temp);
	free (new_line);
}
