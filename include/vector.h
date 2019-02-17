/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbatz <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/15 18:58:04 by kbatz             #+#    #+#             */
/*   Updated: 2019/02/17 04:05:12 by kbatz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_H
# define VECTOR_H

#include "fdf.h"

void		k_vector(t_vector *v, double k);
t_vector	add_vector(t_vector a, t_vector b);
t_vector	turn_vector(t_vector v, t_qtrn q, char clockwise);
double		mod_vector(t_vector v);
t_vector	rev_vector(t_vector v);
double		scalar_mul(t_vector a, t_vector b);
double		get_angle(t_vector a, t_vector b);
t_vector	vector_mul(t_vector a, t_vector b);
void		project_vector(t_vector *a, t_vector b);

#endif
