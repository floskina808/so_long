#include "so_long.h"
#include <stdio.h>
#include <stdlib.h>

void	error_exit(char *message, t_game *game)
{
	if (message)
		write(2, message, ft_strlen(message));
	if (game)
		destroy_game(game); // libera la memoria se serve
	exit(EXIT_FAILURE);
}
