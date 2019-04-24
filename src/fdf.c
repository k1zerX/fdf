/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbatz <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/06 08:41:09 by kbatz             #+#    #+#             */
/*   Updated: 2019/04/24 17:12:44 by kbatz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_qtrn			*g_qx = NULL;
t_qtrn			*g_qy = NULL;
t_qtrn			*g_qz = NULL;
double			g_delta;

void	ft_draw(t_params *prms);
void	ft_initialize(t_params *prms);

void	ft_exit(int status, t_params *prms)
{
	int		i;

	if (status == USAGE)
		write(1, "usage:\n\t./fdf [file_name]\n\t./fdf [file_name] [size_x > 0] [size_y > 0]\n", 71);
	else if (status == CLOSE || status == ERROR || status == READ_ERROR)
	{
		while (prms->y-- > 0)
		{
			i = prms->x;
			while (i-- > 0)
				free(prms->map[prms->y][i]);
			free(prms->map[prms->y]);
		}
		free(prms->map);
		free(g_qx);
		free(g_qy);
		if (status != READ_ERROR)
		{
			mlx_destroy_window(prms->mlx, prms->win);
			free(prms->deep_map);
		}
		if (status == ERROR || status == READ_ERROR)
			write(2, "Error\n", 6);
	}
	exit(0);
}

int		ft_close(t_params *prms)
{
	ft_exit(CLOSE, prms);
	return (0);
}

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
		g_delta *= 0.8;
	}
	else if (keycode == 78)
	{
		prms->d *= 1.25;
		prms->shift.z *= 1.25;
		g_delta *= 1.25;
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
		prms->shift.z += g_delta;
	else if (button == 5)
		prms->shift.z -= g_delta;
	ft_draw(prms);
	return (0);
}

int		ft_mouse_release(int button, int x, int y, t_params *prms)
{
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
		prms->shift.x += (double)(x - prms->rmb_p.x) / prms->d * (prms->shift.z + prms->d) / K;
		prms->shift.y += (double)(y - prms->rmb_p.y) / prms->d * (prms->shift.z + prms->d) / K;
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

void	put_sector(t_params *prms, int i, int j)
{
	t_vector from;
	t_vector to;

	from = get_vector(i, j, prms->map[j][i][0]);
	if (i + 1 < prms->x)
	{
		to = get_vector(i + 1, j, prms->map[j][i + 1][0]);
		ft_put_line(prms, from, to);
	}
	if (j + 1 < prms->y)
	{
		to = get_vector(i, j + 1, prms->map[j + 1][i][0]);
		ft_put_line(prms, from, to);
	}
}

void	ft_draw(t_params *prms)
{
	int			i;
	int			j;

	mlx_clear_window(prms->mlx, prms->win);
	j = -1;
	while (++j < prms->m)
	{
		i = -1;
		while (++i < prms->n)
		{
			prms->img[(j * prms->n + i) * 4 + A] = 0xff;
			prms->deep_map[j * prms->n + i] = -1.0 / 0.0;
		}
	}
	j = -1;
	while (++j < prms->y)
	{
		i = -1;
		while (++i < prms->x)
			put_sector(prms, i, j);
	}
	mlx_put_image_to_window(prms->mlx, prms->win, prms->img_ptr, 0, 0);
}

void	fill_map_elem(int *elem, char **str)
{
	char	sign;

	sign = 1;
	if (**str == '-' || **str == '+')
		sign = 44 - *(*str)++;
	while (ft_isdigit(**str))
		elem[0] = elem[0] * 10 + *(*str)++ - '0';
	elem[0] *= sign;
	while (ft_isspace(**str))
		(*str)++;
	if (*(*str) == ',')
	{
		(*str)++;
		while (ft_isspace(**str))
			(*str)++;
		(*str) += 2;
		while (ft_isdigit(*(++*str)) || \
				(ft_tolower(**str) >= 'a' && ft_tolower(**str) <= 'f'))
		{
			elem[1] <<= 4;
			if (ft_isdigit(**str))
				elem[1] |= **str - '0';
			else
				elem[1] |= **str - 'a' + 10;
		}
	}
}

void	ft_read(int fd, t_params *prms)
{
	char	*str;
	char	*buf;
	char	b;
	int		***map;
	int		len;
	int		k;
	int		min;
	int		max;
	int		i;
	int		j;
	double	bk;

	map = NULL;
	len = 0;
	while ((b = get_next_line(fd, &buf)) > 0)
	{
		str = buf;
		map = ft_realloc(map, sizeof(*map) * len, 1);
		k = 0;
		while (*str)
		{
			while (ft_isspace(*str))
				str++;
			if (*str == '-' || *str == '+' || ft_isdigit(*str))
			{
				map[len] = ft_realloc(map[len], sizeof(**map) * k, 1);
				map[len][k] = ft_memalloc(sizeof(***map) * 2);
				fill_map_elem(map[len][k++], &str);
				if (!len && !(k - 1))
				{
					min = map[len][k - 1][0];
					max = min;
				}
				else if (map[len][k - 1][0] < min)
					min = map[len][k - 1][0];
				else if (map[len][k - 1][0] > max)
					max = map[len][k - 1][0];
			}
		}
		len++;
		free(buf);
		if (!prms->x)
			prms->x = k;
		else if (prms->x != k)
		{
			prms->map = map;
			prms->y = len - 1;
			close(fd);
			while (k-- > 0)
				free(map[prms->y][k]);
			free(map[prms->y]);
			ft_exit(READ_ERROR, prms);
		}
	}
	close(fd);
	prms->map = map;
	prms->y = len;
	if (b == -1)
		ft_exit(READ_ERROR, prms);
	j = len;
	while (j-- > 0)
	{
		i = k;
		while (i-- > 0)
		{
			if (!map[j][i][1])
			{
				if (!map[j][i][0])
					map[j][i][1] = ZERO;
				else if (map[j][i][0] > 0)
				{
					bk = (double)map[j][i][0] / (double)max;
					map[j][i][1] = (int)round(((TOP >> 16) & 0xff) * bk + ((ZERO >> 16) & 0xff) * (1 - bk)) << 16;
					map[j][i][1] |= (int)round(((TOP >> 8) & 0xff) * bk + ((ZERO >> 8) & 0xff) * (1 - bk)) << 8;
					map[j][i][1] |= (int)round((TOP & 0xff) * bk + (ZERO & 0xff) * (1 - bk));
				}
				else if (map[j][i][0] < 0)
				{
					bk = (double)map[j][i][0] / (double)min;
					map[j][i][1] = (int)round(((BOT >> 16) & 0xff) * bk + ((ZERO >> 16) & 0xff) * (1 - bk)) << 16;
					map[j][i][1] |= (int)round(((BOT >> 8) & 0xff) * bk + ((ZERO >> 8) & 0xff) * (1 - bk)) << 8;
					map[j][i][1] |= (int)round((BOT & 0xff) * bk + (ZERO & 0xff) * (1 - bk));
				}
			}
			else
				map[j][i][1] &= 0x00ffffff;
			map[j][i][0] -= min;
		}
	}
	max -= min;
	prms->z = max;
}

void	ft_initialize(t_params *prms)
{
	if (!(g_qx = malloc(sizeof(*g_qx))))
		ft_exit(ERROR, prms);
	*g_qx = get_qtrn(get_vector(1, 0, 0), ANGLE);
	if (!(g_qy = malloc(sizeof(*g_qy))))
		ft_exit(ERROR, prms);
	*g_qy = get_qtrn(get_vector(0, 1, 0), ANGLE);
	if (!(g_qz = malloc(sizeof(*g_qz))))
		ft_exit(ERROR, prms);
	*g_qz = get_qtrn(get_vector(0, 0, 1), ANGLE);
	if (!prms->n || !prms->m)
	{
		prms->n = 1000;
		prms->m = 1000;
	}
	if (!prms->deep_map)
		prms->deep_map = ft_memalloc(prms->n * prms->m * sizeof(*prms->deep_map));
	prms->q = get_qtrn(get_vector(1, 0, 0), M_PI * 2 / 3);
	prms->q = mul_qtrn(prms->q, get_qtrn(get_vector(0, 1, 0), M_PI * 2 / 3));
	prms->q = get_qtrn(get_vector(1, 0, 0), 0);
	ft_bzero(&prms->shift, sizeof(prms->shift));
	prms->start.x = -(double)(prms->x - 1) / 2;
	prms->start.y = -(double)(prms->y - 1) / 2;
	prms->start.z = -(double)prms->z / 2;
	g_delta = prms->z + 1;
	prms->d = -g_delta * K;
}

void	get_img(t_params *prms)
{
	int			bits_per_pixel;
	int			size_line;
	int			endian;

	prms->mlx = mlx_init();
	prms->win = mlx_new_window(prms->mlx, prms->n, prms->m, "mlx 42");
	prms->img_ptr = mlx_new_image(prms->mlx, prms->n, prms->m);
	prms->img = mlx_get_data_addr(prms->img_ptr, &bits_per_pixel, &size_line, &endian);
}
int		main(int ac, char **av)
{
	t_params	prms;
	int			**map;

	ft_bzero(&prms, sizeof(prms));
	if (ac != 2 && ac != 4)
		ft_exit(1, NULL);
	if (ac == 4)
	{
		prms.n = ft_atoi(av[2]);
		prms.m = ft_atoi(av[3]);
		if (!prms.n || !prms.m)
			ft_exit(1, NULL);
	}
	ft_read(open(av[1], O_RDONLY), &prms);
	ft_initialize(&prms);
	get_img(&prms);
	ft_draw(&prms);
	mlx_hook(prms.win, 2, 0, &ft_key_press, &prms);
	mlx_hook(prms.win, 4, 0, &ft_mouse_press, &prms);
	mlx_hook(prms.win, 5, 0, &ft_mouse_release, &prms);
	mlx_hook(prms.win, 6, 0, &ft_mouse_move, &prms);
	mlx_hook(prms.win, 17, 0, &ft_close, &prms);
	mlx_loop(prms.mlx);
	return (0);
}
