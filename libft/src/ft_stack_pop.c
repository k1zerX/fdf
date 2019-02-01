/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stack_pop.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbatz <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/28 16:25:19 by kbatz             #+#    #+#             */
/*   Updated: 2019/01/17 17:03:44 by kbatz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_elem		*ft_stack_pop(t_stack *stack)
{
	t_elem		*tmp;

	if (!stack->len)
		return (NULL);
	tmp = stack->start;
	stack->start = tmp->next;
	stack->len--;
	tmp->next = NULL;
	return (tmp);
}
