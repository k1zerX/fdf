/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_queue_new.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbatz <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/28 14:47:37 by kbatz             #+#    #+#             */
/*   Updated: 2019/01/17 17:09:28 by kbatz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_queue		*ft_queue_new(void)
{
	t_queue		*queue;

	queue = malloc(sizeof(*queue));
	queue->len = 0;
	queue->start = NULL;
	queue->end = NULL;
	return (queue);
}
