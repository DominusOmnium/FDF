/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkathlee <dkathlee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/25 13:03:24 by dkathlee          #+#    #+#             */
/*   Updated: 2019/10/25 16:13:40 by dkathlee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int mouse_hook(int button, int X, int Y, t_view *v)
{
	if (v->tr_type == tr_scale_ALL || v->tr_type == tr_scale_X ||
		v->tr_type == tr_scale_Y || v->tr_type == tr_scale_Z)
	{
		if (button == BTN_MOUSE_WHEEL_UP)
			p3D_transform(v->map, 1.1, v->tr_type, &p3D_scale);
		else if (button == BTN_MOUSE_WHEEL_DOWN)
			p3D_transform(v->map, 0.9, v->tr_type, &p3D_scale);
	}
	if (v->tr_type == tr_rot_X || v->tr_type == tr_rot_Y ||
									v->tr_type == tr_rot_Z)
	{
		if (button == BTN_MOUSE_WHEEL_UP)
			p3D_transform(v->map, 5, v->tr_type, &p3D_rotate);
		else if (button == BTN_MOUSE_WHEEL_DOWN)
			p3D_transform(v->map, -5, v->tr_type, &p3D_rotate);
	}
	if (v->tr_type == tr_translate_X || v->tr_type == tr_translate_Y ||
									v->tr_type == tr_translate_Z)
	{
		if (button == BTN_MOUSE_WHEEL_UP)
			p3D_transform(v->map, 10, v->tr_type, &p3D_translate);
		else if (button == BTN_MOUSE_WHEEL_DOWN)
			p3D_transform(v->map, -10, v->tr_type, &p3D_translate);
	}
	mlx_clear_window(v->mlx_ptr, v->win_ptr);
	draw_map(v);
	return (1);
}

int	key_hook(int keycode, t_view *v)
{
	if (keycode == BTN_ESC)
		exit(0);
	if (keycode == BTN_Q)
		v->tr_type = tr_rot_X;
	if (keycode == BTN_W)
		v->tr_type = tr_rot_Y;
	if (keycode == BTN_E)
		v->tr_type = tr_rot_Z;
	if (keycode == BTN_Z)
		v->tr_type = tr_translate_X;
	if (keycode == BTN_X)
		v->tr_type = tr_translate_Y;
	if (keycode == BTN_C)
		v->tr_type = tr_translate_Z;
	if (keycode == BTN_A)
		v->tr_type = tr_scale_X;
	if (keycode == BTN_S)
		v->tr_type = tr_scale_Y;
	if (keycode == BTN_D)
		v->tr_type = tr_scale_Z;
	if (keycode == BTN_F)
		v->tr_type = tr_scale_ALL;
	return (1);
}
