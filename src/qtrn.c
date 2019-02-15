/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   qtrn.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbatz <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/15 18:45:51 by kbatz             #+#    #+#             */
/*   Updated: 2019/02/15 19:26:15 by kbatz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

double		mod_qtrn(t_qtrn q)
{
	return (sqrt(q.v.x * q.v.x + q.v.y * q.v.y + q.v.z * q.v.z + q.w * q.w));
}

t_qtrn		rev_qtrn(t_qtrn q)
{
	k_vector(&q.v, -1);
	return (q);
}

void		k_qtrn(t_qtrn *q, double k)
{
	q->v.x *= k;
	q->v.y *= k;
	q->v.z *= k;
	q->w *= k;
}

t_qtrn		get_qtrn(t_vector axis, double alpha)
{
	t_qtrn	q;

	k_vector(&axis, sin(alpha) / 2);
	q.v = axis;
	q.w = cos(alpha / 2);
	k_qtrn(&q, 1 / mod_qtrn(q));
	return (q);
}

t_qtrn		mul_qtrn(t_qtrn a, t_qtrn b)
{
	t_qtrn	res;

	res.w = a.w * b.w - a.v.x * b.v.x - a.v.y * b.v.y - a.v.z * b.v.z;
	res.v.x = a.w * b.v.x + a.v.x * b.w + a.v.y * b.v.z - a.v.z * b.v.y;
	res.v.y = a.w * b.v.y + a.v.y * b.w + a.v.z * b.v.x - a.v.x * b.v.z;
	res.v.z = a.w * b.v.z + a.v.z * b.w + a.v.x * b.v.y - a.v.y * b.v.x;
	return (res); 
}
