#include "libft.h"
#include "so_long.h"
#include <stdbool.h>

static bool	check_walls(t_map *map, int x, int y, char tile)
{
	if (y == 0 || y == map->height - 1 || x == 0 || x == map->width - 1)
		return (tile == '1');
	return (true);
}

bool	validate_map(t_map *map)
{
	int	player_count;
	int	exit_count;
	int	y;
	int	x;

	if (!map || !map->map || map->width < 3 || map->height < 3)
		return (false);
	player_count = 0;
	exit_count = 0;
	map->collectibles = 0;
	y = 0;
	while (y < map->height)
	{
		if ((int)ft_strlen(map->map[y]) != map->width)
			return (false);
		x = 0;
		while (x < map->width)
		{
			if (!check_walls(map, x, y, map->map[y][x]))
				return (false);
			if (map->map[y][x] == 'P')
			{
				player_count++;
				map->player.x = x;
				map->player.y = y;
				map->map[y][x] = '0';
			}
			else if (map->map[y][x] == 'E')
			{
				exit_count++;
			}
			else if (map->map[y][x] == 'C')
				map->collectibles++;
			else if (map->map[y][x] != '0' && map->map[y][x] != '1')
				return (false);
			x++;
		}
		y++;
	}
	if (player_count != 1 || exit_count != 1 || map->collectibles == 0)
		return (false);
	return (true);
}
