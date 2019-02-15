/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbatz <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/15 18:58:04 by kbatz             #+#    #+#             */
/*   Updated: 2019/02/15 19:05:18 by kbatz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_H
# define VECTOR_H

#include "fdf.h"

void		k_vector(t_vector *v, double k);
t_vector	add_vector(t_vector a, t_vector b);
t_vector	turn_vector(t_vector v, t_qtrn q, char clockwise);
double		mod_vector(t_vector v);

#endif
