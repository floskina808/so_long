#include "so_long.h"
#include <stdlib.h>
#include <stdbool.h>

typedef struct s_point {
    int x;
    int y;
} t_point;

bool check_map_path(t_map *map)
{
    int max = map->width * map->height;
    t_point *queue;
    int front = 0;
    int back = 0;
    int *visited;
    int dirs[4][2] = { {0, 1}, {1, 0}, {0, -1}, {-1, 0} };
    t_point player;
    
    if (!map || !map->map)
        return false;

    player.x = map->player.x;
    player.y = map->player.y;

    queue = (t_point *)ft_calloc(max, sizeof(t_point));
    if (!queue)
        return false;

    visited = (int *)ft_calloc(max, sizeof(int));
    if (!visited)
    {
        free(queue);
        return false;
    }

    queue[back++] = player;
    visited[player.y * map->width + player.x] = 1;

    while (front < back)
    {
        t_point current = queue[front++];
        for (int i = 0; i < 4; i++)
        {
            int nx = current.x + dirs[i][0];
            int ny = current.y + dirs[i][1];

            if (nx < 0 || nx >= map->width || ny < 0 || ny >= map->height)
                continue;
            if (map->map[ny][nx] == '1')
                continue;
            if (visited[ny * map->width + nx])
                continue;

            visited[ny * map->width + nx] = 1;
            queue[back++] = (t_point){nx, ny};
        }
    }

    bool all_reachable = true;
    for (int y = 0; y < map->height && all_reachable; y++)
    {
        for (int x = 0; x < map->width; x++)
        {
            if ((map->map[y][x] == 'C' || map->map[y][x] == 'E') &&
                !visited[y * map->width + x])
            {
                all_reachable = false;
                break;
            }
        }
    }

    free(queue);
    free(visited);
    return all_reachable;
}

