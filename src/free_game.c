/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marimoli <marimoli@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 22:06:48 by marimoli          #+#    #+#             */
/*   Updated: 2025/05/20 22:06:55 by marimoli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	free_player_frames(t_game *game)
{
	int i;

	i = 0;
	while (i<3)
	{
		if (game->player_frames[i])
		mlx_destroy_image(game->graphics.mlx, game->player_frames[i]);
		i++;
	}
}

static void	free_images(t_game *game)
{
	if (game->sprites.player)
		mlx_destroy_image(game->graphics.mlx, game->sprites.player);
	if (game->sprites.floor)
		mlx_destroy_image(game->graphics.mlx, game->sprites.floor);
	if (game->sprites.wall)
		mlx_destroy_image(game->graphics.mlx, game->sprites.wall);
	if (game->sprites.coin)
		mlx_destroy_image(game->graphics.mlx, game->sprites.coin);
	if (game->sprites.exit)
		mlx_destroy_image(game->graphics.mlx, game->sprites.exit);
	free_player_frames(game);
}

void free_game(t_game *game)
{
	if (!game)
		return;
	if (game->map)
		free_split(game->map);
	if (game->graphics.mlx)
	{
		free_images(game);
		mlx_destroy_window(game->graphics.mlx, game->graphics.win);
	#ifdef _linux_
		mlx_destroy_display(game->graphics.mlx);
		free(game->graphics.mlx);
	#endif
	}
}