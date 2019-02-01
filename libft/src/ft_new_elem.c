/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_new_elem.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbatz <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/17 16:56:53 by kbatz             #+#    #+#             */
/*   Updated: 2019/01/17 17:28:51 by kbatz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_elem		*ft_new_elem(void *content, size_t content_size, char copy)
{
	t_elem		*tmp;

	if (!(tmp = malloc(sizeof(*tmp))))
		return (NULL);
	tmp->content_size = content_size;
	if (!copy)
		tmp->content = content;
	else if (content)
	{
		tmp->content = malloc(content_size);
		if (!tmp->content)
		{
			free(tmp);
			return (NULL);
		}
		ft_memcpy(tmp->content, content, content_size);
	}
	else
	{
		tmp->content = NULL;
		tmp->content_size = 0;
	}
	tmp->next = NULL;
	return (tmp);
}
