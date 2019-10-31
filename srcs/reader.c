/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkathlee <dkathlee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/21 22:54:22 by dkathlee          #+#    #+#             */
/*   Updated: 2019/10/31 17:40:25 by dkathlee         ###   ########.fr       */
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

	wc = map->width;
	while (--wc >= 0)
	{
		(map->points3d)[i][wc].z = ft_atoi(splited_line[wc]);
		(map->points3d)[i][wc].x = i;
		(map->points3d)[i][wc].y = wc;
		(map->points3d)[i][wc].color.b = 255;
	}
}

int			read_map(char *fname, t_map *map)
{
	int		fd;
	int		i;
	char	*line;
	char	**splited_line;

	if ((fd = open(fname, O_RDONLY)) == -1)
		return (0);
	i = 0;
	while (get_next_line(fd, &line) == 1)
	{
		map->points3d = ft_realloc(map->points3d, sizeof(t_point3d*) * i,
												sizeof(t_point3d*) * (i + 1));
		splited_line = ft_strsplit(line, ' ');
		map->width = ft_word_count(line, ' ');
		(map->points3d)[i] = ft_memalloc(sizeof(t_point3d) * map->width);
		set_point(map, i, splited_line);
		free_splited_str(splited_line, map->width);
		ft_memdel((void**)&line);
		i++;
	}
	map->height = i;
	close(fd);
	return (1);
}
