/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbatz <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/15 19:02:37 by kbatz             #+#    #+#             */
/*   Updated: 2019/02/15 19:04:21 by kbatz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

double		mod_vector(t_vector v)
{
	return (sqrt(v.x * v.x + v.y * v.y + v.z * v.z));
}

void		k_vector(t_vector *v, double k)
{
	v->x *= k;
	v->y *= k;
	v->z *= k;
}

t_vector	add_vector(t_vector a, t_vector b)
{
	t_vector	res;

	res.x = a.x + b.x;
	res.y = a.y + b.y;
	res.z = a.z + b.z;
	return (res);
}

t_vector	turn_vector(t_vector v, t_qtrn q, char clockwise)
{
	t_qtrn	tmp;

	tmp.w = 0;
	tmp.v = v;
	if (clockwise)
		tmp = mul_qtrn(mul_qtrn(q, tmp), rev_qtrn(q));
	else
		tmp = mul_qtrn(mul_qtrn(rev_qtrn(q), tmp), q);
	return (tmp.v);
}
