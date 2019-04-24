/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbatz <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/24 17:49:03 by kbatz             #+#    #+#             */
/*   Updated: 2019/04/24 17:57:58 by kbatz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		ft_key_press(int keycode, t_params *prms)
{
	if (keycode == 53)
		ft_close(prms);
	else if (keycode == 15)
		ft_initialize(prms);
	else if (keycode == 69)
	{
		prms->d *= 0.8;
		prms->shift.z *= 0.8;
		prms->delta *= 0.8;
	}
	else if (keycode == 78)
	{
		prms->d *= 1.25;
		prms->shift.z *= 1.25;
		prms->delta *= 1.25;
	}
	ft_draw(prms);
	return (0);
}

int		ft_mouse_press(int button, int x, int y, t_params *prms)
{
	if (button == 1)
	{
		if (x >= 0 && y >= 0 && x < prms->n && y < prms->m)
			prms->lmb = 1;
		prms->lmb_p.x = x;
		prms->lmb_p.y = y;
	}
	else if (button == 2)
	{
		if (x >= 0 && y >= 0 && x < prms->n && y < prms->m)
			prms->rmb = 1;
		prms->rmb_p.x = x;
		prms->rmb_p.y = y;
	}
	else if (button == 4)
		prms->shift.z += prms->delta;
	else if (button == 5)
		prms->shift.z -= prms->delta;
	ft_draw(prms);
	return (0);
}

int		ft_mouse_release(int button, int x, int y, t_params *prms)
{
	(void)x;
	(void)y;
	if (button == 1)
		prms->lmb = 0;
	else if (button == 2)
		prms->rmb = 0;
	return (0);
}

int		ft_mouse_move(int x, int y, t_params *prms)
{
	t_qtrn		q;
	t_vector	axis;

	if (prms->rmb)
	{
		prms->shift.x += (double)(x - prms->rmb_p.x) / prms->d \
						* (prms->shift.z + prms->d) / K;
		prms->shift.y += (double)(y - prms->rmb_p.y) / prms->d \
						* (prms->shift.z + prms->d) / K;
		prms->rmb_p.x = x;
		prms->rmb_p.y = y;
	}
	else if (prms->lmb)
	{
		axis = turn_vector(get_vector(0, 1, 0), prms->q, 0);
		q = get_qtrn(axis, (double)(x - prms->lmb_p.x) / 100);
		prms->q = mul_qtrn(prms->q, q);
		axis = turn_vector(get_vector(-1, 0, 0), prms->q, 0);
		q = get_qtrn(axis, (double)(y - prms->lmb_p.y) / 100);
		prms->q = mul_qtrn(prms->q, q);
		prms->lmb_p.x = x;
		prms->lmb_p.y = y;
	}
	ft_draw(prms);
	return (0);
}
