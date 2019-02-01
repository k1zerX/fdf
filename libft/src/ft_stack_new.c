/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stack_new.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbatz <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/28 15:00:24 by kbatz             #+#    #+#             */
/*   Updated: 2019/01/17 17:08:43 by kbatz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_stack		*ft_stack_new(void)
{
	t_stack		*stack;

	stack = malloc(sizeof(stack));
	stack->start = NULL;
	stack->len = 0;
	return (stack);
}
