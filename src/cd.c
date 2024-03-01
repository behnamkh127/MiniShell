/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bekhodad <bekhodad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/28 10:48:06 by mfeshara          #+#    #+#             */
/*   Updated: 2024/02/08 16:37:47 by bekhodad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	cd(t_mini **mini)
{
	char	path[1024];
	char	*str;

	str = ft_strtrim((*mini)->line, " \r\t\v");
	str = make_str(mini, str);
	if (chdir(str) == 0)
	{
		if ((*mini)->oldpwd)
		{
			free((*mini)->oldpwd);
			(*mini)->oldpwd = NULL;
		}
		(*mini)->oldpwd = (*mini)->pwd;
		(*mini)->pwd = ft_strdup(getcwd(path, sizeof(path)));
	}
	else
	{
		ft_putstr_fd("mini_shell: cd: ", 2);
		ft_putstr_fd(str, 2);
		exit_cd(mini, str, ": No such file or directory", 1);
	}
	if (str)
		free(str);
}

char	*make_str(t_mini **mini, char *str)
{
	char	*aux;

	str = quat_handle(str, 0);
	aux = str;
	str = ft_strchr(str, 'd') + 1;
	while (is_space(*str))
		str++;
	if (*str == '-')
	{
		if (!(*mini)->oldpwd)
			exit_cd (mini, aux, "minishell: cd: OLDPWD not set", 1);
		else
		{
			str = (*mini)->oldpwd;
			printf("%s\n", str);
		}
	}
	else if (*str == '~' || *str == '\0')
		str = getenv("HOME");
	str = ft_strdup(str);
	free (aux);
	return (str);
}

char	*quat_handle(char *str, int i)
{
	char	*temp;

	temp = str;
	if (str[i] == 34)
	{
		str = ft_strtrim(str, "\"");
		free(temp);
	}
	else if (str[i] == 39)
	{
		str = ft_strtrim(str, "\'");
		free(temp);
	}
	else
	{
		str = ft_strdup(str);
		free(temp);
	}
	return (str);
}

void	exit_cd(t_mini **mini, char *str, char *err, int error)
{
	if (str)
		free (str);
	(*mini)->error = error;
	if (err)
		ft_putendl_fd(err, 2);
	mini_exit(mini);
}
