/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkathlee <dkathlee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/25 13:03:24 by dkathlee          #+#    #+#             */
/*   Updated: 2019/11/07 13:09:41 by dkathlee         ###   ########.fr       */
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
	if ((b == BTN_MOUSE_LEFT || b == BTN_MOUSE_RIGHT) && x >= 0 && x < WIDTH
														&& y >= 0 && y < HEIGHT)
	{
		v->mouse.is_pressed = true;
		v->mouse.prev.x = x;
		v->mouse.prev.y = y;
		if (b == BTN_MOUSE_LEFT)
			v->mouse.tr_type = m_tr_translate;
		else
			v->mouse.tr_type = m_tr_rotate;
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

int				key_press(int k, t_view *v)
{
	if (k == BTN_ESC)
		exit(0);
	if (k == BTN_Q)
		v->mouse.tr_type = m_tr_rotate;
	if (k == BTN_W)
		v->mouse.tr_type = m_tr_rotate;
	if (k == BTN_A)
		v->tr_type = tr_scale_X;
	if (k == BTN_S)
		v->tr_type = tr_scale_Y;
	if (k == BTN_D)
		v->tr_type = tr_scale_Z;
	if (k == BTN_F)
		v->tr_type = tr_scale_ALL;
	if (k == BTN_I)
		v->projection = ISO;
	if (k == BTN_P)
		v->projection = Parallel;
	if (k == BTN_C)
		colorize_points(v->map);
	if (k == BTN_R)
		reset(v);
	if (k == BTN_C || k == BTN_I || k == BTN_P || k == BTN_R)
		draw_map(v);
	return (1);
}

static void		set_transl_rot(t_view *v, t_point2d delta)
{
	if (v->mouse.tr_type == m_tr_translate)
	{
		if (v->projection == ISO)
		{
			v->transform.translation.x += delta.x * TAN30;
			v->transform.translation.y -= delta.x * TAN30;
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
		v->transform.rotation.y += delta.x >> 2;
		v->transform.rotation.x += delta.y >> 2;
	}
}

int				mouse_move(int x, int y, t_view *v)
{
	t_point2d	delta;

	delta.x = x - v->mouse.prev.x;
	delta.y = y - v->mouse.prev.y;
	if (v->mouse.is_pressed && (delta.x != 0 || delta.y != 0))
	{
		set_transl_rot(v, delta);
		v->mouse.prev.x = x;
		v->mouse.prev.y = y;
		draw_map(v);
	}
	return (1);
}
