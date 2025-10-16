#include "so_long.h"
#include <fcntl.h>

static char	**append_row(char **rows, int height, char *line)
{
	char	**tmp;
	int		i;

	tmp = (char **)ft_calloc(height + 2, sizeof(char *));
	if (!tmp)
		return (NULL);
	i = 0;
	while (i < height)
	{
		tmp[i] = rows[i];
		i++;
	}
	tmp[height] = line;
	free(rows);
	return (tmp);
}

bool	load_map(const char *path, t_map *map)
{
	int		fd;
	char	*line;
	size_t	len;

	ft_bzero(map, sizeof(t_map));
	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (false);
	while ((line = get_next_line(fd)))
	{
		len = ft_strlen(line);
		if (len > 0 && line[len - 1] == '\n')
		{
			line[len - 1] = '\0';
			len--;
		}
		if (len == 0)
		{
			free(line);
			free_map(map);
			close(fd);
			return (false);
		}
		if (map->height == 0)
			map->width = (int)len;
		else if ((int)len != map->width)
		{
			free(line);
			free_map(map);
			close(fd);
			return (false);
		}
		map->map = append_row(map->map, map->height, line);
		if (!map->map)
		{
			free(line);
			free_map(map);
			close(fd);
			return (false);
		}
		map->height++;
	}
	close(fd);
	if (map->height == 0 || map->width == 0)
	{
		free_map(map);
		return (false);
	}
	return (true);
}

void	free_map(t_map *map)
{
	int	i;

	if (!map || !map->map)
		return ;
	i = 0;
	while (i < map->height)
	{
		free(map->map[i]);
		i++;
	}
	free(map->map);
	map->map = NULL;
	map->height = 0;
	map->width = 0;
	map->collectibles = 0;
}
