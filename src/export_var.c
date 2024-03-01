/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bekhodad <bekhodad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 12:45:03 by bekhodad          #+#    #+#             */
/*   Updated: 2024/02/08 16:49:04 by bekhodad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	export_var(t_mini **mini)
{
	int			i;
	char		**arr;

	i = 1;
	while ((*mini)->args[i])
	{
		if (ft_isalpha((int)(*mini)->args[i][0]) == 0)
		{
			ft_putstr_fd("minishell: export: `", 2);
			ft_putstr_fd((*mini)->args[i], 2);
			ft_putendl_fd("': not a valid identifier", 2);
			(*mini)->error = 1;
		}
		else if (ft_strchr((*mini)->args[i], '='))
		{
			arr = ft_split((*mini)->args[i], '=');
			find_in_var(mini, arr);
			if (find_in_env(mini, arr[0], i))
				env_add(mini, &(*mini)->env, ft_strdup((*mini)->args[i]));
			free_array(arr);
		}
		else
			add_to_env(mini, i);
		i++;
	}
}

void	find_in_var(t_mini **mini, char **arr)
{
	t_variable	*temp;

	temp = (*mini)->var;
	while (temp)
	{
		if (ft_strcmp(temp->name, arr[0]) == 0)
		{
			free (temp->value);
			if (arr[1])
				temp->value = ft_strdup(arr[1]);
			else
				temp->value = ft_strdup("");
			return ;
		}
		temp = temp->next;
	}
	add_node(mini, arr);
}

int	find_in_env(t_mini **mini, char *str, int i)
{
	t_node	*temp;
	char	*aux;

	aux = ft_strjoin(str, "=");
	temp = (*mini)->env;
	while (temp)
	{
		if (ft_strncmp(aux, temp->str, ft_strlen(aux)) == 0)
		{
			free (temp->str);
			temp->str = ft_strdup((*mini)->args[i]);
			free (aux);
			return (0);
		}
		temp = temp->next;
	}
	free (aux);
	return (1);
}

void	add_to_env(t_mini **mini, int i)
{
	t_variable	*temp;
	int			exist;
	char		*str;
	char		*str2;

	exist = 0;
	temp = (*mini)->var;
	while (temp)
	{
		if (ft_strcmp(temp->name, (*mini)->args[i]) == 0)
		{
			exist++;
			break ;
		}
		temp = temp->next;
	}
	if (exist != 0 && check_env(mini, (*mini)->args[i]))
	{
		str = ft_strjoin(temp->name, "=");
		str2 = ft_strjoin(str, temp->value);
		env_add(mini, &(*mini)->env, ft_strdup(str2));
		test_break(&str, &str2);
	}
	else if (check_env(mini, (*mini)->args[i]))
		add_sorted(mini, &(*mini)->export, ft_strdup((*mini)->args[i]));
}

int	check_env(t_mini **mini, char *str)
{
	t_node	*temp;
	char	*aux;

	aux = ft_strjoin(str, "=");
	temp = (*mini)->env;
	while (temp)
	{
		if (ft_strncmp(aux, temp->str, ft_strlen(aux)) == 0)
			return (0);
		temp = temp->next;
	}
	free (aux);
	return (1);
}
