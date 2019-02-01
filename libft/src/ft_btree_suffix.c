/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bintree_suffix.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbatz <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/28 17:54:55 by kbatz             #+#    #+#             */
/*   Updated: 2018/12/20 13:29:19 by kbatz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_btree_suffix(t_btree *start, void (*f)(t_btree *))
{
	if (!start || !f)
		return ;
	ft_btree_suffix(start->left, f);
	ft_btree_suffix(start->right, f);
	(*f)(start);
}
