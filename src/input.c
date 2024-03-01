/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bekhodad <bekhodad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 11:53:30 by bekhodad          #+#    #+#             */
/*   Updated: 2024/02/08 11:37:51 by bekhodad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	change_input(t_mini **mini, int i)
{
	int		j;
	int		sign;
	char	*file_name;
	int		start;

	sign = 0;
	start = i - 1;
	if ((*mini)->line[i] == '>')
		sign = i++;
	while (is_space((*mini)->line[i]) && (*mini)->line[i])
		i++;
	j = i;
	while ((*mini)->line[j] && !is_space((*mini)->line[j]))
		j++;
	file_name = ft_substr((*mini)->line, i, (j - i));
	open_file(mini, file_name, sign);
	(*mini)->infile = file_name;
	while (start <= j)
		(*mini)->line[start++] = ' ';
}

void	open_file(t_mini **mini, char *file_name, int sign)
{
	if ((*mini)->fd_input)
		close ((*mini)->fd_input);
	if (sign == 0)
		(*mini)->fd_input = open(file_name, O_RDONLY);
	else
		(*mini)->fd_input = open(file_name, O_CREAT | O_RDONLY);
	if ((*mini)->fd_input == -1)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(file_name, 2);
		if (access(file_name, F_OK) == 0 && access(file_name, R_OK))
			ft_putendl_fd(": Permission denied.", 2);
		else
			ft_putendl_fd(": No such file or directory", 2);
		(*mini)->error = 1;
		free (file_name);
		free ((*mini)->line);
		(*mini)->line = NULL;
		read_prompt(mini);
	}
	(*mini)->std_in = dup(0);
	dup2((*mini)->fd_input, STDIN_FILENO);
	close ((*mini)->fd_input);
}

int	skip_quat(char *str, int i)
{
	if (str[i] == 34)
	{
		i++;
		while (str[i] != 34 && str[i])
			i++;
		i++;
	}
	if (str[i] == 39)
	{
		i++;
		while (str[i] != 39 && str[i])
			i++;
		i++;
	}
	return (i);
}

char	*skip_quat2(char *line)
{
	if (*line == 34)
	{
		line++;
		while (*line != 34)
			line++;
		line++;
	}
	if (*line == 39)
	{
		line++;
		while (*line != 39)
			line++;
		line++;
	}
	return (line);
}
