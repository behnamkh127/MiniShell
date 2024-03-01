/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfeshara <mfeshara@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 15:22:46 by mfeshara          #+#    #+#             */
/*   Updated: 2024/01/31 11:30:13 by mfeshara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	delete_nodes(t_mini **mini)
{
	delete_var(mini);
	remove_node(mini, &(*mini)->env);
	remove_node(mini, &(*mini)->export);
}

void	delete_var(t_mini **mini)
{
	t_variable	*curr;
	t_variable	*prev;

	curr = (*mini)->var;
	while (curr)
	{
		if (curr->shlvl == (*mini)->shlvl)
		{
			if (curr == (*mini)->var)
				(*mini)->var = curr->next;
			else
				prev->next = curr->next;
			free (curr->name);
			free (curr->value);
			free (curr);
		}
		prev = curr;
		curr = curr->next;
	}
}

void	remove_node(t_mini **mini, t_node **root)
{
	t_node	*curr;
	t_node	*prev;

	curr = *root;
	while (curr)
	{
		if (curr->shlvl == (*mini)->shlvl)
		{
			if (curr == *root)
				*root = curr->next;
			else
				prev->next = curr->next;
			free (curr->str);
			free (curr);
		}
		prev = curr;
		curr = curr->next;
	}
}

void	final_exit(t_mini **mini)
{
	int	error;

	error = (*mini)->error;
	if ((*mini)->oldpwd)
		free ((*mini)->oldpwd);
	if ((*mini)->pwd)
		free ((*mini)->pwd);
	if ((*mini)->infile)
		free ((*mini)->infile);
	if ((*mini)->outfile)
		free ((*mini)->outfile);
	if ((*mini))
		free ((*mini));
	exit (error);
}
