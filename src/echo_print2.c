/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_print2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bekhodad <bekhodad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 11:20:12 by bekhodad          #+#    #+#             */
/*   Updated: 2024/02/08 16:58:35 by bekhodad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	handle_n(t_echo **echo, char *line)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (j < (*echo)->sign_n)
	{
		while (is_space(line[i]) && line[i])
			i++;
		line[i++] = ' ';
		while (line[i] == 'n')
			line[i++] = ' ';
		j++;
	}
	(*echo)->str = ft_strtrim(line, " \t\r\v");
}

void	echo_quat(t_echo **echo, t_mini **mini)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while ((*echo)->str[i])
	{
		while ((*echo)->str[i] != 34 && (*echo)->str[i] != 39
			&& (*echo)->str[i] != '\0')
		{
			if ((*echo)->str[i] == 36)
			{
				i = case_sign2(echo, mini, i);
				break ;
			}
			printf("%c", (*echo)->str[i]);
			i++;
		}
		if ((*echo)->str[i] == 39)
			(*echo)->sign_quat = 1;
		else if ((*echo)->str[i] == 34)
			(*echo)->sign_double = 1;
		if (((*echo)->sign_quat == 1) || ((*echo)->sign_double == 1))
			i = echo_print(echo, mini, ++i);
	}
}

void	find_variable(char *str, t_mini **mini)
{
	t_variable	*temp;
	int			sign;

	sign = 0;
	temp = (*mini)->var;
	while (temp)
	{
		if (ft_strcmp(str, temp->name) == 0)
		{
			sign = 1;
			break ;
		}
		temp = temp->next;
	}
	if (sign)
		printf("%s", temp->value);
	else
		search_variable(str, mini);
}

void	search_variable(char *str, t_mini **mini)
{
	t_node	*temp;
	int		sign;

	sign = 0;
	temp = (*mini)->env;
	while (temp)
	{
		if (ft_strncmp(str, temp->str, ft_strlen(str)) == 0)
		{
			sign = 1;
			break ;
		}
		temp = temp->next;
	}
	if (sign)
		printf("%s", (ft_strchr(temp->str, '=') + 1));
}
