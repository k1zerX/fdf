/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   qtrn.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbatz <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/15 18:49:11 by kbatz             #+#    #+#             */
/*   Updated: 2019/02/15 19:21:42 by kbatz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef QTRN_H
# define QTRN_H

# include "fdf.h"

double		mod_qtrn(t_qtrn q);
t_qtrn		rev_qtrn(t_qtrn q);
void		k_qtrn(t_qtrn *q, double k);
t_qtrn		get_qtrn(t_vector axis, double alpha);
t_qtrn		mul_qtrn(t_qtrn a, t_qtrn b);

#endif
