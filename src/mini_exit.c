/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bekhodad <bekhodad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 11:35:43 by mfeshara          #+#    #+#             */
/*   Updated: 2024/02/09 10:59:52 by bekhodad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	mini_exit(t_mini **mini)
{
	update_env(mini);
	free_array((*mini)->lines);
	free((*mini)->line);
	(*mini)->line = NULL;
	(*mini)->pipe_count = 0;
	if ((*mini)->fd_here_doc)
	{
		dup2((*mini)->std_in, STDIN_FILENO);
		close ((*mini)->fd_here_doc);
		unlink("temp");
	}
	if ((*mini)->fd_input)
	{
		dup2((*mini)->std_in, STDIN_FILENO);
		close ((*mini)->fd_input);
	}
	if ((*mini)->fd_out)
	{
		dup2((*mini)->std_out, STDOUT_FILENO);
		close ((*mini)->fd_out);
		close((*mini)->std_out);
	}
	signal(SIGINT, handle_sigint);
	read_prompt(mini);
}

void	free_array(char **diff)
{
	char	**temp;

	if (diff)
	{
		temp = diff;
		while (*temp)
		{
			free(*temp);
			*temp = NULL;
			temp++;
		}
		free(diff);
	}
}

void	close_wait(t_mini **mini, int **fd_pipe, int *pid)
{
	int		i;
	int		wstatus;

	i = 0;
	while (i < (*mini)->pipe_count)
	{
		close(fd_pipe[i][0]);
		close(fd_pipe[i][1]);
		i++;
	}
	i = 0;
	while (i < (*mini)->pipe_count + 1)
		waitpid(pid[i++], &wstatus, 0);
	if (WIFEXITED(wstatus))
		(*mini)->error = WEXITSTATUS(wstatus);
}
