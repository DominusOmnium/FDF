/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkathlee <dkathlee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/21 22:54:22 by dkathlee          #+#    #+#             */
/*   Updated: 2019/11/01 16:20:55 by dkathlee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	free_splited_str(char **mem, int c)
{
	while (--c >= 0)
		free(mem[c]);
	free(mem);
}

static void	set_point(t_map *map, int i, char **splited_line)
{
	int		wc;

	wc = map->w;
	while (--wc >= 0)
	{
		(map->points3d)[i][wc].z = ft_atoi(splited_line[wc]);
		if ((map->points3d)[i][wc].z < map->min_z)
			map->min_z = (int)(map->points3d)[i][wc].z;
		if ((map->points3d)[i][wc].z > map->max_z)
			map->max_z = (int)(map->points3d)[i][wc].z;
		(map->points3d)[i][wc].x = wc;
		(map->points3d)[i][wc].y = i;
		(map->points3d)[i][wc].color.b = 255;
	}
}

int			read_map(char *fname, t_map *map)
{
	int		fd;
	char	*line;
	char	**splited_line;

	if ((fd = open(fname, O_RDONLY)) == -1)
		return (0);
	map->h = 0;
	while (get_next_line(fd, &line) == 1)
	{
		map->points3d = ft_realloc(map->points3d, sizeof(t_point3d*) * map->h, 
											sizeof(t_point3d*) * (map->h + 1));
		splited_line = ft_strsplit(line, ' ');
		map->w = ft_word_count(line, ' ');
		(map->points3d)[map->h] = ft_memalloc(sizeof(t_point3d) * map->w);
		set_point(map, map->h, splited_line);
		free_splited_str(splited_line, map->w);
		ft_memdel((void**)&line);
		(map->h)++;
	}
	close(fd);
	colorize_points(map);
	return (1);
}
