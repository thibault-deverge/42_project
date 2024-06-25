/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prototype_cub3d.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeverge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/16 17:26:41 by tdeverge          #+#    #+#             */
/*   Updated: 2023/04/17 20:27:19 by tdeverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef PROTOTYPE_CUB3D_H
# define PROTOTYPE_CUB3D_H

/********************************************************/
/*						PARSING							*/
/********************************************************/
/*						general							*/
void		parsing(t_assets *assets, char *assets_path);
int			is_extension(char *path, char *extension, int length);
bool		is_all_whitespace(char **element);
/*						elements						*/
char		*parsing_elements(t_assets *assets);
void		save_layer(t_assets *assets, char **element);
void		save_texture(t_assets *assets, char **element, int id);	
void		get_layer_hexadecimal(t_assets *assets, int *floor, int *ceil);
/*						map								*/
void		parsing_map(t_assets *assets, char *line);
int			validity_map(char **map);

/********************************************************/
/*						RENDERS							*/
/********************************************************/
/*						window							*/
bool		render_window(t_render *render, t_assets *assets);
void		loop_hook(void *arg);
/*						images							*/
bool		generate_background(t_render *render, int floor, int ceil);
bool		generate_game_image(t_render *render, bool first_draw);
/*						draw							*/
void		draw_background(mlx_image_t *img, int floor_color, int ceil_color);
void		build_walls(t_render *render, t_player *player);
/*						textures						*/
int			get_texture(t_pixel pixel, int position);
t_pixel		get_pixel_param(t_render *render, t_rays ray, float wall_height);
bool		convert_textures(t_render *render, int idx_texture);

/********************************************************/
/*						HOOKS							*/
/********************************************************/
bool		check_move(t_render *render);
bool		check_rotation(t_render *render);
bool		check_collision(char **maps, int pos_x, int pos_y);
void		rotation(t_render *render, int angle);
void		make_first_rotation_player(t_render *render);

/********************************************************/
/*						UTILS							*/
/********************************************************/
/*						init.c							*/
void		init_assets(t_assets *assets);
void		init_player(t_render *render);
void		init_render(t_render *render, t_player *player, char **map);
bool		init_img_textures(t_render *render, t_assets *assets);
t_rays		*init_rays(t_render *render);
/*						free.c							*/
void		free_matrix(char **matrix);
void		free_textures(t_render *render);
void		free_assets(t_assets *assets);
void		free_parsing(t_assets *assets, char **split_line, char *line);
/*						errors.c						*/
void		exit_program(t_render *render, t_assets *assets);
void		exit_error(char *err_msg, int status);
void		exit_perror(int exit_status);
/*						helpers.c						*/
float		get_distance(float x1, float y1, float x2, float y2);
float		get_sign(int vector);
bool		is_player_position(char c);
int			get_hexa(int r, int g, int b, int a);
/*						standalone						*/
char		**ft_insert_matrix(char **matrix, char *str);

#endif
