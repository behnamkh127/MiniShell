/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bekhodad <bekhodad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 15:00:47 by mfeshara          #+#    #+#             */
/*   Updated: 2024/02/08 12:06:09 by bekhodad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	parsing(t_mini **mini)
{
	t_node	*args;
	char	*line;
	int		i;
	int		k;

	line = (*mini)->line;
	i = 0;
	k = 0;
	args = NULL;
	(*mini)->lines = (char **)malloc(sizeof(char *)
			* ((*mini)->pipe_count + 1) + 1);
	if (!(*mini)->lines)
		exit (2);
	while (line[i])
	{
		i = make_args(&args, line, i, 0);
		make_lines(mini, &args, k);
		k++;
		if (line[i] == '|')
			i++;
	}
	(*mini)->pipe_count = k - 1;
	(*mini)->lines[k] = NULL;
}

int	make_args(t_node **args, char *line, int i, int len)
{
	while (line[i] && line[i] != '|')
	{
		while (is_space(line[i]) && line[i])
			i++;
		if (line[i] == 34 || line[i] == 39)
		{
			len = ++i;
			if (line[i - 1] == 34)
				while (line[len] != 34)
					len++;
			else if (line[i - 1] == 39)
				while (line[len] != 39)
					len++;
			i = (add_args(args, line, i, len)) + 1;
		}
		else if (line[i] != '|')
		{
			len = i;
			while (!is_space(line[len]) && line[len] != '|' && line[len])
				len++;
			i = add_args(args, line, i, len);
		}
	}
	return (i);
}

int	add_args(t_node **args, char *line, int i, int len)
{
	char	*str;
	int		j;

	j = 0;
	str = (char *)malloc(sizeof(char) * len + 1);
	if (!str)
		exit (2);
	while (i < len)
		str[j++] = line[i++];
	str[j] = '\0';
	pars_add_node(args, str);
	free (str);
	return (i);
}

void	pars_add_node(t_node **args, char *str)
{
	t_node	*new_node;
	t_node	*curr;

	new_node = (t_node *)malloc(sizeof(t_node));
	if (!new_node)
	{
		ft_putendl_fd("Allocating error", 2);
		exit (1);
	}
	new_node->str = ft_strdup(str);
	new_node->next = NULL;
	if (!*args)
		*args = new_node;
	else
	{
		curr = *args;
		while (curr->next)
			curr = curr->next;
		curr->next = new_node;
	}
}

void	make_lines(t_mini **mini, t_node **args, int k)
{
	t_node	*temp;
	int		i;
	int		len;

	len = count_len(args);
	(*mini)->lines[k] = (char *)malloc(sizeof(char *) * len + 1);
	if (!(*mini)->lines[k])
		exit (2);
	temp = *args;
	i = 0;
	while (temp)
	{
		len = 0;
		while (temp->str[len])
			(*mini)->lines[k][i++] = temp->str[len++];
		(*mini)->lines[k][i++] = 34;
		temp = temp->next;
	}
	(*mini)->lines[k][i] = '\0';
	free_args(args);
}
