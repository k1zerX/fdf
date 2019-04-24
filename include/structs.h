/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbatz <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/15 19:20:04 by kbatz             #+#    #+#             */
/*   Updated: 2019/04/24 18:02:21 by kbatz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include "fdf.h"

typedef struct		s_point
{
	int				x;
	int				y;
}					t_point;

typedef struct		s_gradient
{
	int				from;
	int				to;
	double			opacity_x;
	double			opacity_y;
	double			k;
	char			inv;
}					t_gradient;

typedef struct		s_vector
{
	double			x;
	double			y;
	double			z;
}					t_vector;

typedef struct		s_qtrn
{
	t_vector		v;
	double			w;
}					t_qtrn;

typedef struct		s_params
{
	void			*mlx;
	void			*win;
	void			*img_ptr;
	char			*img;
	int				x;
	int				y;
	int				z;
	t_vector		shift;
	t_qtrn			q;
	char			alt;
	char			lmb;
	t_point			lmb_p;
	char			rmb;
	t_point			rmb_p;
	char			xturn;
	char			yturn;
	char			zturn;
	int				***map;
	double			*deep_map;
	int				n;
	int				m;
	t_vector		start;
	double			d;
	double			delta;
}					t_params;

typedef struct		s_draw
{
	t_vector		from;
	t_vector		v;
	int				color;
}					t_draw;

#endif
