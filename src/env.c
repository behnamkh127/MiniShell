/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bekhodad <bekhodad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 16:05:23 by mfeshara          #+#    #+#             */
/*   Updated: 2024/02/07 15:44:35 by bekhodad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	env(t_mini **mini)
{
	t_node	*env;
	int		i;

	env = NULL;
	i = 0;
	while ((*mini)->envp[i])
	{
		if (ft_strncmp((*mini)->envp[i], "OLDPWD", 6) == 0
			|| ft_strncmp((*mini)->envp[i], "_", 1) == 0)
			i++;
		else if (ft_strncmp((*mini)->envp[i], "PWD", 3) == 0)
		{
			env_add(mini, &env, ft_strjoin("PWD=", (*mini)->pwd));
			i++;
		}
		else if (ft_strncmp((*mini)->envp[i], "SHLVL", 5) == 0)
		{
			env_add(mini, &env, ft_strjoin("SHLVL=", ft_itoa((*mini)->shlvl)));
			i++;
		}
		else
			env_add(mini, &env, ft_strdup((*mini)->envp[i++]));
	}
	(*mini)->env = env;
}

void	print_env(t_mini **mini, int i)
{
	t_node	*curr;
	char	*temp;

	curr = (*mini)->env;
	while (curr)
	{
		printf("%s\n", curr->str);
		curr = curr->next;
	}
	temp = ft_strtrim((*mini)->lines[i], " \t\v\r");
	temp = quat_handle(temp, 0);
	printf("_=/usr/bin/%s\n", temp);
	if (temp)
		free(temp);
}

void	env_add(t_mini **mini, t_node **env, char *str)
{
	t_node	*new_node;
	t_node	*curr;

	new_node = (t_node *)malloc(sizeof(t_node));
	if (!new_node)
	{
		(*mini)->error = 1;
		ft_putendl_fd("Allocating error", 2);
		exit (1);
	}
	new_node->str = str;
	new_node->shlvl = (*mini)->shlvl;
	new_node->next = NULL;
	if (!*env)
		*env = new_node;
	else
	{
		curr = *env;
		while (curr->next)
			curr = curr->next;
		curr->next = new_node;
	}
}

void	update_env(t_mini **mini)
{
	t_node	*temp;
	int		sign;

	temp = (*mini)->env;
	while (temp)
	{
		sign = check_need_change(temp, mini);
		temp = temp->next;
	}
	if (sign == 0)
		if ((*mini)->oldpwd)
			env_add(mini, &(*mini)->env,
				ft_strjoin("OLDPWD=", (*mini)->oldpwd));
}

int	check_need_change(t_node *temp, t_mini **mini)
{
	int	sign;

	sign = 0;
	if (ft_strncmp(temp->str, "PWD", 3) == 0)
	{
		free (temp->str);
		temp->str = ft_strjoin("PWD=", (*mini)->pwd);
	}
	if (ft_strncmp(temp->str, "SHLVL=", 6) == 0)
	{
		free (temp->str);
		temp->str = ft_strjoin("SHLVL=", ft_itoa((*mini)->shlvl));
	}
	if (ft_strncmp(temp->str, "OLDPWD", 6) == 0)
	{
		sign = 1;
		free (temp->str);
		temp->str = ft_strjoin("OLDPWD=", (*mini)->oldpwd);
	}
	return (sign);
}
