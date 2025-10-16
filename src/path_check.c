/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_check.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faiello <faiello@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 23:32:04 by faiello           #+#    #+#             */
/*   Updated: 2025/10/16 23:32:06 by faiello          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include <stdbool.h>
#include <stdlib.h>

bool	check_map_path(t_map *map)
{
	int			max;
	t_player	*queue;
	int			front;
	int			back;
	int			*visited;
	int			dirs[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
	t_player	player;
	t_player	current;
	int			nx;
	int			ny;
	bool		all_reachable;

	max = map->width * map->height;
	front = 0;
	back = 0;
	if (!map || !map->map)
		return (false);
	player.x = map->player.x;
	player.y = map->player.y;
	queue = (t_player *)ft_calloc(max, sizeof(t_player));
	if (!queue)
		return (false);
	visited = (int *)ft_calloc(max, sizeof(int));
	if (!visited)
	{
		free(queue);
		return (false);
	}
	queue[back++] = player;
	visited[player.y * map->width + player.x] = 1;
	while (front < back)
	{
		current = queue[front++];
		for (int i = 0; i < 4; i++)
		{
			nx = current.x + dirs[i][0];
			ny = current.y + dirs[i][1];
			if (nx < 0 || nx >= map->width || ny < 0 || ny >= map->height)
				continue ;
			if (map->map[ny][nx] == '1')
				continue ;
			if (visited[ny * map->width + nx])
				continue ;
			visited[ny * map->width + nx] = 1;
			queue[back++] = (t_player){nx, ny};
		}
	}
	all_reachable = true;
	for (int y = 0; y < map->height && all_reachable; y++)
	{
		for (int x = 0; x < map->width; x++)
		{
			if ((map->map[y][x] == 'C' || map->map[y][x] == 'E') && !visited[y
				* map->width + x])
			{
				all_reachable = false;
				break ;
			}
		}
	}
	free(queue);
	free(visited);
	return (all_reachable);
}
