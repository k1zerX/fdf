/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbatz <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/21 18:18:23 by kbatz             #+#    #+#             */
/*   Updated: 2018/12/03 12:17:53 by kbatz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	l1;
	size_t	l2;

	l1 = ft_strlen(dst);
	l2 = ft_strlen(src);
	i = 0;
	while (i < l2 && l1 + i < size)
	{
		dst[l1 + i] = src[i];
		i++;
	}
	if (l1 + i == size)
		i--;
	if (l1 + i < l1)
		i = 0;
	dst[l1 + i] = 0;
	if (size < l1)
		l1 = size;
	return (l1 + l2);
}
