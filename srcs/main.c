/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkathlee <dkathlee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/18 02:39:25 by marvin            #+#    #+#             */
/*   Updated: 2019/10/24 16:50:59 by dkathlee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		prepare_points(t_point2D *p1, t_point2D *p2)
{
	int tmp;
	int ret;
	
	ret = 0;
	if (ABS(((p2->Y) - (p1->Y))) > ABS(((p2->X) - (p1->X))))
	{
		tmp = p1->X;
		p1->X = p1->Y;
		p1->Y = tmp;
		tmp = p2->X;
		p2->X = p2->Y;
		p2->Y = tmp;
		ret = 1;
	}
	if (p1->X > p2->X)
	{
		tmp = p1->X;
		p1->X = p2->X;
		p2->X = tmp;
		tmp = p1->Y;
		p1->Y = p2->Y;
		p2->Y = tmp;
	}
	return (ret);
}

void	draw_line(t_point2D *p1, t_point2D *p2, t_view *param)
{
	int	error;
	int	derr;
	int	dir;
	int	dx;
	int flag;
	
	flag = prepare_points(p1, p2);
	dx = (ABS((p1->X - p2->X)));
	dir = p2->Y - p1->Y;
	derr = (ABS(dir));
	dir = dir > 0 ? 1 : -1;
	error = 0;
	while ((p1->X) <= p2->X)
	{
		if (flag == 1)
			mlx_pixel_put(param->mlx_ptr, param->win_ptr, p1->Y, p1->X, 255);
		else
			mlx_pixel_put(param->mlx_ptr, param->win_ptr, p1->X, p1->Y, 255);	
		error += derr;
		if (2 * error >= derr)
		{
			p1->Y += dir;
			error -= dx;
		}
		(p1->X)++;
	}
}

t_point2D	*iso(t_point3D *p)
{
	t_point2D	*newP;

	newP = ft_memalloc(sizeof(t_point2D));
	newP->color = p->color;
	newP->X = (p->X - p->Y) * cos(RAD(35.26));
	newP->Y = (p->Z) + (p->X + p->Y) * sin(RAD(35.26));
	return (newP);
}

void	p3D_transform(t_map *map, float value, void (tr)(t_point3D*, float))
{
	int i;
	int j;

	i = 0;
	while (i < map->Height)
	{
		j = 0;
		while (j < map->Width)
		{
			tr((map->points3D)[i] + j, value);
			j++;
		}
		i++;
	}
}

void	p3D_rotate(t_point3D *p, float angle)
{
	/*if (ax == X)
	{*/
		p->X = p->X * cos(RAD(angle)) - p->Y * sin(RAD(angle));
		p->Y = p->X * sin(RAD(angle)) + p->Y * cos(RAD(angle));
	/*}
	else if (ax == Y)
	{
		p->Y = p->Y * cos(RAD(angle)) - p->Z * sin(RAD(angle));
		p->Y = p->Y * sin(RAD(angle)) + p->Z * cos(RAD(angle));
	}
	else if (ax == Z)
	{
		p->X = p->X * cos(RAD(angle)) + p->Z * sin(RAD(angle));
		p->Z = p->Z * cos(RAD(angle)) + p->X * sin(RAD(angle));
	}*/
}

void	draw_map(t_view *v)
{
	int i;
	int j;

	i = 0;
	while (i < v->map->Height)
	{
		j = 0;
		while (j < v->map->Width)
		{
			if (j < v->map->Width - 1)
				draw_line(iso((v->map->points3D)[i] + j), iso((v->map->points3D)[i] + j + 1), v);
			if (i < v->map->Height - 1)
				draw_line(iso((v->map->points3D)[i] + j), iso((v->map->points3D)[i + 1] + j), v);
			j++;
		}
		i++;
	}
}

int mouse_hook(int button, int X, int Y, t_view *param)
{
	/*
	t_point2D	p;
	
	p.X = X;
	p.Y = Y;
	if (param->prevP == NULL)
		param->prevP = ft_memalloc(sizeof(t_point2D));
	else
		draw_line(&p, param->prevP, param);
	param->prevP->X = X;
	param->prevP->Y = Y;*/
	if (button == 4)
		p3D_transform(param->map, 1.0, &p3D_rotate);
	if (button == 5)
		p3D_transform(param->map, -1.0, &p3D_rotate);
	mlx_clear_window(param->mlx_ptr, param->win_ptr);
	draw_map(param);
	return (1);
}

int	main(int ac, char **av)
{
	t_view *v;

	v = ft_memalloc(sizeof(t_view));
	v->mlx_ptr = mlx_init();
	v->win_ptr = mlx_new_window(v->mlx_ptr, WIDTH, HEIGHT, "FdF");
	v->map = ft_memalloc(sizeof(t_map));
	/*v->map->points3D = ft_memalloc(sizeof(t_point3D*));
	v->prevP = NULL;
	(v->map->points3D)[0] = ft_memalloc(sizeof(t_point3D)*3);
	(v->map->points3D)[0][0].X = 0;
	(v->map->points3D)[0][0].Y = 0;
	(v->map->points3D)[0][0].Z = 0;
	(v->map->points3D)[0][1].X = 50;
	(v->map->points3D)[0][1].Y = 0;
	(v->map->points3D)[0][1].Z = 0;
	(v->map->points3D)[0][2].X = 0;
	(v->map->points3D)[0][2].Y = 0;
	(v->map->points3D)[0][2].Z = -50;
	printf("p1: %f, %f\n", iso((v->map->points3D)[0])->X, iso((v->map->points3D)[0])->Y);
	printf("p2: %f, %f\n", iso((v->map->points3D)[0] + 1)->X, iso((v->map->points3D)[0] + 1)->Y);
	printf("p3: %f, %f\n", iso((v->map->points3D)[0] + 2)->X, iso((v->map->points3D)[0] + 2)->Y);
	draw_line(iso((v->map->points3D)[0]), iso((v->map->points3D)[0] + 1), v);
	draw_line(iso((v->map->points3D)[0] + 1), iso((v->map->points3D)[0] + 2), v);
	draw_line(iso((v->map->points3D)[0] + 2), iso((v->map->points3D)[0]), v);*/
	if (read_map(av[1], v->map) != 1)
		ft_putendl("Error reading");
	draw_map(v);
	mlx_mouse_hook(v->win_ptr, &mouse_hook, v);
	mlx_loop(v->mlx_ptr);
	return (0);
}
