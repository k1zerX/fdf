/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bintree_infix.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbatz <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/28 17:52:42 by kbatz             #+#    #+#             */
/*   Updated: 2018/12/20 13:28:50 by kbatz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_btree_infix(t_btree *start, void (*f)(t_btree *))
{
	if (!start || !f)
		return ;
	ft_btree_infix(start->left, f);
	(*f)(start);
	ft_btree_infix(start->right, f);
}
