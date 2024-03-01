/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfeshara <mfeshara@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 16:16:13 by bekhodad          #+#    #+#             */
/*   Updated: 2024/01/31 11:30:02 by mfeshara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	my_exit(t_mini **mini)
{
	char	*line;
	char	**args;
	int		len;

	if (ft_strchr((*mini)->line, '|') || (*mini)->line[1] == '\0')
		return ;
	args = ft_split((*mini)->line, ' ');
	len = 0;
	while (args[len])
		len++;
	line = quat_handle(ft_strdup(args[0]), 0);
	if (ft_strcmp(line, "exit") == 0)
	{
		find_error(mini, args, len);
		if (len < 3 || (len > 2 && !(check_is_num(args[1]))))
			correct_exit(mini, args, line);
		else
			read_prompt(mini);
	}
	free_array(args);
	free (line);
}

void	find_error(t_mini **mini, char **args, int len)
{
	ft_putendl_fd("exit", 2);
	if (len == 1)
		(*mini)->error = 0;
	else if (len < 3 && check_is_num(args[1]))
		(*mini)->error = ft_atoi(args[1]);
	else if (!check_is_num(args[1]))
	{
		(*mini)->error = 255;
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(args[1], 2);
		ft_putendl_fd(": numeric argument required", 2);
	}
	else
	{
		(*mini)->error = 1;
		ft_putendl_fd("minishell: exit: too many arguments", 2);
	}
}

int	check_is_num(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

void	correct_exit(t_mini **mini, char **args, char *line)
{
	delete_nodes(mini);
	free ((*mini)->line);
	free_array(args);
	free (line);
	if ((*mini)->shlvl == 1)
		final_exit(mini);
	else
	{
		(*mini)->shlvl--;
		read_prompt(mini);
	}
}
