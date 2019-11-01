/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkathlee <dkathlee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/01 15:47:26 by dkathlee          #+#    #+#             */
/*   Updated: 2019/11/01 18:29:09 by dkathlee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_color		rand_color()
{
	t_color	res;
	
	res.r = rand() % 205 + 50;
	res.g = rand() % 205 + 50;
	res.b = rand() % 205 + 50;
	res.a = 0;
	return (res);
}

static void	p3d_calc_color(t_point3d *p, t_map *m)
{
	p->color.r = m->min_color.r + (m->min_color.r - m->max_color.r) *
							((p->z - m->min_z) / ABS(m->max_z - m->min_z));
	p->color.g = m->min_color.g + (m->min_color.g - m->max_color.g) *
							((p->z - m->min_z) / ABS(m->max_z - m->min_z));
	p->color.b = m->min_color.b + (m->min_color.b - m->max_color.b) *
							((p->z - m->min_z) / ABS(m->max_z - m->min_z));
}

t_color		calc_pixel_color(t_point2d *st_p, t_point2d *end_p, t_point2d *cur_p)
{
	int		start;
	int		end;
	int		current;
	float	percentage;

	if (end_p->x - st_p->x > end_p->y - st_p->y)
	{
		start = st_p->x;
		end = end_p->x;
		current = cur_p->x;
	}
	else
	{
		start = st_p->y;
		end = end_p->y;
		current = cur_p->y;
	}
	percentage = (end - start == 0) ? 1.0 : (current - start) / (float)(end - start);
	cur_p->color.r = (1 - percentage) * (float)st_p->color.r + percentage * (float)end_p->color.r;
	cur_p->color.g = (1 - percentage) * st_p->color.g + percentage * end_p->color.g;
	cur_p->color.b = (1 - percentage) * st_p->color.b + percentage * end_p->color.b;
	cur_p->color.a = 0;
}

void		colorize_points(t_map *m)
{
	int			i;
	int			j;
	
	i = 0;
	while (i < m->h)
	{
		j = 0;
		while (j < m->w)
		{
			p3d_calc_color(m->points3d[i] + j, m);
			j++;
		}
		i++;
	}
}
