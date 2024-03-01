/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bultins.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bekhodad <bekhodad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 18:43:51 by bekhodad          #+#    #+#             */
/*   Updated: 2024/02/08 11:33:54 by bekhodad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	bultins(t_mini **mini, int i)
{
	char	*arg;

	arg = ft_strdup((*mini)->args[0]);
	arg = quat_handle(arg, 0);
	if (ft_strcmp(make_small(arg), "echo") == 0)
		echo(mini, 0);
	else if (ft_strcmp(make_small(arg), "cd") == 0)
		cd(mini);
	else if (ft_strcmp(make_small(arg), "pwd") == 0)
		printf("%s\n", (*mini)->pwd);
	else if (ft_strcmp(arg, "export") == 0)
		export(mini);
	else if (ft_strcmp(make_small(arg), "env") == 0)
		print_env(mini, i);
	else if (ft_strcmp(arg, "./minishell") == 0)
		(*mini)->shlvl++;
	else if (ft_strcmp(arg, "unset") == 0)
		unset(mini, 1);
	else
		exec(mini);
}

void	mini_bultins(t_mini **mini, char *temp)
{
	(*mini)->args = ft_split(temp, ' ');
	if (ft_strcmp(temp, "./minishell") == 0)
	{
		(*mini)->shlvl += 1;
		update_env(mini);
		back_to_top(mini, temp);
	}
	else if (ft_strncmp(temp, "unset", 5) == 0)
	{
		unset(mini, 1);
		back_to_top(mini, temp);
	}
	else if ((ft_strncmp(temp, "export", 6) == 0) && ((*mini)->args[1]))
	{
		export_var(mini);
		update_env(mini);
		back_to_top(mini, temp);
	}
	else if (ft_strncmp(make_small(temp), "cd", 2) == 0)
	{
		cd(mini);
		back_to_top(mini, temp);
	}
	free(temp);
	free_array((*mini)->args);
}

void	back_to_top(t_mini **mini, char *temp)
{
	free(temp);
	free_array((*mini)->args);
	read_prompt(mini);
}
