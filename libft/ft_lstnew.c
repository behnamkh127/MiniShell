/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: behnam <behnam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 22:14:09 by behnam            #+#    #+#             */
/*   Updated: 2023/09/26 22:14:20 by behnam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*ptr;

	ptr = (t_list *) malloc(sizeof(t_list));
	if (ptr == 0)
		return (0);
	ptr->content = content;
	ptr->next = 0;
	return (ptr);
}
