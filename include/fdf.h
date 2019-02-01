/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbatz <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/06 08:41:58 by kbatz             #+#    #+#             */
/*   Updated: 2019/02/01 11:21:54 by kbatz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <mlx.h>
# include <libc.h>
# include <math.h>
# include "libft.h"

# define CLOSE 0
# define USAGE 1
# define ERROR 2
# define X_ANGLE 0.1
# define Y_ANGLE 0.1

typedef struct		s_point
{
	double			x;
	double			y;
}					t_point;

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
	int				x;
	int				y;
	t_point			shift;
	t_qtrn			q;
	char			alt;
	int				***map;
	int				n;
	int				m;
}					t_params;

#endif
