/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfeshara <mfeshara@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 10:47:39 by mfeshara          #+#    #+#             */
/*   Updated: 2024/01/31 17:24:45 by mfeshara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	export(t_mini **mini)
{
	t_node	*exp;
	t_node	*temp;
	int		sign;

	update_env(mini);
	exp = NULL;
	sign = 0;
	temp = (*mini)->env;
	while (temp)
	{
		if (ft_strncmp(temp->str, "OLDPWD", 6) == 0)
			sign += 1;
		init_export(mini, temp->str, &exp, 0);
		temp = temp->next;
	}
	temp = (*mini)->export;
	while (temp)
	{
		init_export(mini, temp->str, &exp, 0);
		temp = temp->next;
	}
	if (sign == 0)
		add_sorted(mini, &exp, ft_strdup("declare -x OLDPWD"));
	print_exp(&exp);
}

void	init_export(t_mini **mini, char *env, t_node **exp, int sign)
{
	char	*str;
	char	*temp;
	int		i;
	int		j;

	i = 0;
	j = 0;
	temp = ft_strjoin("declare -x ", env);
	str = (char *)malloc(sizeof(char) * ft_strlen(temp) + 3);
	while (temp[i])
	{
		str[j] = temp[i];
		if (temp[i] == 61)
		{
			sign = 1;
			str[++j] = 34;
		}
		i++;
		j++;
	}
	if (sign == 1)
		str[j++] = 34;
	str[j] = '\0';
	free (temp);
	add_sorted(mini, exp, str);
}

void	print_exp(t_node **exp)
{
	t_node	*temp;
	t_node	*curr;

	curr = *exp;
	temp = NULL;
	while (curr)
	{
		temp = curr;
		printf("%s\n", curr->str);
		curr = curr->next;
		free (temp->str);
		free (temp);
	}
}

void	add_sorted(t_mini **mini, t_node **exp, char *str)
{
	t_node	*new;

	new = (t_node *)malloc(sizeof(t_node));
	if (!new)
		exit (10);
	new->str = str;
	new->shlvl = (*mini)->shlvl;
	new->next = NULL;
	if (*exp == NULL || ft_strcmp(new->str, (*exp)->str) < 0)
	{
		new->next = *exp;
		*exp = new;
	}
	else
		continue_add_sorted(new, exp);
}

void	continue_add_sorted(t_node *new, t_node **exp)
{
	t_node	*curr;

	curr = *exp;
	while (curr->next)
	{
		if (ft_strcmp(new->str, curr->next->str) < 0)
			break ;
		curr = curr->next;
	}
	new->next = curr->next;
	curr->next = new;
}
