/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: celva <celva@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/21 22:54:22 by dkathlee          #+#    #+#             */
/*   Updated: 2019/10/30 16:36:56 by celva            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	free_splited_str(char **mem, int c)
{
	while (--c >= 0)
		free(mem[c]);
	free(mem);
}

int	read_map(char *fname, t_map *map)
{
	int		fd;
	int		i;
	int		wc;
	char	*line;
	char	**splited_line;
	
	if ((fd = open(fname, O_RDONLY)) == -1)
		return (0);
	map->points3D = ft_memalloc(sizeof(t_point3D*));
	i = 0;
	while (get_next_line(fd, &line) == 1)
	{
		map->points3D = ft_realloc(map->points3D, sizeof(t_point3D*) * i, sizeof(t_point3D*) * (i + 1));
		splited_line = ft_strsplit(line, ' ');
		map->Width = ft_word_count(line, ' ');
		(map->points3D)[i] = ft_memalloc(sizeof(t_point3D) * map->Width);
		wc = map->Width;
		while (--wc >= 0)
		{
			(map->points3D)[i][wc].Z = ft_atoi(splited_line[wc]);
			(map->points3D)[i][wc].X = i;
			(map->points3D)[i][wc].Y = wc;
		}
		free_splited_str(splited_line, map->Width);
		ft_memdel((void**)&line);
		i++;
	}
	close(fd);
	map->Height = i;
	p3D_transform(map, i / -2, tr_translate_Y, &p3D_translate);
	p3D_transform(map, map->Width / -2, tr_translate_X, &p3D_translate);
	return (1);
}
