/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: celva <celva@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/25 13:03:24 by dkathlee          #+#    #+#             */
/*   Updated: 2019/11/04 00:31:47 by celva            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int				mouse_press(int b, int x, int y, t_view *v)
{
	v->map->min_color = rand_color();
	v->map->max_color = rand_color();
	draw_map(v);
	if (b == BTN_MOUSE_WHEEL_DOWN || b == BTN_MOUSE_WHEEL_UP)
	{
		if (v->tr_type == tr_scale_ALL || v->tr_type == tr_scale_X)
			v->transform.scale.x *= b == BTN_MOUSE_WHEEL_UP ? 0.9 : 1.1;
		if (v->tr_type == tr_scale_ALL || v->tr_type == tr_scale_Y)
			v->transform.scale.y *= b == BTN_MOUSE_WHEEL_UP ? 0.9 : 1.1;
		if (v->tr_type == tr_scale_ALL || v->tr_type == tr_scale_Z)
			v->transform.scale.z *= b == BTN_MOUSE_WHEEL_UP ? 0.9 : 1.1;
		draw_map(v);
	}
	if (b == BTN_MOUSE_LEFT && x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
	{
		v->mouse.is_pressed = true;
		v->mouse.tr_type = m_tr_translate;
		v->mouse.prev.x = x;
		v->mouse.prev.y = y;
	}
	else if (b == BTN_MOUSE_RIGHT && x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
	{
		v->mouse.is_pressed = true;
		v->mouse.tr_type = m_tr_rotate;
		v->mouse.prev.x = x;
		v->mouse.prev.y = y;
	}
	return (1);
}

int				mouse_release(int b, int x, int y, t_view *v)
{
	(void)x;
	(void)y;
	if ((b == BTN_MOUSE_LEFT && v->mouse.tr_type == m_tr_translate) ||
		(b == BTN_MOUSE_RIGHT && v->mouse.tr_type == m_tr_rotate))
		v->mouse.is_pressed = false;
	return (1);
}

int				key_press(int keycode, t_view *v)
{
	if (keycode == BTN_ESC)
		exit(0);
	if (keycode == BTN_Q)
		v->mouse.tr_type = m_tr_rotate;
	if (keycode == BTN_W)
		v->mouse.tr_type = m_tr_rotate;
	if (keycode == BTN_A)
		v->tr_type = tr_scale_X;
	if (keycode == BTN_S)
		v->tr_type = tr_scale_Y;
	if (keycode == BTN_D)
		v->tr_type = tr_scale_Z;
	if (keycode == BTN_F)
		v->tr_type = tr_scale_ALL;
	if (keycode == BTN_I)
		v->projection = ISO;
	if (keycode == BTN_P)
		v->projection = Parallel;
	if (keycode == BTN_C)
	{
		v->map->min_color = rand_color();
		v->map->max_color = rand_color();
		colorize_points(v->map);
	}
	if (keycode == BTN_C || keycode == BTN_I || keycode == BTN_P)
		draw_map(v);
	return (1);
}

int				mouse_move(int x, int y, t_view *v)
{
	t_point2d	delta;

	delta.x = x - v->mouse.prev.x;
	delta.y = y - v->mouse.prev.y;
	if (v->mouse.is_pressed && (delta.x != 0 || delta.y != 0))
	{
		if (v->mouse.tr_type == m_tr_translate)
		{
			if (v->projection == ISO)
			{
				v->transform.translation.x += delta.x * tan(RAD(30));
				v->transform.translation.y -= delta.x * tan(RAD(30));
				v->transform.translation.z -= delta.y;
			}
			else
			{
				v->transform.translation.x += delta.x;
				v->transform.translation.y += delta.y;
			}
		}
		else if (v->mouse.tr_type == m_tr_rotate)
		{
			if (v->projection == Parallel)
			{
				v->transform.rotation.y += delta.x >> 2;
				v->transform.rotation.x -= delta.y >> 2;
			}
			else
			{
				v->transform.rotation.x += (delta.x >> 2) * TAN30 + (delta.y >> 2) * (1 - TAN30);
				v->transform.rotation.y += (delta.x >> 2) * (1 - TAN30) + (delta.y >> 2) * TAN30;
			}
			
		}
		v->mouse.prev.x = x;
		v->mouse.prev.y = y;
		draw_map(v);
	}
	return (1);
}
