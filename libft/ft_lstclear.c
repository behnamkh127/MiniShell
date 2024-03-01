/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: behnam <behnam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 22:05:46 by behnam            #+#    #+#             */
/*   Updated: 2023/09/26 22:06:01 by behnam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*ptr;

	if (lst == 0 || *lst == 0 || del == 0)
		return ;
	ptr = *lst;
	while (lst && *lst)
	{
		ptr = (*lst)->next;
		ft_lstdelone(*lst, del);
		*lst = ptr;
	}
}
