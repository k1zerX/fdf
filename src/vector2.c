/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbatz <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/16 19:39:35 by kbatz             #+#    #+#             */
/*   Updated: 2019/04/24 17:47:54 by kbatz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

double		scalar_mul(t_vector a, t_vector b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}

double		get_angle(t_vector a, t_vector b)
{
	return (acos(scalar_mul(a, b) / mod_vector(a) / mod_vector(b)));
}

t_vector	vector_mul(t_vector a, t_vector b)
{
	t_vector	res;

	res.x = a.y * b.z - a.z * b.y;
	res.y = a.z * b.x - a.x * b.z;
	res.z = a.x * b.y - a.y * b.x;
	return (res);
}

void		project_vector(t_vector *a, t_vector b)
{
	t_qtrn	q;

	q = get_qtrn(vector_mul(*a, b), acos(scalar_mul(*a, b)));
	*a = turn_vector(*a, q, 1);
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
