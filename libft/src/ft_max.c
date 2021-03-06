/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_max.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbatz <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/20 13:54:53 by kbatz             #+#    #+#             */
/*   Updated: 2018/12/20 13:56:37 by kbatz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_max(void *a, void *b, size_t size)
{
	if (ft_memcmp(a, b, size) < 0)
		return (b);
	return (a);
}
