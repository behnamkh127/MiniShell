/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bekhodad <bekhodad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 11:01:33 by bekhodad          #+#    #+#             */
/*   Updated: 2024/02/07 19:08:21 by bekhodad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	change_output(t_mini **mini)
{
	char	*line;
	int		sign;
	char	*temp;

	sign = 0;
	line = ft_strdup((*mini)->line);
	temp = line;
	while (*line)
	{
		line = skip_quat2(line);
		if (*line == '>')
		{
			sign = 1;
			line = valid_line(mini, line, temp);
		}
		else
			line++;
	}
	if (sign != 0)
		edit_line(mini);
	free (temp);
}

char	*valid_line(t_mini **mini, char *line, char *temp)
{
	if (*(line + 1) == '>' && *(line + 2) != '>'
		&& (line + 1) && (line + 2))
	{
		line = append_output(mini, (line + 2), temp);
		(*mini)->out_sign = 2;
	}
	else if (*(line + 1) != '>' && (line + 1))
	{
		line = append_output(mini, (line + 1), temp);
		(*mini)->out_sign = 1;
	}
	return (line);
}

char	*append_output(t_mini **mini, char *line, char *temp)
{
	char	*filename;
	int		len;
	int		i;

	len = 0;
	i = -1;
	while (is_space(*line) && *line)
		line++;
	while (line[len] && !(is_space(line[len])))
		len++;
	filename = (char *)malloc(sizeof(char) * len + 1);
	while (++i < len)
		filename[i] = line[i];
	(*mini)->outfile = filename;
	open_outfile(mini, filename, temp);
	return (line + len);
}

void	open_outfile(t_mini **mini, char *filename, char *temp)
{
	if ((*mini)->fd_out)
		close((*mini)->fd_out);
	(*mini)->fd_out = open(filename, O_CREAT | O_WRONLY, 0777);
	(*mini)->std_out = dup(1);
	if ((*mini)->fd_out == -1)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(filename, 2);
		if (access(filename, W_OK))
			ft_putendl_fd(": Permission denied.", 2);
		else
			ft_putendl_fd(": No such file or directory", 2);
		free(temp);
		free ((*mini)->line);
		(*mini)->outfile = NULL;
		free ((*mini)->outfile);
		(*mini)->error = 1;
		read_prompt(mini);
	}
	if ((*mini)->out_sign == 1)
		(*mini)->fd_out = open((*mini)->outfile, O_WRONLY | O_APPEND);
	else
		(*mini)->fd_out = open((*mini)->outfile, O_WRONLY | O_TRUNC);
	(*mini)->std_out = dup(STDOUT_FILENO);
	dup2((*mini)->fd_out, STDOUT_FILENO);
}

void	edit_line(t_mini **mini)
{
	int		i;
	char	*temp;

	temp = (*mini)->line;
	i = 0;
	while (temp[i])
	{
		while (temp[i] && temp[i] != '>')
			i++;
		while ((is_space(temp[i]) || temp[i] == '>') && temp[i])
			temp[i++] = ' ';
		while (!(is_space(temp[i])) && temp[i] != '>' && temp[i])
			temp[i++] = ' ';
	}
}
