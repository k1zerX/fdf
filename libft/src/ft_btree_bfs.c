/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_btree_bfs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbatz <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/28 18:41:56 by kbatz             #+#    #+#             */
/*   Updated: 2019/01/17 17:12:05 by kbatz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void			ft_btree_bfs(t_btree *start, void (*f)(t_btree *))
{
	t_queue		*queue;
	t_btree		*tmp;

	if (!start || !f)
		return ;
	queue = ft_memalloc(sizeof(*queue));
	ft_queue_push(queue, ft_new_elem(start, sizeof(t_btree), 1));
	while (queue->len)
	{
		tmp = (t_btree *)ft_queue_pop(queue)->content;
		(*f)(tmp);
		free(tmp->content);
		free(tmp);
		if (tmp->left)
			ft_queue_push(queue, ft_new_elem(tmp->left, sizeof(t_btree), 1));
		if (tmp->right)
			ft_queue_push(queue, ft_new_elem(tmp->right, sizeof(t_btree), 1));
	}
}
