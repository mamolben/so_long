/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marimoli <marimoli@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 21:02:22 by marimoli          #+#    #+#             */
/*   Updated: 2025/05/19 21:02:25 by marimoli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	free_visited(int **visited, int height)
{
	int	i;

	if (!visited)
		return ;
	i = 0;
	while (i < height)
		free(visited[i++]);
	free(visited);
}

int	**init_visited_matrix(t_game *game)
{
	int	**visited;
	int	i;

	visited = malloc(sizeof (int *) * game->height);
	if (!visited)
		return (NULL);
	i = 0;
	while (i < game->height)
	{
		visited[i] = calloc(game->width, sizeof(int));
		if (!visited[i])
		{
			free_visited(visited, i);
			return (NULL);
		}
		i++;
	}
	return (visited);
}

int	is_valid_move(int x, int y, t_game *game)
{
	if (x < 0 || x >= game->width || y < 0 || y >= game->height)
		return (0);
	if (game->visited[y][x] || game->map[y][x] == WALL)
		return (0);
	return (1);
}

void	dfs(int x, int y, t_game *game)
{
	if (!is_valid_move(x, y, game)) //celda válida
		return ;
	game->visited[y][x] = 1; //celda visitada
	if (game->map[y][x] == EXIT) //llegó a la salida
		game->exit_reached = 1;
	if (game->map[y][x] == COIN) //encuentra moneda
		game->collectibles_found++;
	dfs(x + 1, y, game);
	dfs(x - 1, y, game);
	dfs(x, y + 1, game);
	dfs(x, y - 1, game);
}
