/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_textures.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeverge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/16 17:08:28 by tdeverge          #+#    #+#             */
/*   Updated: 2023/04/21 18:46:27 by tdeverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "cub3d.h"

static void	fill_line(uint8_t *pix, int *line, int width, int k);
static int	get_rgba(int r, int g, int b, int a);

/*
 * @summary:
 * 		- Convert array of pixels receive by mlx in the form each 
 * 		to a 2d int array where every int will be a full color 
 * 		in hexadecimal form.
 * 		- Do many of calculation at first but will allow better optimisation
 * 		during the game. Alse make the code easier to read.
*/
bool	convert_textures(t_render *render, int idx)
{
	xpm_t		*old;
	int			**new_texture;
	uint32_t	i;

	i = 0;
	old = render->textures_mlx[idx];
	new_texture = (int **)malloc(old->texture.height * sizeof(int *));
	if (!new_texture)
		return (false);
	while (i < old->texture.height)
	{
		new_texture[i] = (int *)malloc(old->texture.width * sizeof(int));
		if (!new_texture[i])
			return (false);
		fill_line(old->texture.pixels, new_texture[i],
			old->texture.width, i * old->texture.width * 4);
		i++;
	}
	render->textures[idx].colors = new_texture;
	render->textures[idx].width = old->texture.width;
	render->textures[idx].height = old->texture.height;
	return (true);
}

static void	fill_line(uint8_t *pix, int *line, int width, int k)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (i < width)
	{
		line[i] = get_rgba(pix[j + k], pix[k + j + 1],
				pix[k + j + 2], pix[k + j + 3]);
		j += 4;
		i++;
	}
}

static int	get_rgba(int r, int g, int b, int a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}
