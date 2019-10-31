/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: celva <celva@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/25 13:03:24 by dkathlee          #+#    #+#             */
/*   Updated: 2019/11/01 02:28:30 by celva            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int				mouse_press(int b, int x, int y, t_view *v)
{
	if (b == BTN_MOUSE_WHEEL_DOWN || b == BTN_MOUSE_WHEEL_UP)
	{
		if (v->tr_type == tr_scale_ALL || v->tr_type == tr_scale_X)
			v->transform->scale.x *= b == BTN_MOUSE_WHEEL_UP ? 0.9 : 1.1;
		if (v->tr_type == tr_scale_ALL || v->tr_type == tr_scale_Y)
			v->transform->scale.y *= b == BTN_MOUSE_WHEEL_UP ? 0.9 : 1.1;
		if (v->tr_type == tr_scale_ALL || v->tr_type == tr_scale_Z)
			v->transform->scale.z *= b == BTN_MOUSE_WHEEL_UP ? 0.9 : 1.1;
		draw_map(v);
	}
	if (b == BTN_MOUSE_LEFT && x != v->mouse.prev_p.x && y != v->mouse.prev_p.y)
		v->mouse.is_pressed = true;
	return (1);
}

int				mouse_release(int b, int x, int y, t_view *v)
{
	(void)x;
	(void)y;
	if (b == BTN_MOUSE_LEFT)
		v->mouse.is_pressed = false;
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
	return (1);
}
