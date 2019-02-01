/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbatz <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/21 19:00:20 by kbatz             #+#    #+#             */
/*   Updated: 2019/02/01 09:23:31 by kbatz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *haystack, const char *needle)
{
	size_t	i;
	size_t	j;
	size_t	l1;
	size_t	l2;
	char	b;

	l1 = ft_strlen(haystack);
	l2 = ft_strlen(needle);
	i = -1;
	if (l2 <= l1)
		while (++i < l1 - l2 + 1)
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
