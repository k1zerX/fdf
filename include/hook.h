/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbatz <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/24 17:49:22 by kbatz             #+#    #+#             */
/*   Updated: 2019/04/24 17:57:57 by kbatz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HOOK_H
# define HOOK_H

int		ft_key_press(int keycode, t_params *prms);
int		ft_mouse_press(int button, int x, int y, t_params *prms);
int		ft_mouse_release(int button, int x, int y, t_params *prms);
int		ft_mouse_move(int x, int y, t_params *prms);

#endif
