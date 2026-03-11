/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defines.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbonneau <sbonneau@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 03:46:43 by sbonneau          #+#    #+#             */
/*   Updated: 2025/11/08 05:38:06 by sbonneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINES_H
# define DEFINES_H

# define BUFFER_SIZE 1000
# define TITLE_SIZE 256
# define TILE_SIZE 48

# define KEY_ESC 65307
# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100
# define KEY_UP 65362
# define KEY_DOWN 65364
# define KEY_LEFT 65361
# define KEY_RIGHT 65363
# define KEY_SPACE 32
# define KEY_ENTER 65293
# define KEY_Q 113

# define ERR_USAGE_INVALIDE "Usage invalide : ./so_long [map.ber]\n"
# define ERR_TILE_SIZE "Taille invalide, le TILE_SIZE doit 48\n"
# define ERR_MEMORY_MAP "Erreur de memoire (t_map)\n"
# define ERR_READ_MAP "Erreur de la lecture de la map\n"
# define ERR_NOT_RECTANGULAR "Map non rectangulaire\n"
# define ERR_NOT_CLOSE "Map non ferme\n"
# define ERR_ELEMS "Map avec des elements non valides\n"
# define ERR_NOT_POSSIBLE "Map impossible\n"
# define ERR_INVALID_FILE "Fichier invalide\n"
# define ERR_NO_DATA "Aucune donnee lors de la lecture\n"
# define ERR_MLX_INIT "Erreur lors de l'initialisation de MLX\n"
# define ERR_WINDOW "Erreur lors de la creation de la fenetre\n"
# define ERR_CANT_LOAD "Impossible de charger "
# define ERR_MLX_ADDR "La fonction get_data_addr de MLX a flop\n"

# define INFO_RECTANGULAR "Map rectangulaire\n"
# define INFO_CLOSE "Map ferme\n"
# define INFO_ELEMS "Map possede les bon elements\n"
# define INFO_POSSIBLE "Map possible\n"
# define INFO_MAP_VALID "Map valide, creation de la fenetre\n"
# define INFO_MOVES_COUNT "Nombre de mouvements : "
# define INFO_COLLECTIBLES ", nombre de collectibles recoltes : "
# define INFO_LIFE ", nombre de points de vie : "

# define SUCCESS_WINDOW "Fenetre creee avec succes\n"
# define SUCCESS_TEXTURES "Textures chargees avec succes\n"
# define SUCCESS_GAME "Partie finie\n"
# define SUCCESS_CLOSE "Fermeture du jeu\n"

#endif
