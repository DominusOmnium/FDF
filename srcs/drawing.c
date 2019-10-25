/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkathlee <dkathlee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/25 13:04:27 by dkathlee          #+#    #+#             */
/*   Updated: 2019/10/25 17:26:54 by dkathlee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	prepare_points(t_point2D *p1, t_point2D *p2)
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

void		draw_line(t_point2D *p1, t_point2D *p2, t_view *param)
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

void		draw_map(t_view *v)
{
	int i;
	int j;
	t_point2D	*p1;
	t_point2D	*p2;

	i = 0;
	while (i < v->map->Height)
	{
		j = 0;
		while (j < v->map->Width)
		{
			if (j < v->map->Width - 1)
			{
				p1 = iso((v->map->points3D)[i] + j);
				p2 = iso((v->map->points3D)[i] + j + 1);/*
				p1->X += WIDTH / 2;
				p1->Y += HEIGHT / 2;
				p2->X += WIDTH / 2;
				p2->Y += HEIGHT / 2;*/
				draw_line(p1, p2, v);
			}
			if (i < v->map->Height - 1)
			{
				p1 = iso((v->map->points3D)[i] + j);
				p2 = iso((v->map->points3D)[i + 1] + j);/*
				p1->X += WIDTH / 2;
				p1->Y += HEIGHT / 2;
				p2->X += WIDTH / 2;
				p2->Y += HEIGHT / 2;*/
				draw_line(p1, p2, v);
			}
			j++;
		}
		i++;
	}
}
