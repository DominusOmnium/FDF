/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: celva <celva@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/18 02:39:56 by marvin            #+#    #+#             */
/*   Updated: 2019/11/01 02:25:18 by celva            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <math.h>
# include "mlx.h"
# include "libft.h"
# include "buttons.h"
# define HEIGHT	800
# define WIDTH	800
# define RAD(Value) ((Value) * 0.0174533)

typedef enum
{
	tr_rot_X, tr_rot_Y, tr_rot_Z,
	tr_translate_X, tr_translate_Y, tr_translate_Z,
	tr_scale_X, tr_scale_Y, tr_scale_Z, tr_scale_ALL
}				t_transform_type;
typedef enum
{
	m_tr_rotate, m_tr_translate
}				t_mouse_tr;
typedef struct	s_color
{
	t_uint8	b;
	t_uint8	g;
	t_uint8	r;
	t_uint8	a;
}				t_color;
typedef struct	s_point3d
{
	float	x;
	float	y;
	float	z;
	t_color	color;
}				t_point3d;
typedef struct	s_point2d
{
	int		x;
	int		y;
	t_color	color;
}				t_point2d;
typedef struct	s_transform
{
	t_point3d	rotation;
	t_point3d	translation;
	t_point3d	scale;
}				t_transform;
typedef struct	s_map
{
	float		min_z;
	float		max_z;
	int			width;
	int			height;
	t_point3d	**points3d;
}				t_map;
typedef struct s_mouse
{
	t_bool		is_pressed;
	t_point2d	prev_p;
	t_mouse_tr	tr_type;
}				t_mouse;

typedef struct	s_view
{
	void				*mlx;
	void				*win;
	void				*img;
	t_color				*data_addr;
	float				*zbuff;
	int					bpp;
	int					line_size;
	int					endian;
	t_transform			*transform;
	t_transform_type	tr_type;
	t_mouse				mouse;
	t_map				*map;
}				t_view;

int				read_map(char *fname, t_map *map);
void			p3d_rotate(t_point3d *p, float angle, t_transform_type t);
void			p3d_scale(t_point3d *p, float value, t_transform_type t);
void			p3d_translate(t_point3d *p, float value, t_transform_type t);
int				mouse_hook(int button, int x, int y, t_view *param);
int				key_hook(int keycode, t_view *v);
void			draw_map(t_view *v);
t_point2d		*iso(t_point3d *p);
t_point2d		*project(t_point3d p, t_view *v);
t_view			*new_view(void);
#endif
