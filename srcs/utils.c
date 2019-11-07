/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkathlee <dkathlee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 14:34:58 by dkathlee          #+#    #+#             */
/*   Updated: 2019/11/07 14:23:12 by dkathlee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	set_scale(t_view *v)
{
	float	scale;

	scale = MIN(WIDTH / (v->map->w * 2.5), HEIGHT / (v->map->h * 2.5));
	v->transform.scale.x = scale;
	v->transform.scale.y = scale;
	v->transform.scale.z = scale;
}

void	reset(t_view *v)
{
	v->transform.rotation.x = 0;
	v->transform.rotation.y = 0;
	v->transform.rotation.z = 0;
	set_scale(v);
	v->transform.translation.x = 0;
	v->transform.translation.y = 0;
	v->transform.translation.z = 0;
	v->projection = ISO;
}
