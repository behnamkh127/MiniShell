/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bekhodad <bekhodad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 14:53:26 by bekhodad          #+#    #+#             */
/*   Updated: 2024/02/09 12:53:06 by bekhodad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

extern int	g_lobal;

void	find_here_doc(t_mini **mini)
{
	int			i;
	t_node		*key;

	i = 0;
	key = NULL;
	while ((*mini)->line[i])
	{
		i = skip_quat((*mini)->line, i);
		if ((*mini)->line[i++] == '<')
		{
			if ((*mini)->line[i] && (*mini)->line[i] != '<')
				change_input(mini, i);
			if ((*mini)->line[i] == '<' && (*mini)->line[i + 1] != '<'
				&& (*mini)->line[i] && (*mini)->line[i + 1])
				i = update_line(mini, &key, i);
			else
				break ;
		}
	}
	if (key)
	{
		init_input(mini, &key);
		free_link (mini, &key);
	}
}

char	*make_delimiter(char *location)
{
	int		i;
	int		j;
	char	*temp;
	char	*limiter;

	i = 0;
	j = 0;
	temp = ft_strtrim(++location, " \t\v\r");
	i = 0;
	while (!(is_space(temp[i])) && temp[i])
		i++;
	limiter = (char *)malloc(sizeof(char) * i + 1);
	if (!limiter)
		exit (2);
	j = 0;
	while (j < i)
	{
		limiter[j] = temp[j];
		j++;
	}
	limiter[j] = '\0';
	free (temp);
	return (limiter);
}

void	init_input(t_mini **mini, t_node **key)
{
	char		*line;
	t_node		*temp;

	temp = *key;
	(*mini)->fd_here_doc = open("temp", O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if ((*mini)->fd_here_doc == -1)
		exit (3);
	signal(SIGINT, handle_sigint3);
	while (1)
	{
		line = readline("> ");
		if (!line || ft_strcmp(line, temp->str) == 0)
		{
			if (temp->next)
				temp = temp->next;
			else
				break ;
		}
		else if ((*key)->next == NULL)
		{
			write((*mini)->fd_here_doc, line, ft_strlen(line));
			write((*mini)->fd_here_doc, "\n", 1);
		}
	}
	close ((*mini)->fd_here_doc);
}

int	update_line(t_mini **mini, t_node **key, int i)
{
	char	*location;
	char	*limiter;

	location = &((*mini)->line[i]);
	limiter = make_delimiter(location);
	env_add(mini, key, limiter);
	*(location - 1) = ' ';
	*location = ' ';
	while (is_space(*location))
		location++;
	while (!(is_space(*location)) && *location)
	{
		*location = ' ';
		location++;
	}
	return (0);
}

void	free_link(t_mini **mini, t_node **key)
{
	t_node	*temp;
	t_node	*curr;

	if (g_lobal == 2)
	{
		g_lobal = 0;
		mini_exit(mini);
	}
	if (!*key)
		return ;
	curr = *key;
	while (curr->next)
	{
		temp = curr;
		curr = curr->next;
		free(temp);
	}
	free (curr);
	(*mini)->fd_here_doc = open ("temp", O_RDONLY);
	(*mini)->std_in = dup(0);
	dup2((*mini)->fd_here_doc, STDIN_FILENO);
	close ((*mini)->fd_here_doc);
}
