/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbatz <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/21 19:30:32 by kbatz             #+#    #+#             */
/*   Updated: 2018/12/23 17:49:13 by kbatz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;
	size_t	l1;
	size_t	l2;
	char	b;

	l1 = ft_strlen(haystack);
	l2 = ft_strlen(needle);
	if (l2 > len)
		return (NULL);
	if (len < l1)
		l1 = len;
	i = -1;
	while (++i < l1 && i <= l1 - l2)
	{
		b = 1;
		j = -1;
		while (++j < l2)
			if (needle[j] != haystack[i + j])
				b = 0;
		if (b)
			return ((char *)haystack + i);
	}
	return (NULL);
}
