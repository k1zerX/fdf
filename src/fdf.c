/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbatz <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/06 08:41:09 by kbatz             #+#    #+#             */
/*   Updated: 2019/04/11 19:32:22 by kbatz            ###   ########.fr       */
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

int		ft_alt_key_press(int keycode, t_params *prms)
{
	if (keycode == 123)
		prms->q = mul_qtrn(prms->q, rev_qtrn(*g_qx));
	else if (keycode == 124)
		prms->q = mul_qtrn(prms->q, *g_qx);
	else if (keycode == 125)
		prms->q = mul_qtrn(prms->q, rev_qtrn(*g_qy));
	else if (keycode == 126)
		prms->q = mul_qtrn(prms->q, *g_qy);
	return (0);
}

int		ft_x_press(int keycode, t_params *prms)
{
	if (keycode == 69)
		prms->q = mul_qtrn(prms->q, *g_qx);
	else if (keycode == 78)
		prms->q = mul_qtrn(prms->q, rev_qtrn(*g_qx));
//	ft_draw(prms);
	return (0);
}

int		ft_y_press(int keycode, t_params *prms)
{
	if (keycode == 69)
		prms->q = mul_qtrn(prms->q, *g_qy);
	else if (keycode == 78)
		prms->q = mul_qtrn(prms->q, rev_qtrn(*g_qy));
//	ft_draw(prms);
	return (0);
}

int		ft_z_press(int keycode, t_params *prms)
{
	if (keycode == 69)
		prms->q = mul_qtrn(prms->q, *g_qz);
	else if (keycode == 78)
		prms->q = mul_qtrn(prms->q, rev_qtrn(*g_qz));
//	ft_draw(prms);
	return (0);
}

int		ft_key_press(int keycode, t_params *prms)
{
	if (prms->alt)
		ft_alt_key_press(keycode, prms);
	else if (prms->xturn)
		ft_x_press(keycode, prms);
	else if (prms->yturn)
		ft_y_press(keycode, prms);
	else if (prms->zturn)
		ft_z_press(keycode, prms);
	else if (keycode == 53)
		ft_close(prms);
	else if (keycode == 15)
		ft_initialize(prms);
	else if (keycode == 259)
		prms->alt = 1;
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
	else if (keycode == 7)
		prms->xturn = 1;
	else if (keycode == 16)
		prms->yturn = 1;
	else if (keycode == 6)
		prms->zturn = 1;
	//printf("d = %f\n", prms->d);
	ft_draw(prms);
	return (0);
}

int		ft_key_release(int keycode, t_params *prms)
{
	if (keycode == 7)
		prms->xturn = 0;
	else if (keycode == 16)
		prms->yturn = 0;
	else if (keycode == 6)
		prms->zturn = 0;
//	else if (prms->xturn || prms->yturn || prms->zturn)
//		return (0);
	else if (keycode == 259)
		prms->alt = 0;
	ft_draw(prms);
	return (0);
}

int		ft_mouse_press(int button, int x, int y, t_params *prms)
{
	/*if (prms->xturn)
	{
		if (button == 5)
			prms->q = mul_qtrn(prms->q, *g_qx);
		else if (button == 4)
			prms->q = mul_qtrn(prms->q, rev_qtrn(*g_qx));
	}
	else if (prms->yturn)
	{
		if (button == 5)
			prms->q = mul_qtrn(prms->q, *g_qy);
		else if (button == 4)
			prms->q = mul_qtrn(prms->q, rev_qtrn(*g_qy));
	}
	else if (prms->zturn)
	{
		if (button == 5)
			prms->q = mul_qtrn(prms->q, *g_qz);
		else if (button == 4)
			prms->q = mul_qtrn(prms->q, rev_qtrn(*g_qz));
	}
	else */
	if (button == 1)
	{
		if (x >= 0 && y >= 0 && x < prms->n && y < prms->m)
			prms->click = 1;
		prms->click_p.x = x;
		prms->click_p.y = y;
	}
	else if (button == 4)
	{
		prms->shift.x += (double)(prms->n / 2 - x) / prms->d * (prms->shift.z + prms->d) / K;
		prms->shift.y += (double)(prms->m / 2 - y) / prms->d * (prms->shift.z + prms->d) / K;
		prms->shift.z += g_delta;
		prms->shift.x += (double)(x - prms->n / 2) / prms->d * (prms->shift.z + prms->d) / K;
		prms->shift.y += (double)(y - prms->m / 2) / prms->d * (prms->shift.z + prms->d) / K;
	}
	else if (button == 5)
	{
		prms->shift.x += (double)(prms->n / 2 - x) / prms->d * (prms->shift.z + prms->d) / K;
		prms->shift.y += (double)(prms->m / 2 - y) / prms->d * (prms->shift.z + prms->d) / K;
		prms->shift.z -= g_delta;
		prms->shift.x += (double)(x - prms->n / 2) / prms->d * (prms->shift.z + prms->d) / K;
		prms->shift.y += (double)(y - prms->m / 2) / prms->d * (prms->shift.z + prms->d) / K;
	}
	//printf("z = %f\n", prms->shift.z);
	ft_draw(prms);
	return (0);
}

int		ft_mouse_release(int button, int x, int y, t_params *prms)
{
	if (button == 1)
		prms->click = 0;
	return (0);
}

int		ft_alt_mouse_move(int x, int y, t_params *prms)
{
	t_vector	axis;
	t_qtrn		q;

	if (prms->click)
	{
		axis = turn_vector(get_vector(0, 1, 0), prms->q, 0);
		q = get_qtrn(axis, (double)(x - prms->click_p.x) / 100);
		prms->q = mul_qtrn(prms->q, q);
		axis = turn_vector(get_vector(-1, 0, 0), prms->q, 0);
		q = get_qtrn(axis, (double)(y - prms->click_p.y) / 100);
		prms->q = mul_qtrn(prms->q, q);
		prms->click_p.x = x;
		prms->click_p.y = y;
	}
	return (0);
}

int		ft_x_mouse_move(int x, int y, t_params *prms)
{
	t_vector	v0;
	t_vector	v1;
	t_qtrn		q;
	double		angle;

	if (prms->click)
	{
		v0 = get_vector(prms->click_p.x, prms->click_p.y, 0);
		v0 = turn_vector(v0, prms->q, 0);
		v1 = turn_vector(get_vector(x, y, 0), prms->q, 0);
		v0.x = 0;
		v1.x = 0;
		angle = get_angle(v0, v1);
		printf("%f\n", angle);
		if ((*(unsigned long long int *)&angle & 0x7ff0000000000000) == 0x7ff0000000000000)
			angle = 0;
//		printf("before:\tv0(%f, %f, %f) & v1(%f, %f, %f)\n", v0.x, v0.y, v0.z, v1.x, v1.y, v1.z);
//		v0 = turn_vector(v0, prms->q, 1);
//		v1 = turn_vector(v1, prms->q, 1);
//		printf("after:\tv0(%f, %f, %f) & v1(%f, %f, %f)\n\n", v0.x, v0.y, v0.z, v1.x, v1.y, v1.z);
		q = get_qtrn(get_vector(1, 0, 0), 5 * angle);
		prms->q = mul_qtrn(prms->q, q);
		prms->click_p.x = x;
		prms->click_p.y = y;
	}
	return (0);
}

int		ft_y_mouse_move(int x, int y, t_params *prms)
{
	t_vector	v0;
	t_vector	v1;
	t_qtrn		q;
	double		angle;

	if (prms->click)
	{
		v0 = get_vector(prms->click_p.x, prms->click_p.y, 0);
		v0 = turn_vector(v0, prms->q, 1);
		v1 = turn_vector(get_vector(x, y, 0), prms->q, 1);
		angle = get_angle(v0, v1);
		if ((*(unsigned long long int *)&angle & 0x7ff0000000000000) == 0x7ff0000000000000)
			angle = 0;
		q = get_qtrn(get_vector(0, 1, 0), 5 * angle);
		prms->q = mul_qtrn(prms->q, q);
		prms->click_p.x = x;
		prms->click_p.y = y;
	}
	return (0);
}

int		ft_z_mouse_move(int x, int y, t_params *prms)
{
	t_vector	v0;
	t_vector	v1;
	t_qtrn		q;
	double		angle;

	if (prms->click)
	{
		v0 = get_vector(prms->click_p.x, prms->click_p.y, 0);
		v0 = turn_vector(v0, prms->q, 1);
		v1 = turn_vector(get_vector(x, y, 0), prms->q, 1);
		angle = get_angle(v0, v1);
		if ((*(unsigned long long int *)&angle & 0x7ff0000000000000) == 0x7ff0000000000000)
			angle = 0;
		q = get_qtrn(get_vector(0, 0, 1), 5 * angle);
		prms->q = mul_qtrn(prms->q, q);
		prms->click_p.x = x;
		prms->click_p.y = y;
	}
	return (0);
}

int		ft_mouse_move(int x, int y, t_params *prms)
{
	if (prms->alt)
		ft_alt_mouse_move(x, y, prms);
	else if (prms->xturn)
		ft_x_mouse_move(x, y, prms);
	else if (prms->yturn)
		ft_y_mouse_move(x, y, prms);
	else if (prms->zturn)
		ft_z_mouse_move(x, y, prms);
	else if (prms->click)
	{
		prms->shift.x += (double)(x - prms->click_p.x) / prms->d * (prms->shift.z + prms->d) / K;
		prms->shift.y += (double)(y - prms->click_p.y) / prms->d * (prms->shift.z + prms->d) / K;
		prms->click_p.x = x;
		prms->click_p.y = y;
	}
	ft_draw(prms);
	return (0);
}

void	ft_put_axis(t_params *prms, t_vector axis, int color)
{
	t_vector	from;
	t_vector	buf;
	t_gradient	gr;
	double		alpha;

	buf = axis;
	k_vector(&axis, 10);
	from = add_vector(rev_vector(axis), rev_vector(prms->start));
	axis = add_vector(axis, rev_vector(prms->start));
	gr.from = (int)round((double)(((color >> 16) & 0xff) * 0.25)) << 16;
	gr.from |= (int)round((double)(((color >> 8) & 0xff) * 0.25)) << 8;
	gr.from |= (int)round((double)((color) & 0xff) * 0.25);
	gr.to = color;
	ft_put_line(prms, from, axis);
	from = axis;
	alpha = 0;
	while (alpha < M_PI * 16)
	{
		gr.from = color;
		gr.to = (int)round((double)(((color >> 16) & 0xff) * 0.925)) << 16;
		gr.to |= (int)round((double)(((color >> 8) & 0xff) * 0.925)) << 8;
		gr.to |= (int)round((double)((color) & 0xff) * 0.925);
		axis = from;
		axis.x -= !!buf.x * 2;
		axis.y -= !!buf.y * 2;
		axis.z -= !!buf.z * 2;
		axis.x += !buf.x * (!buf.y * sin(alpha) + !buf.z * cos(alpha));
		axis.y += !buf.y * (!buf.z * sin(alpha) + !buf.x * cos(alpha));
		axis.z += !buf.z * (!buf.x * sin(alpha) + !buf.y * cos(alpha));
		ft_put_line(prms, from, axis);
		alpha += 0.1;
	}
}

void	ft_test(t_params *prms)
{
	t_vector	from;
	t_vector	to;
	t_point		p0;
	t_point		p1;
	t_gradient	gr;

	gr.from = 0x00ffffff;
	gr.to = 0x00ff0000;
	p0.x = -21;
	p0.y = -21;
	p1.x = 20;
	p1.y = 20;
	mlx_clear_window(prms->mlx, prms->win);
//	((int *)prms->img)[99 * prms->n + 99] = 0x000000ff;
//	((int *)prms->img)[100 * prms->n + 99] = 0x0000ff00;
//	((int *)prms->img)[99 * prms->n + 100] = 0x00ff0000;
	from = get_vector(0, 0, 0);
	to = get_vector(p0.x, p0.y, 0);
	while (++to.x < p1.x)
		ft_put_line(prms, from, to);
	ft_put_line(prms, from, to);
	while (++to.y < p1.y)
		ft_put_line(prms, from, to);
	ft_put_line(prms, from, to);
	while (--to.x > p0.x)
		ft_put_line(prms, from, to);
	ft_put_line(prms, from, to);
	while (--to.y > p0.y)
		ft_put_line(prms, from, to);
	ft_put_line(prms, from, to);
}

void	ft_draw(t_params *prms)
{
	int			bits_per_pixel;
	int			size_line;
	int			endian;
	int			i;
	int			j;
	t_vector	from;
	t_vector	to;

	mlx_clear_window(prms->mlx, prms->win);
	prms->img_ptr = mlx_new_image(prms->mlx, prms->n, prms->m);
	prms->img = mlx_get_data_addr(prms->img_ptr, &bits_per_pixel, &size_line, &endian);
	j = -1;
	while (++j < prms->m)
	{
		i = -1;
		while (++i < prms->n)
		{
			prms->img[(j * prms->n + i) * 4 + A] = 0xff;
			prms->deep_map[j * prms->n + i] = -1.0 / 0.0;
//			printf("%f\n", prms->deep_map[j * prms->n + i]);
		}
	}
//	ft_test(prms);
	j = -1;
	while (++j < prms->y -1)
	{
		i = -1;
		while (++i < prms->x - 1)
		{
//			printf("%d, %d\n", i, j);
			from = get_vector(i, j, prms->map[j][i][0]);
			to = get_vector(i + 1, j, prms->map[j][i + 1][0]);
			ft_put_line(prms, from, to);
			to = get_vector(i, j + 1, prms->map[j + 1][i][0]);
			ft_put_line(prms, from, to);
		}
	}
	j = prms->y - 1;
	i = prms->x;
	while (--i > 0)
	{
			from = get_vector(i, j, prms->map[j][i][0]);
			to = get_vector(i - 1, j, prms->map[j][i - 1][0]);
			ft_put_line(prms, from, to);
	}
	i = prms->x - 1;
	j = prms->y;
	while (--j > 0)
	{
			from = get_vector(i, j, prms->map[j][i][0]);
			to = get_vector(i, j - 1, prms->map[j - 1][i][0]);
			ft_put_line(prms, from, to);
	}
	if (prms->xturn)
		ft_put_axis(prms, get_vector(1, 0, 0), RED);
	if (prms->yturn)
		ft_put_axis(prms, get_vector(0, 1, 0), GREEN);
	if (prms->zturn)
		ft_put_axis(prms, get_vector(0, 0, 1), BLUE);
/*	printf("--------------------------------------\n");
	j = -1;
	while (++j < prms->m)
	{
		i = -1;
		while (++i < prms->n)
			if (prms->deep_map[j * prms->n + i] > 0)
				printf("%f\m", prms->deep_map[j * prms->n + i]);
	}
	printf("--------------------------------------\n");*/
	/**/
//	ft_test(prms);
	/**/
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
		//printf("%s\n", str);
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
					//printf("%f / %f = %f\n", (double)map[j][i][0], (double)max, (double)map[j][i][0] / (double)max);
					map[j][i][1] = (int)round(((TOP >> 16) & 0xff) * bk + ((ZERO >> 16) & 0xff) * (1 - bk)) << 16;
					map[j][i][1] |= (int)round(((TOP >> 8) & 0xff) * bk + ((ZERO >> 8) & 0xff) * (1 - bk)) << 8;
					map[j][i][1] |= (int)round((TOP & 0xff) * bk + (ZERO & 0xff) * (1 - bk));
				}
				else if (map[j][i][0] < 0)
				{
					bk = (double)map[j][i][0] / (double)min;
					//printf("%f / %f = %f\n", (double)map[j][i][0], (double)min, (double)map[j][i][0] / (double)min);
					map[j][i][1] = (int)round(((BOT >> 16) & 0xff) * bk + ((ZERO >> 16) & 0xff) * (1 - bk)) << 16;
					map[j][i][1] |= (int)round(((BOT >> 8) & 0xff) * bk + ((ZERO >> 8) & 0xff) * (1 - bk)) << 8;
					map[j][i][1] |= (int)round((BOT & 0xff) * bk + (ZERO & 0xff) * (1 - bk));
				}
			}
			else
				map[j][i][1] &= 0x00ffffff;
			//printf("%#010x\n", map[j][i][1]);
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
//	prms->start.z = 0;
	g_delta = prms->z + 1;
	prms->d = -g_delta * K;
}
/*
нужно учитывать перспективу при расчете точки с которой нужно начинать отрисовывать
ищем самую отдаленную из четырех крайних точек от камеры
*/
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
//	int j = -1;
//	if (prms.map)
//		while (++j < prms.m)
//		{
//			int i = -1;
//			while (++i < prms.n)
//				printf("%d ", prms.map[j][i][0]);
//			printf("\n");
//		}
	ft_initialize(&prms);
	prms.mlx = mlx_init();
	prms.win = mlx_new_window(prms.mlx, prms.n, prms.m, "mlx 42");
	ft_draw(&prms);
	mlx_hook(prms.win, 2, 0, &ft_key_press, &prms);
	mlx_hook(prms.win, 3, 0, &ft_key_release, &prms);
	mlx_hook(prms.win, 4, 0, &ft_mouse_press, &prms);
	mlx_hook(prms.win, 5, 0, &ft_mouse_release, &prms);
	mlx_hook(prms.win, 6, 0, &ft_mouse_move, &prms);
	mlx_hook(prms.win, 17, 0, &ft_close, &prms);
	mlx_loop(prms.mlx);
	return (0);
}
