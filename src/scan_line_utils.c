/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scan_line_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bekhodad <bekhodad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 16:16:24 by mfeshara          #+#    #+#             */
/*   Updated: 2024/02/08 11:57:14 by bekhodad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	slash_condition(t_mini **mini, char *line)
{
	char	*str;
	int		i;

	i = 1;
	while (line[i] == '/' && line[i])
		i++;
	if (line[i] != ' ' && line[i])
		return ;
	str = (char *)malloc(sizeof (char) * i + 1);
	if (!str)
		scan_exit(mini, "", 2);
	str[i--] = '\0';
	while (i >= 0)
	{
		str[i] = line[i];
		i--;
	}
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(": is a directory", 2);
	free(str);
	scan_exit(mini, "", 126);
}

void	first_char(t_mini **mini, char *line)
{
	if (line[0] == '/')
		slash_condition(mini, line);
	if (line[0] == '!')
		scan_exit (mini, "near unexpected token `newline'", 258);
	if (line[0] == ':')
		scan_exit (mini, "", 0);
	if (line[0] == '&' && line[1] != '&')
		scan_exit (mini, "near unexpected token `&'", 258);
	if (line[0] == '&' && line[1] == '&')
		scan_exit (mini, "near unexpected token `&&'", 258);
	if (line[0] == ';' && line[1] != ';')
		scan_exit (mini, "near unexpected token `;'", 258);
	if (line[0] == ';' && line[1] == ';')
		scan_exit (mini, "near unexpected token `;;'", 258);
	if (line[0] == '~' && !line[1])
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(getenv("HOME="), 2);
		ft_putstr_fd(": is a directory", 2);
		scan_exit(mini, "", 126);
	}
}

void	question_mark(t_mini **mini)
{
	int		i;

	i = 0;
	while ((*mini)->line[i])
	{
		if ((*mini)->line[i] == 39)
		{
			i++;
			while ((*mini)->line[i] != 39)
				i++;
			i++;
		}
		if ((*mini)->line[i] == 36 && (*mini)->line[i + 1]
			&& (*mini)->line[i + 1] == 63)
		{
			question_mark2(mini, i, 0, 0);
			return ;
		}
		i++;
	}
}

void	question_mark2(t_mini **mini, int i, int j, int len)
{
	char	*str1;
	char	*str2;
	int		sign;

	str1 = ft_substr((*mini)->line, 0, i);
	sign = 1;
	j = i;
	while ((*mini)->line[j])
	{
		if ((*mini)->line[j] == 36 && (*mini)->line[j + 1]
			&& (*mini)->line[j + 1] == 63)
			sign++;
		j++;
		len++;
	}
	len += sign * (ft_strlen(ft_itoa((*mini)->error)));
	str2 = (char *)malloc(sizeof(char) * len + 1);
	question_mark3(mini, i, str1, str2);
}

void	question_mark3(t_mini **mini, int i, char *str1, char *str2)
{
	char	*temp;
	int		j;
	int		len;

	temp = ft_itoa((*mini)->error);
	j = 0;
	while ((*mini)->line[i])
	{
		if ((*mini)->line[i] == 36 && (*mini)->line[i + 1]
			&& (*mini)->line[i + 1] == 63)
		{
			i += 2;
			len = 0;
			while (temp[len])
				str2[j++] = temp[len++];
		}
		else if ((*mini)->line[i])
			str2[j++] = (*mini)->line[i++];
	}
	str2[j] = '\0';
	free ((*mini)->line);
	(*mini)->line = ft_strjoin(str1, str2);
	free (str1);
	free (str2);
	free (temp);
}
