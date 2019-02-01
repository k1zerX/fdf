/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stack_push.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbatz <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/28 16:21:26 by kbatz             #+#    #+#             */
/*   Updated: 2019/01/17 17:07:42 by kbatz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_stack_push(t_stack *stack, t_elem *tmp)
{
	if (!tmp)
		return ;
	tmp->next = stack->start;
	stack->start = tmp;
	stack->len++;
}
