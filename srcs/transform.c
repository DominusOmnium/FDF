/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkathlee <dkathlee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/25 12:58:57 by dkathlee          #+#    #+#             */
/*   Updated: 2019/10/31 16:44:21 by dkathlee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	p3d_rotate(t_point3d *p, float angle, t_transform_type t)
{
	float		prev;

	if (t == tr_rot_X)
	{
		prev = p->y;
		p->y = (prev * cos(RAD(angle)) - p->z * sin(RAD(angle)));
		p->z = (prev * sin(RAD(angle)) + p->z * cos(RAD(angle)));
	}
	else if (t == tr_rot_Y)
	{
		prev = p->x;
		p->x = (p->x * cos(RAD(angle)) + p->z * sin(RAD(angle)));
		p->z = (p->z * cos(RAD(angle)) - prev * sin(RAD(angle)));
	}
	else if (t == tr_rot_Z)
	{
		prev = p->x;
		p->x = (p->x * cos(RAD(angle)) - p->y * sin(RAD(angle)));
		p->y = (prev * sin(RAD(angle)) + p->y * cos(RAD(angle)));
	}
}

void	p3d_scale(t_point3d *p, float value, t_transform_type t)
{
	if (t == tr_scale_X)
	{
		p->x *= value;
	}
	else if (t == tr_scale_Y)
	{
		p->y *= value;
	}
	else if (t == tr_scale_Z)
	{
		p->z *= value;
	}
	else if (t == tr_scale_ALL)
	{
		p->x *= value;
		p->y *= value;
		p->z *= value;
	}
}

void	p3d_translate(t_point3d *p, float value, t_transform_type t)
{
	if (t == tr_translate_X)
	{
		p->x += value;
	}
	else if (t == tr_translate_Y)
	{
		p->y += value;
	}
	else if (t == tr_translate_Z)
	{
		p->z += value;
	}
}
