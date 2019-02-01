/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bintree_new.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbatz <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/28 14:29:45 by kbatz             #+#    #+#             */
/*   Updated: 2018/12/20 13:30:27 by kbatz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_btree		*ft_btree_new(void const *content, size_t content_size)
{
	t_btree	*tmp;

	tmp = (t_btree *)malloc(sizeof(*tmp));
	if (!tmp)
		return (NULL);
	if (content)
	{
		tmp->content = malloc(content_size);
		if (!tmp->content)
		{
			free(tmp);
			return (NULL);
		}
		tmp->content_size = content_size;
		ft_memcpy(tmp->content, content, content_size);
	}
	else
	{
		tmp->content = NULL;
		tmp->content_size = 0;
	}
	tmp->left = NULL;
	tmp->right = NULL;
	return (tmp);
}
