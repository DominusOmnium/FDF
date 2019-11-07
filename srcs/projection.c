/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkathlee <dkathlee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/31 14:35:23 by dkathlee          #+#    #+#             */
/*   Updated: 2019/11/07 14:15:22 by dkathlee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void				p3d_rotate_x(float *y, float *z, float angle)
{
	float		prev_y;
	float		prev_z;

	prev_y = *y;
	prev_z = *z;
	*y = (prev_y * cos(RAD(angle)) - prev_z * sin(RAD(angle)));
	*z = (prev_y * sin(RAD(angle)) + prev_z * cos(RAD(angle)));
}

void				p3d_rotate_y(float *x, float *z, float angle)
{
	float		prev_x;
	float		prev_z;

	prev_x = *x;
	prev_z = *z;
	*x = (prev_x * cos(RAD(angle)) + prev_z * sin(RAD(angle)));
	*z = (prev_z * cos(RAD(angle)) - prev_x * sin(RAD(angle)));
}

void				p3d_rotate_z(float *x, float *y, float angle)
{
	float		prev_x;
	float		prev_y;

	prev_x = *x;
	prev_y = *y;
	*x = (prev_x * cos(RAD(angle)) - prev_y * sin(RAD(angle)));
	*y = (prev_x * sin(RAD(angle)) + prev_y * cos(RAD(angle)));
}

static t_point2d	make_projection(t_point3d p, t_projection_type pr_t)
{
	t_point2d	new_p;

	new_p.color = p.color;
	if (pr_t == ISO)
	{
		new_p.x = (p.x - p.y) * COS30;
		new_p.y = -(p.z) + (p.x + p.y) * SIN30;
	}
	else if (pr_t == Parallel)
	{
		new_p.x = p.x;
		new_p.y = p.y;
	}
	return (new_p);
}

t_point2d			project(t_point3d p, t_view *v)
{
	t_point2d	p2d;
	t_transform	tr;

	tr = v->transform;
	p.x -= v->map->w / 2;
	p.y -= v->map->h / 2;
	p.x *= tr.scale.x;
	p.y *= tr.scale.y;
	p.z *= tr.scale.z;
	if (tr.rotation.x != 0)
		p3d_rotate_x(&p.y, &p.z, tr.rotation.x);
	if (tr.rotation.y != 0)
		p3d_rotate_y(&p.x, &p.z, tr.rotation.y);
	if (tr.rotation.z != 0)
		p3d_rotate_z(&p.x, &p.y, tr.rotation.z);
	p.x += tr.translation.x;
	p.y += tr.translation.y;
	p.z += tr.translation.z;
	p2d = make_projection(p, v->projection);
	p2d.x += (WIDTH - MENU_WIDTH) / 2 + MENU_WIDTH;
	p2d.y += HEIGHT / 2 + (v->map->max_z) * tr.scale.z / 2;
	return (p2d);
}
