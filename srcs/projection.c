/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkathlee <dkathlee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/31 14:35:23 by dkathlee          #+#    #+#             */
/*   Updated: 2019/11/06 15:59:36 by dkathlee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	p3d_rotate_x(float *y, float *z, float angle)
{
	float		prev;
	
	prev = *y;
	*y = (prev * cos(RAD(angle)) - *z * sin(RAD(angle)));
	*z = (prev * sin(RAD(angle)) + *z * cos(RAD(angle)));
}

void	p3d_rotate_y(float *x, float *z, float angle)
{
	float		prev;
	
	prev = *x;
	*x = (*x * cos(RAD(angle)) + *z * sin(RAD(angle)));
	*z = (*z * cos(RAD(angle)) - prev * sin(RAD(angle)));
}

void	p3d_rotate_z(float *x, float *y, float angle)
{
	float		prev;

	prev = *x;
	*x = (*x * cos(RAD(angle)) - *y * sin(RAD(angle)));
	*y = (prev * sin(RAD(angle)) + *y * cos(RAD(angle)));
}

static t_point2d	make_projection(t_point3d *p, t_projection_type pr_t)
{
	t_point2d	new_p;

	new_p.color = p->color;
	if (pr_t == ISO)
	{
		new_p.x = (p->x - p->y) * COS30;
		new_p.y = -(p->z) + (p->x + p->y) * SIN30;
	}
	else if (pr_t == Parallel)
	{
		new_p.x = p->x;
		new_p.y = p->y;
	}
	return (new_p);
}

t_point2d			project(t_point3d p, t_view *v)
{
	t_point2d	p2d;

	p.x -= v->map->w / 2;
	p.y -= v->map->h / 2;
	p.x *= v->transform.scale.x;
	p.y *= v->transform.scale.y;
	p.z *= v->transform.scale.z;
	if (v->transform.rotation.x != 0)
		p3d_rotate_x(&p.y, &p.z, v->transform.rotation.x);
	if (v->transform.rotation.y != 0)
		p3d_rotate_y(&p.x, &p.z, v->transform.rotation.y);
	if (v->transform.rotation.z != 0)
		p3d_rotate_z(&p.x, &p.y, v->transform.rotation.z);
	p.x += v->transform.translation.x;
	p.y += v->transform.translation.y;
	p.z += v->transform.translation.z;
	p2d = make_projection(&p, v->projection);
	p2d.x += WIDTH / 2;
	p2d.y += HEIGHT / 2;
	return (p2d);
}
