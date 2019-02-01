/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbatz <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/23 23:08:15 by kbatz             #+#    #+#             */
/*   Updated: 2018/12/22 20:14:49 by kbatz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void		ft_del(void *content, size_t content_size)
{
	if (!content)
		return ;
	ft_bzero(content, content_size);
	free(content);
}

t_list			*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*res;

	if (!lst || !f)
		return (NULL);
	res = (*f)(lst);
	if (res)
	{
		res->next = ft_lstmap(lst->next, f);
		if (!res->next && lst->next)
		{
			ft_lstdelone(&res, &ft_del);
			return (NULL);
		}
	}
	return (res);
}
