/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_print.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfeshara <mfeshara@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 12:08:32 by bekhodad          #+#    #+#             */
/*   Updated: 2024/02/02 14:44:21 by mfeshara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	control_str(char *str, int i)
{
	while (str[i])
	{
		if (check_quats(str, i))
			return (-1);
		while (str[i] != 34 && str[i] != 39
			&& str[i])
			i++;
		if (str[i] == 34)
		{
			i++;
			while (str[i] != 34 && str[i])
				i++;
			if (str[i] == 34)
				i++;
		}
		else if (str[i] == 39)
		{
			i++;
			while (str[i] != 39 && str[i])
				i++;
			if (str[i] == 39)
				i++;
		}
	}
	return (0);
}

int	case_sign(t_echo **echo, t_mini **mini, int i)
{
	char	*str;
	int		j;

	if ((*echo)->str[i + 1] == 63)
	{
		printf("%d", (*mini)->error);
		i += 2;
	}
	else
	{
		j = 0;
		i++;
		str = (char *)malloc((ft_strlen((*echo)->str)) * sizeof(char));
		if (!str)
			free_echo(echo, mini, "Allocating error", 1);
		while ((!is_space((*echo)->str[i])) && ((*echo)->str[i] != 34)
			&& ((*echo)->str[i] != 39) && ((*echo)->str[i] != 36))
			str[j++] = (*echo)->str[i++];
		str[j] = '\0';
		find_variable(str, mini);
		free(str);
	}
	return (i);
}

int	echo_print(t_echo **echo, t_mini **mini, int i)
{
	if ((*echo)->sign_quat)
	{
		while ((*echo)->str[i] != 39 && (*echo)->str[i])
		{
			printf("%c", (*echo)->str[i]);
			i++;
		}
		(*echo)->sign_quat = 0;
	}
	else if ((*echo)->sign_double)
	{
		while ((*echo)->str[i] != 34 && (*echo)->str[i])
		{
			if ((*echo)->str[i] == 36)
				i = case_sign(echo, mini, i);
			if ((*echo)->str[i] != 34 && (*echo)->str[i]
				&& (*echo)->str[i] != 36)
				printf("%c", (*echo)->str[i]);
			i++;
		}
		(*echo)->sign_double = 0;
	}
	if ((*echo)->str[i])
		i++;
	return (i);
}

void	reg_print(t_echo **echo, t_mini **mini)
{
	int	i;

	i = 0;
	while ((*echo)->str[i])
	{
		while ((*echo)->str[i] == 36)
			i = case_sign2(echo, mini, i);
		if ((*echo)->str[i])
			printf("%c", (*echo)->str[i]);
		i++;
	}
}

int	case_sign2(t_echo **echo, t_mini **mini, int i)
{
	char	*str;
	int		j;

	if ((*echo)->str[i + 1] == 63)
	{
		printf("%d", (*mini)->error);
		i += 2;
	}
	else
	{
		j = 0;
		i++;
		str = (char *)malloc((ft_strlen((*echo)->str)) * sizeof(char));
		if (!str)
			free_echo(echo, mini, "Allocating error", 1);
		while (!(is_space((*echo)->str[i])) && (*echo)->str[i]
			&& (*echo)->str[i] != 36 && (*echo)->str[i] != 34)
			str[j++] = (*echo)->str[i++];
		str[j] = '\0';
		find_variable(str, mini);
		free(str);
	}
	return (i);
}
