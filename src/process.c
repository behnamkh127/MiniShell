/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bekhodad <bekhodad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 11:16:23 by mfeshara          #+#    #+#             */
/*   Updated: 2024/02/08 11:46:57 by bekhodad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	do_processes(t_mini **mini, int **fd_pipe, int i)
{
	if ((*mini)->pipe_count == 0)
		single_process(mini, i);
	else if (i == 0)
		first_process(mini, fd_pipe, i);
	else if (i == (*mini)->pipe_count)
		last_process(mini, fd_pipe, i);
	else
		repeated_process(mini, fd_pipe, i);
}

void	single_process(t_mini **mini, int i)
{
	bultins(mini, i);
}

void	first_process(t_mini **mini, int **fd_pipe, int i)
{
	dup2(fd_pipe[i][1], STDOUT_FILENO);
	bultins(mini, i);
}

void	last_process(t_mini **mini, int **fd_pipe, int i)
{
	dup2(fd_pipe[i - 1][0], STDIN_FILENO);
	bultins(mini, i);
}

void	repeated_process(t_mini **mini, int **fd_pipe, int i)
{
	dup2(fd_pipe[i - 1][0], STDIN_FILENO);
	dup2(fd_pipe[i][1], STDOUT_FILENO);
	bultins(mini, i);
}
