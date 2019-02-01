/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_queue_push.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbatz <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/28 16:20:02 by kbatz             #+#    #+#             */
/*   Updated: 2019/01/17 17:06:19 by kbatz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_queue_push(t_queue *queue, t_elem *tmp)
{
	if (!tmp)
		return ;
	if (queue->len)
		queue->end->next = tmp;
	else
		queue->start = tmp;
	queue->end = tmp;
	queue->len++;
}
