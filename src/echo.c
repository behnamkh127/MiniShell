/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bekhodad <bekhodad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/25 12:40:05 by mfeshara          #+#    #+#             */
/*   Updated: 2024/02/08 16:59:36 by bekhodad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	echo(t_mini **mini, int i)
{
	t_echo	*echo;
	int		j;

	echo = (t_echo *)malloc(sizeof(t_echo));
	if (!echo)
		free_echo(&echo, mini, "Allocating error", 1);
	init_struct(&echo);
	j = 1;
	while ((*mini)->args[j] && ft_strncmp((*mini)->args[j++], "-n", 2) == 0)
		echo->sign_n += 1;
	creat_str(&echo, mini, i);
	if (echo->str)
	{
		if (ft_strchr(echo->str, 34) || ft_strchr(echo->str, 39))
		{
			if (control_str(echo->str, 0) == -1)
				free_echo(&echo, mini, "minishell: Syntax error: quat", 1);
			echo_quat(&echo, mini);
		}
		else
			reg_print(&echo, mini);
	}
	if (echo->sign_n == 0)
		printf("\n");
	free_echo(&echo, mini, NULL, 0);
}

void	init_struct(t_echo **echo)
{
	(*echo)->sign_double = 0;
	(*echo)->sign_n = 0;
	(*echo)->sign_quat = 0;
	(*echo)->str = NULL;
}

void	creat_str(t_echo **echo, t_mini **mini, int i)
{
	char	*temp;
	int		j;

	temp = ft_strnstr((*mini)->line, "echo", ft_strlen((*mini)->line));
	while (temp[i])
	{
		i = skip_quat(temp, i);
		if (temp[i] == '|')
			break ;
		i++;
	}
	temp = ft_substr(temp, 0, i);
	if ((temp[4] == 34) || temp[4] == 39)
		temp[4] = ' ';
	i = 0;
	while (is_space(temp[i]) && temp[i])
		i++;
	j = 0;
	while (j++ < 5)
		temp[i++] = ' ';
	if ((*echo)->sign_n)
		handle_n(echo, temp);
	else
		(*echo)->str = ft_strtrim(temp, " \t\r\v");
	free (temp);
}

void	free_echo(t_echo **echo, t_mini **mini, char *err, int error)
{
	(*mini)->error = error;
	if ((*echo)->str)
	{
		free((*echo)->str);
		(*echo)->str = NULL;
	}
	if (*echo)
		free(*echo);
	if (err)
	{
		ft_putendl_fd(err, 2);
		exit (1);
	}
}

int	check_quats(char *str, int i)
{
	int	count_double;
	int	count_quat;

	count_double = 0;
	count_quat = 0;
	while (str[i])
	{
		if (str[i] == 39)
			count_quat++;
		if (str[i] == 34)
			count_double++;
		i++;
	}
	if ((count_double < 2 && (count_quat) % 2)
		|| (count_quat < 2 && (count_double) % 2))
		return (1);
	return (0);
}
