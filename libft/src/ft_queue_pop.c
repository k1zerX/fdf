/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_queue_pop.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbatz <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/28 16:20:31 by kbatz             #+#    #+#             */
/*   Updated: 2019/01/17 17:03:23 by kbatz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_elem		*ft_queue_pop(t_queue *queue)
{
	t_elem		*tmp;

	if (!queue->len)
		return (NULL);
	tmp = queue->start;
	queue->start = tmp->next;
	queue->len--;
	if (!queue->len)
		queue->end = NULL;
	tmp->next = NULL;
	return (tmp);
}
