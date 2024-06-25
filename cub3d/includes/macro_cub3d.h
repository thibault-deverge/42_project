/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   macro_cub3d.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeverge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/16 17:26:31 by tdeverge          #+#    #+#             */
/*   Updated: 2023/04/21 18:46:04 by tdeverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef MACRO_CUB3D_H
# define MACRO_CUB3D_H

/********************************************************/
/*						ERRORS							*/
/********************************************************/
# define ERR_ARG		"error: cub3d should contains only one argument\n"
# define ERR_CUB		"error: argument is not of type '.cub'\n"
# define ERR_ELEMENTS	"error: some textures or elements are missing.\n"
# define ERR_TEXT_TYPO	"error: syntax error in texture line\n"
# define ERR_TEXT_PATH	"error: texture path is incorrect, cannot open\n"
# define ERR_TEXT_DUP	"error: only one texture per direction is allowed.\n"
# define ERR_LAYER_RGB	"error: rgb color is not correct\n"
# define ERR_LAYER_DUP	"error: only one color can be given to a layer.\n"
# define ERR_LAYER_NB	"error: layer format is not valid.\n"
# define ERR_MAP_LOST	"error: map is missing in the file.\n"
# define ERR_MAP_CHAR	"error: map contains some forbiden characters\n"
# define ERR_MAP_DATA	"error: map description is not last on the file\n"
# define ERR_MAP_PLAYER	"error: map should contains one player exactly\n"
# define ERR_MAP_BORDER	"error: map should be inside borders.\n"
# define ERR_TEXT_LOAD	"error: texture can't be load.\n"

/********************************************************/
/*						EXIT STATUS						*/
/********************************************************/
# define EXIT_ALLOC		1
# define EXIT_ARG		2
# define EXIT_EXTENSION	3
# define EXIT_ELEMENTS	4
# define EXIT_TEXTURE	5
# define EXIT_LAYER		6
# define EXIT_MAP		7
# define EXIT_GAME		8

/********************************************************/
/*						ELEMENT_ID						*/
/********************************************************/
# define NORTH_ID	0
# define EAST_ID	1
# define SOUTH_ID	2
# define WEST_ID	3
# define FLOOR_ID 	4
# define CEIL_ID	5
# define EMPTY_LINE	6

/********************************************************/
/*						BOOLEANS						*/
/********************************************************/
# define FALSE		0
# define TRUE		1
# define FAIL		0
# define SUCCESS	1

/********************************************************/
/*						TEXTURES						*/
/********************************************************/
# define NORTH	0
# define EAST	1
# define SOUTH	2
# define WEST	3

/********************************************************/
/*						DIRECTIONS						*/
/********************************************************/
# define EAST_DIR	-2
# define NORTH_DIR	-1
# define SOUTH_DIR	1
# define WEST_DIR	2

/********************************************************/
/*						SIZE							*/
/********************************************************/
# define WIN_W		1280
# define WIN_H		720
# define TILE_L		32
# define DEP		3.0
# define DIAM		6

/********************************************************/
/*						WALL_HIT						*/
/********************************************************/
# define HORIZONTAL	0
# define VERTICAL	1

/********************************************************/
/*						COLORS							*/
/********************************************************/
# define BLACK	0x000000FF
# define GREY	0x808080FF
# define WHITE	0xFFFFFFFF
# define YELLOW	0xFCCA60FF
# define RED	0xDA121AFF
# define BLUE 	0x3B8EBFFF
# define GREEN 	0x649441FF
# define BROWN 	0x2F75AAFF
# define PURPLE	0x936599FF
# define GRAY	0xD3D3D3EE

#endif
