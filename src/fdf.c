/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbatz <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/06 08:41:09 by kbatz             #+#    #+#             */
/*   Updated: 2019/02/15 21:44:05 by kbatz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_qtrn			*g_qx = NULL;
t_qtrn			*g_qy = NULL;
t_qtrn			*g_qz = NULL;
int				g_shift = 0;

void		ft_draw(t_params *prms);

void	ft_exit(int status, t_params *prms)
{
	int		i;

	if (status == USAGE)
		write(1, "usage:\n\t./fdf [file_name]\n\t./fdf [file_name] [size_x > 0] [size_y > 0]\n", 71);
	else if (status == CLOSE || status == ERROR || status == READ_ERROR)
	{
		while (prms->m-- > 0)
		{
			i = prms->n;
			while (i-- > 0)
				free(prms->map[prms->m][i]);
			free(prms->map[prms->m]);
		}
		free(prms->map);
		free(g_qx);
		free(g_qy);
		if (status != READ_ERROR)
			mlx_destroy_window(prms->mlx, prms->win);
		if (status == ERROR || status == READ_ERROR)
			write(2, "Error\n", 6);
	}
	exit(0);
}

int			ft_close(t_params *prms)
{
	ft_exit(CLOSE, prms);
	return (0);
}

void		ft_initialize(t_params *prms)
{
	t_vector		axis;

	if (!(g_qx = malloc(sizeof(*g_qx))))
		ft_exit(ERROR, prms);
	axis.x = 1;
	axis.y = 0;
	axis.z = 0;
	*g_qx = get_qtrn(axis, ANGLE);
	if (!(g_qy = malloc(sizeof(*g_qy))))
		ft_exit(ERROR, prms);
	axis.x = 0;
	axis.y = 1;
	axis.z = 0;
	*g_qy = get_qtrn(axis, ANGLE);
	if (!(g_qz = malloc(sizeof(*g_qz))))
		ft_exit(ERROR, prms);
	axis.x = 0;
	axis.y = 0;
	axis.z = 1;
	*g_qz = get_qtrn(axis, ANGLE);
	if (!prms->x || !prms->y)
	{
		prms->x = 1000;
		prms->y = 1000;
	}
	prms->shift.x = prms->x / 2;
	prms->shift.y = prms->y / 2;
	prms->q.w = 1;
	ft_bzero(&prms->q.v, sizeof(prms->q.v));
	g_shift = (int)sqrt(prms->x * prms->y) / 40;
	k_qtrn(&prms->q, 2);
}

int			ft_alt_key_press(int keycode, t_params *prms)
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

int			ft_x_press(int keycode, t_params *prms)
{
	if (keycode == 69)
		prms->q = mul_qtrn(prms->q, *g_qx);
	else if (keycode == 78)
		prms->q = mul_qtrn(prms->q, rev_qtrn(*g_qx));
	ft_draw(prms);
	return (0);
}

int			ft_y_press(int keycode, t_params *prms)
{
	if (keycode == 69)
		prms->q = mul_qtrn(prms->q, *g_qy);
	else if (keycode == 78)
		prms->q = mul_qtrn(prms->q, rev_qtrn(*g_qy));
	ft_draw(prms);
	return (0);
}

int			ft_z_press(int keycode, t_params *prms)
{
	if (keycode == 69)
		prms->q = mul_qtrn(prms->q, *g_qz);
	else if (keycode == 78)
		prms->q = mul_qtrn(prms->q, rev_qtrn(*g_qz));
	ft_draw(prms);
	return (0);
}

int			ft_key_press(int keycode, t_params *prms)
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
	else if (keycode == 259)
		prms->alt = 1;
	else if (keycode == 123)
		prms->shift.x -= g_shift;
	else if (keycode == 124)
		prms->shift.x += g_shift;
	else if (keycode == 125)
		prms->shift.y += g_shift;
	else if (keycode == 126)
		prms->shift.y -= g_shift;
	else if (keycode == 7)
		prms->xturn = 1;
	else if (keycode == 16)
		prms->yturn = 1;
	else if (keycode == 6)
		prms->zturn = 1;
	ft_draw(prms);
	return (0);
}

int			ft_key_release(int keycode, t_params *prms)
{
	if (keycode == 7)
		prms->xturn = 0;
	else if (keycode == 16)
		prms->yturn = 0;
	else if (keycode == 6)
		prms->zturn = 0;
	else if (prms->xturn || prms->yturn || prms->zturn)
		return (0);
	else if (keycode == 259)
		prms->alt = 0;
	else if (keycode == 69)
		k_qtrn(&prms->q, 1.25);
	else if (keycode == 78)
		k_qtrn(&prms->q, 0.8);
	ft_draw(prms);
	return (0);
}

int		ft_mouse_press(int button, int x, int y, t_params *prms)
{
	if (prms->xturn)
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
	else if (button == 4)
		k_qtrn(&prms->q, 1.25);
	else if (button == 5)
		k_qtrn(&prms->q, 0.8);
	ft_draw(prms);
	return (0);
}

void	ft_put_axis(t_params *prms)
{
	t_vector	x;
	t_vector	y;
	t_vector	z;
	t_vector	start;
	double		alpha;
	double		step;
	t_vector	v;
	t_gradient	gr;

	step = 0.1;
	ft_bzero(&x, sizeof(t_vector));
	ft_bzero(&y, sizeof(t_vector));
	ft_bzero(&z, sizeof(t_vector));
	start.x = 0;
	start.y = 0;
	start.z = 0;
	x.x = 20;
	y.y = 20;
	z.z = 20;
	x = add_vector(x, start);
	y = add_vector(y, start);
	z = add_vector(z, start);
	gr.from = 0x00ff0000;
	gr.to = 0x00ff0000;
	ft_put_line(prms, start, x, gr);
	alpha = 0;
	while (alpha < M_PI * 2)
	{
		v.x = -3;
		v.z = sin(alpha);
		v.y = cos(alpha);
		k_vector(&v, 0.5);
		v = add_vector(v, x);
		ft_put_line(prms, x, v, gr);
		alpha += step;
	}
	gr.from = 0x0000ff00;
	gr.to = 0x0000ff00;
	ft_put_line(prms, start, y, gr);
	alpha = 0;
	while (alpha < M_PI * 2)
	{
		v.x = sin(alpha);
		v.y = -3;
		v.z = cos(alpha);
		k_vector(&v, 0.5);
		v = add_vector(v, y);
		ft_put_line(prms, y, v, gr);
		alpha += step;
	}
	gr.from = 0x000000ff;
	gr.to = 0x000000ff;
	ft_put_line(prms, start, z, gr);
	alpha = 0;
	while (alpha < M_PI * 2)
	{
		v.x = sin(alpha);
		v.y = cos(alpha);
		v.z = -3;
		k_vector(&v, 0.5);
		v = add_vector(v, z);
		ft_put_line(prms, z, v, gr);
		alpha += step;
	}
	gr.from = 0x00707070;
	gr.to = 0x00707070;
	ft_put_line(prms, start, start, gr);
}

t_draw	*new_draw(t_params *prms, t_vector v)
{
	t_draw	*tmp;

	tmp = malloc(sizeof(*tmp));
	tmp->v = v;
	tmp->color = prms->map[(int)tmp->v.y][(int)tmp->v.x][1];
	return (tmp);
}

void	ft_draw(t_params *prms)
{
	int			color;
	t_vector	axis;
	t_vector	v;
	t_vector	from;
	t_qtrn		q;
	t_draw		*tmp;
	t_elem		*elem;
	t_queue		*queue;
	t_draw		*buf;
	t_gradient	gr;

	g_shift = (int)sqrt(prms->x * prms->y) / 200 * mod_qtrn(prms->q);
	mlx_clear_window(prms->mlx, prms->win);
	ft_put_axis(prms);
	from.x = 0.0;
	from.y = 0.0;
	from.z = prms->map[0][0][0];
	queue = ft_queue_new();
	buf = new_draw(prms, from);
	ft_queue_push(queue, ft_new_elem(buf, sizeof(*buf), 0));
	while (queue->len)
	{
		elem = ft_queue_pop(queue);
		tmp = (t_draw *)elem->content;
		from = tmp->v;
		gr.from = tmp->color;
		//printf("\nfrom: %f, %f, %f\n", from.x, from.y, from.z);
		tmp->v.x += 1;
		if (tmp->v.x < prms->n)
		{
			tmp->v.z = prms->map[(int)tmp->v.y][(int)tmp->v.x][0];
			gr.to = prms->map[(int)tmp->v.y][(int)tmp->v.x][1];
			//printf("v: %f, %f, %f\n", v.x, v.y, v.z);
			//printf("%.0f < %.0f ||| %.0f, %.0f => %.0f\n", tmp->v.y, prms->m, tmp->v.x, tmp->v.y, tmp->v.z);
			ft_put_line(prms, from, tmp->v, gr);
			buf = new_draw(prms, tmp->v);
			ft_queue_push(queue, ft_new_elem(buf, sizeof(*buf), 0));
		}
		tmp->v.x -= 1;
		tmp->v.y += 1;
		if (tmp->v.y < prms->m)
		{
			//printf("v: %f, %f, %f\n", v.x, v.y, v.z);
			tmp->v.z = prms->map[(int)tmp->v.y][(int)tmp->v.x][0];
			gr.to = prms->map[(int)tmp->v.y][(int)tmp->v.x][1];
			//printf("%.0f < %.0f ||| %.0f, %.0f => %.0f\n", tmp->v.y, prms->m, tmp->v.x, tmp->v.y, tmp->v.z);
			ft_put_line(prms, from, tmp->v, gr);
			if (!tmp->v.x)
			{
				buf = new_draw(prms, tmp->v);
				ft_queue_push(queue, ft_new_elem(buf, sizeof(*buf), 0));
			}
		}
		tmp->v.y -= 1;
		free(tmp);
		free(elem);
	}
	free(queue);
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
	if (*(*str) == ',')
	{
		(*str) += 3;
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

void	ft_read(char *file, t_params *prms)
{
	int		fd;
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
	fd = open(file, O_RDONLY);
	while ((b = get_next_line(fd, &buf) > 0))
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
		if (!prms->n)
			prms->n = k;
		else if (prms->n != k)
		{
			prms->map = map;
			prms->m = len - 1;
			close(fd);
			while (k-- > 0)
				free(map[prms->m][k]);
			free(map[prms->m]);
			ft_exit(READ_ERROR, prms);
		}
	}
	close(fd);
	prms->map = map;
	prms->m = len;
	if (b == -1)
		ft_exit(ERROR, prms);
	j = len;
	while (j-- > 0)
	{
		i = k;
		while (i-- > 0)
			if (!map[j][i][1])
			{
				if (min == max)
					bk = 0.5;
				else
					bk = (double)(map[j][i][0] - min) / (double)(max - min);
				map[j][i][1] = ((int)round(0xff * (1 - bk)) << 16) | (int)round(0xff * bk);
			}
			else
				map[j][i][1] &= 0x00ffffff;
	}
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
	ft_read(av[1], &prms);
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
	prms.win = mlx_new_window(prms.mlx, prms.x, prms.y, "mlx 42");
	ft_draw(&prms);
	mlx_hook(prms.win, 2, 0, &ft_key_press, &prms);
	mlx_hook(prms.win, 3, 0, &ft_key_release, &prms);
	mlx_hook(prms.win, 4, 0, &ft_mouse_press, &prms);
	mlx_hook(prms.win, 17, 0, &ft_close, &prms);
	mlx_loop(prms.mlx);
	return (0);
}
