/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marimoli <marimoli@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 13:39:10 by marimoli          #+#    #+#             */
/*   Updated: 2025/04/13 13:39:34 by marimoli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	handle_coin(t_game *game, int x, int y)
{
    game->score++;           // Aumentar el contador de monedas
    game->coin_count--;
    game->map[y][x] = FLOOR; // Cambiar la casilla de la moneda a "suelo"
    printf("Moneda recogida. Monedas restantes: %d\n", game->coin_count);
}

static int	handle_exit(t_game *game)
{ // Comprobar si recogió todas las monedas y está en la salida
    if (check_all_coins_and_exit(game))  
    {
        printf("¡YOUR WIN!!! %d movimientos!\n", game->player.move_count);
        exit_game(game);  // Salir del juego si hizo victoria
    }
    else
    {
    printf("Aún faltan monedas.\n");
    return (0);  // Si no se ha ganado, continuar
    }
    return (0);
}

int    move_player(t_game *game, int move_x, int move_y)
{
    int	new_x;
    int	new_y;

    new_x = game->player.x + move_x;   //nueva posición X del jugador
    new_y = game->player.y + move_y;   //nueva posición Y del jugador
    game->step_counter++;
    game->current_frame = (game->step_counter % 2) + 1; //alterna paso
    if (!check_move_valid(game, new_x, new_y)) //Sí movimiento es válida
    {
        printf("Movimiento inválido\n");
        return (0);  // no mover al jugador
    }
    if (game->map[new_y][new_x] == COIN)  // Si se mueve a una celda con moneda
        handle_coin(game, new_x, new_y);  // Encuentra la moneda
    else if (game->map[new_y][new_x] == EXIT)  // Si llega a la salida
        return (handle_exit(game));  // Llamar a función para salir
    game->player.x = new_x;
    game->player.y = new_y;    
    game->player.move_count++;  // Incrementar el contador de movimientos
    printf("Movimientos: %d\n", game->player.move_count); //número de movimientos realizados
    paint(game);
    return (1);  // El movimiento fue exitoso
}