/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bekhodad <bekhodad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 10:53:04 by bekhodad          #+#    #+#             */
/*   Updated: 2024/02/09 15:18:13 by bekhodad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

extern int	g_lobal;

void	fork_pipe_excute(t_mini **mini)
{
	int	i;
	int	**fd_pipe;
	int	*pid;

	fd_pipe = init_pipe(mini, &pid);
	i = 0;
	while (i < (*mini)->pipe_count + 1)
	{
		(*mini)->args = ft_split((*mini)->lines[i], 34);
		do_fork(mini, pid, fd_pipe, i);
		i++;
	}
	close_wait(mini, fd_pipe, pid);
	mini_exit(mini);
}

int	**init_pipe(t_mini **mini, int **pid)
{
	int		i;
	int		**fd_pipe;

	i = 0;
	fd_pipe = (int **)malloc(sizeof(int ) * (*mini)->pipe_count);
	if (!fd_pipe)
		exit (2);
	while (i < (*mini)->pipe_count)
	{
		fd_pipe[i] = (int *)malloc(sizeof(int) * 2);
		if (pipe(fd_pipe[i++]) == -1)
			exit (2);
	}
	*pid = (int *)malloc(sizeof(int) * (*mini)->pipe_count + 1);
	if (!pid)
		exit (2);
	return (fd_pipe);
}

void	close_in_loop(t_mini **mini, int **fd_pipe, int i)
{
	int		j;

	j = 0;
	while (j < (*mini)->pipe_count)
	{
		if (j != i)
			close (fd_pipe[j][1]);
		if ((j != i - 1 && i != 0) || ft_strcmp((*mini)->args[0], "cat") == 0)
			close (fd_pipe[j][0]);
		j++;
	}
}

void	free_pipe_pid(int **fd_pipe, int *pid)
{
	int		**temp;

	temp = NULL;
	if (fd_pipe)
	{
		temp = fd_pipe;
		while (*temp)
		{
			free(*temp);
			*temp = NULL;
			temp++;
		}
		free(fd_pipe);
	}
	if (pid)
		free (pid);
}

void	do_fork(t_mini **mini, int *pid, int **fd_pipe, int i)
{
	pid[i] = fork();
	if (pid[i] == -1)
		exit (2);
	signal(SIGINT, handle_sigint2);
	if (pid[i] == 0)
	{
		signal(SIGINT, SIG_DFL);
		close_in_loop(mini, fd_pipe, i);
		do_processes(mini, fd_pipe, i);
		exit (0);
	}
	free_array((*mini)->args);
}
