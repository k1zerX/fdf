/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bintree_prefix.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbatz <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/28 17:48:54 by kbatz             #+#    #+#             */
/*   Updated: 2018/12/20 13:29:42 by kbatz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_btree_prefix(t_btree *start, void (*f)(t_btree *))
{
	if (!start || !f)
		return ;
	(*f)(start);
	ft_btree_prefix(start->left, f);
	ft_btree_prefix(start->right, f);
}
