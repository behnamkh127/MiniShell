/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scan_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bekhodad <bekhodad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 10:52:08 by mfeshara          #+#    #+#             */
/*   Updated: 2024/02/08 11:57:47 by bekhodad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	scan_line(t_mini **mini)
{
	int		i;
	char	*line;

	line = (*mini)->line;
	if (control_str(line, 0) == -1)
		scan_exit (mini, "quat", 1);
	first_char(mini, line);
	i = 0;
	question_mark(mini);
	while (line[i])
	{
		if (line[i] == '<')
			i = less_condition(mini, line, i);
		else if (line[i] == '>')
			i = great_condition(mini, line, i);
		else if (line[i] == ')' || line[i] == '(')
			scan_exit (mini, "near unexpected token `)'", 258);
		else if (line[i] == '|')
		{
			(*mini)->pipe_count++;
			i = pipe_condition(mini, line, i);
		}
		else
			i++;
	}
}

int	less_condition(t_mini **mini, char *line, int i)
{
	int	j;

	j = -1;
	i++;
	if ((!line[i]) || ((line[i] == '<') && (!line[i + 1]))
		|| ((line[i] == '<') && (line[i + 1] == '<') && (!line[i + 2]))
		|| ((line[i] == '>') && (!line[i + 1])))
		scan_exit (mini, "near unexpected token `newline'", 258);
	if (line[i] == '|' && line[i])
		scan_exit (mini, "near unexpected token `<'", 258);
	while (line[i] == '<' && line[i])
	{
		j++;
		i++;
	}
	if (j == 2)
		scan_exit (mini, "near unexpected token `<<'", 258);
	if (j > 2)
		scan_exit (mini, "near unexpected token `<<<'", 258);
	while (is_space (line[i]) && line[i])
		i++;
	if ((line[i] == '<' || line[i] == '>' || line [i] == '|') && line [i])
		scan_exit (mini, "near unexpected token `<'", 258);
	return (i);
}

int	pipe_condition(t_mini **mini, char *line, int i)
{
	if (i == 0)
	{
		(*mini)->pipe_count = 0;
		scan_exit (mini, "near unexpected token `|'", 258);
	}
	i++;
	if (!line[i])
	{
		(*mini)->pipe_count = 0;
		scan_exit (mini, "near unexpected token `newline'", 258);
	}
	while (is_space (line[i]) && line[i])
		i++;
	if (line[i] == '|' && line[i])
	{
		(*mini)->pipe_count = 0;
		scan_exit (mini, "near unexpected token `|'", 258);
	}
	return (i);
}

int	great_condition(t_mini **mini, char *line, int i)
{
	if (line[++i] == '>' && line[i])
		i++;
	while (is_space(line[i]) && line[i])
		i++;
	if (line[i] == '\0')
		scan_exit (mini, "near unexpected token `newline'", 258);
	if (line[i] == '|' && line[i])
		scan_exit(mini, "near unexpected token `|'", 258);
	if (line[i] == '<' && line[i])
	{
		if (line[i + 1] == '<' && line[i + 1])
			scan_exit (mini, "near unexpected token `<<'", 258);
		else
			scan_exit (mini, "near unexpected token `<'", 258);
	}
	if (line[i] == '>' && line[i])
	{
		if (line[i + 1] == '>' && line[i + 1])
			scan_exit (mini, "near unexpected token `>>'", 258);
		else if (line[i + 1] == '\0')
			scan_exit (mini, "near unexpected token `newline'", 258);
		else
			scan_exit (mini, "near unexpected token `>'", 258);
	}
	return (i);
}

void	scan_exit(t_mini **mini, char *err, int error)
{
	(*mini)->error = error;
	if (err)
	{
		ft_putstr_fd("minishell: Syntax error ", 2);
		ft_putendl_fd(err, 2);
	}
	free ((*mini)->line);
	(*mini)->line = NULL;
	read_prompt(mini);
}
