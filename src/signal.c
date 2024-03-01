/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bekhodad <bekhodad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 12:40:20 by bekhodad          #+#    #+#             */
/*   Updated: 2024/02/09 12:48:10 by bekhodad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

extern int	g_lobal;

void	handle_sigint(int sig)
{
	(void)sig;
	g_lobal = 1;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	handle_sigint2(int sig)
{
	(void)sig;
	g_lobal = 130;
	write(1, "\n", 1);
	rl_replace_line("", 1);
	rl_redisplay();
}

void	handle_sigint3(int sig)
{
	(void)sig;
	g_lobal = 2;
	write(1, "\n", 1);
	close(STDIN_FILENO);
}
