/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkathlee <dkathlee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/31 14:35:23 by dkathlee          #+#    #+#             */
/*   Updated: 2019/10/31 16:59:55 by dkathlee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_point2d	*iso(t_point3d *p)
{
	t_point2d	*new_p;

	new_p = ft_memalloc(sizeof(t_point2d));
	new_p->color = p->color;
	new_p->x = (p->x - p->y) * cos(RAD(30));
	new_p->y = -(p->z) - (p->x + p->y) * sin(RAD(30));
	return (new_p);
}

t_point2d	*project(t_point3d p, t_view *v)
{
	t_point2d	*p2d;

	p.x -= v->map->height / 2;
	p.y -= v->map->width / 2;
	p3d_scale(&p, v->transform->scale.x, tr_scale_X);
	p3d_scale(&p, v->transform->scale.y, tr_scale_Y);
	p3d_scale(&p, v->transform->scale.z, tr_scale_Z);
	p3d_rotate(&p, v->transform->rotation.x, tr_rot_X);
	p3d_rotate(&p, v->transform->rotation.y, tr_rot_Y);
	p3d_rotate(&p, v->transform->rotation.z, tr_rot_Z);
	p3d_translate(&p, v->transform->translation.x, tr_translate_X);
	p3d_translate(&p, v->transform->translation.y, tr_translate_Y);
	p3d_translate(&p, v->transform->translation.z, tr_translate_Z);
	p2d = iso(&p);
	p2d->x += WIDTH / 2;
	p2d->y += HEIGHT / 2;
	return (p2d);
}
