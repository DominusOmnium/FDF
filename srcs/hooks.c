/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkathlee <dkathlee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/25 13:03:24 by dkathlee          #+#    #+#             */
/*   Updated: 2019/10/31 14:18:38 by dkathlee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	mouse_hook(int b, int x, int y, t_view *v)
{
	if (v->tr_type == tr_scale_ALL || v->tr_type == tr_scale_X)
		v->transform->scale.x *= b == BTN_MOUSE_WHEEL_UP ? 0.9 : 1.1;
	if (v->tr_type == tr_scale_ALL || v->tr_type == tr_scale_Y)
		v->transform->scale.y *= b == BTN_MOUSE_WHEEL_UP ? 0.9 : 1.1;
	if (v->tr_type == tr_scale_ALL || v->tr_type == tr_scale_Z)
		v->transform->scale.z *= b == BTN_MOUSE_WHEEL_UP ? 0.9 : 1.1;
	if (v->tr_type == tr_rot_X)
		v->transform->rotation.x += b == BTN_MOUSE_WHEEL_UP ? 5 : -5;
	if (v->tr_type == tr_rot_Y)
		v->transform->rotation.y += b == BTN_MOUSE_WHEEL_UP ? 5 : -5;
	if (v->tr_type == tr_rot_Z)
		v->transform->rotation.z += b == BTN_MOUSE_WHEEL_UP ? 5 : -5;
	if (v->tr_type == tr_translate_X)
		v->transform->translation.x += b == BTN_MOUSE_WHEEL_UP ? 10 : -10;
	if (v->tr_type == tr_translate_Y)
		v->transform->translation.y += b == BTN_MOUSE_WHEEL_UP ? 10 : -10;
	if (v->tr_type == tr_translate_Z)
		v->transform->translation.z += b == BTN_MOUSE_WHEEL_UP ? 10 : -10;
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
