/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bekhodad <bekhodad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 10:24:25 by mfeshara          #+#    #+#             */
/*   Updated: 2024/02/09 12:41:16 by bekhodad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int		g_lobal = 0;

int	main(int ac, char **av, char **envp)
{
	t_mini	*mini;

	(void)ac;
	(void)av;
	mini = (t_mini *)malloc(sizeof(t_mini));
	if (!mini)
		exit (1);
	mini->error = 0;
	mini->envp = envp;
	mini->oldpwd = NULL;
	mini->pwd = ft_strdup(getenv("PWD"));
	mini->shlvl = 1;
	mini->fd_input = -2;
	mini->pipe_count = 0;
	mini->fd_out = 0;
	mini->std_in = dup(STDIN_FILENO);
	mini->export = NULL;
	env(&mini);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, handle_sigint);
	while (1)
		read_prompt(&mini);
	return (0);
}

void	read_prompt(t_mini **mini)
{
	char	*line;

	line = readline("minishell: ");
	if (line == NULL)
	{
		(*mini)->line = ft_strdup("exit");
		my_exit(mini);
	}
	if (line)
		add_history(line);
	if (g_lobal == 1 || g_lobal == 130)
	{
		(*mini)->error = g_lobal;
		g_lobal = 0;
	}
	(*mini)->line = ft_strtrim(line, " \t\v\r");
	scan_line(mini);
	find_here_doc(mini);
	change_output(mini);
	if ((*mini)->pipe_count == 0)
		mini_bultins(mini, quat_handle(ft_strdup((*mini)->line), 0));
	parsing(mini);
	my_exit(mini);
	var(mini);
	fork_pipe_excute(mini);
}
