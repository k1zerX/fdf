/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbatz <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/22 18:34:10 by kbatz             #+#    #+#             */
/*   Updated: 2018/12/02 05:45:47 by kbatz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	if (dst != src)
	{
		dst += n;
		src += n;
		while (n-- > 0)
			*(unsigned char *)--dst = *(unsigned char *)--src;
	}
	return (dst);
}
