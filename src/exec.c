/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bekhodad <bekhodad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 13:18:55 by mfeshara          #+#    #+#             */
/*   Updated: 2024/02/09 14:57:17 by bekhodad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	exec(t_mini **mini)
{
	char	*path;

	path = NULL;
	if ((*mini)->args[0][0] == '/')
	{
		if (access((*mini)->args[0], F_OK) == 0)
			path = ft_strdup((*mini)->args[0]);
		else
			exec_exit (mini, 0);
	}
	else
		path = find_path(mini, NULL);
	if (path == NULL)
		exec_exit (mini, 1);
	execve(path, (*mini)->args, (*mini)->envp);
	exit (0);
}

char	*find_path(t_mini **mini, char *path)
{
	char	**env_path;
	char	*with_slash;
	char	*path_final;
	int		i;

	i = 0;
	path_final = ft_getenv(mini);
	if (path_final == NULL)
		exec_exit (mini, 0);
	env_path = ft_split(path_final, ':');
	while (env_path[i])
	{
		with_slash = ft_strjoin(env_path[i++], "/");
		path_final = ft_strjoin(with_slash, (*mini)->args[0]);
		if (access(path_final, F_OK) == 0)
		{
			path = ft_strdup(path_final);
			break ;
		}
		test_break(&with_slash, &path_final);
	}
	test_break(&with_slash, &path_final);
	free_array(env_path);
	return (path);
}

void	test_break(char **with_slash, char **path_final)
{
	if (!*with_slash || !*path_final)
		return ;
	if (*with_slash)
		free(*with_slash);
	if (*path_final)
		free(*path_final);
	*with_slash = NULL;
	*path_final = NULL;
}

char	*ft_getenv(t_mini **mini)
{
	t_node	*temp;

	temp = (*mini)->env;
	while (temp)
	{
		if (ft_strncmp(temp->str, "PATH", 4) == 0)
			return ((ft_strchr(temp->str, '=') + 1));
		temp = temp->next;
	}
	return (NULL);
}

void	exec_exit(t_mini **mini, int sign)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd((*mini)->args[0], 2);
	if (sign == 0)
		ft_putendl_fd(": No such file or directory", 2);
	if (sign == 1)
		ft_putendl_fd(": command not found", 2);
	(*mini)->error = 127;
	exit ((*mini)->error);
}
