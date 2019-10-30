/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: celva <celva@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/25 12:58:57 by dkathlee          #+#    #+#             */
/*   Updated: 2019/10/30 13:28:09 by celva            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	p3D_transform(t_map *map, float value, t_transform_type type,
						void (tr)(t_point3D*, float, t_transform_type))
{
	int i;
	int j;

	i = 0;
	while (i < map->Height)
	{
		j = 0;
		while (j < map->Width)
		{
			tr((map->points3D)[i] + j, value, type);
			j++;
		}
		i++;
	}
}

void	p3D_rotate(t_point3D *p, float angle, t_transform_type t)
{
	float	prev;
	
	if (t == tr_rot_X)
	{
		prev = p->Y;
		p->Y = (prev * cos(RAD(angle)) - p->Z * sin(RAD(angle)));
		p->Z = (prev * sin(RAD(angle)) + p->Z * cos(RAD(angle)));
	}
	else if (t == tr_rot_Y)
	{
		prev = p->X;
		p->X = (p->X * cos(RAD(angle)) + p->Z * sin(RAD(angle)));
		p->Z = (p->Z * cos(RAD(angle)) - prev * sin(RAD(angle)));
	}
	else if (t == tr_rot_Z)
	{
		prev = p->X;
		p->X = (p->X * cos(RAD(angle)) - p->Y * sin(RAD(angle)));
		p->Y = (prev * sin(RAD(angle)) + p->Y * cos(RAD(angle)));
	}
}

void	p3D_scale(t_point3D *p, float value, t_transform_type t)
{
	if (t == tr_scale_X)
	{
		p->X *= value;
	}
	else if (t == tr_scale_Y)
	{
		p->Y *= value;
	}
	else if (t == tr_scale_Z)
	{
		p->Z *= value;
	}
	else if (t == tr_scale_ALL)
	{
		p->X *= value;
		p->Y *= value;
		p->Z *= value;
	}
}

void	p3D_translate(t_point3D *p, float value, t_transform_type t)
{
	if (t == tr_translate_X)
	{
		p->X += value;
	}
	else if (t == tr_translate_Y)
	{
		p->Y += value;
	}
	else if (t == tr_translate_Z)
	{
		p->Z += value;
	}
}
