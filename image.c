/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joleksia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 12:31:47 by joleksia          #+#    #+#             */
/*   Updated: 2025/01/15 08:17:01 by joleksia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minilibx/mlx.h"
#include "so_long.h"

int	sl_load_img(t_game *game, t_image *image, char *path)
{
	int	w;
	int	h;

	image->ptr = mlx_xpm_file_to_image(game->s_mlx.ptr, path, &w, &h);
	image->pix = mlx_get_data_addr(image->ptr,
			&image->bits, &image->len, &image->endian);
	return (1);
}

int	sl_dimg(t_game *game, t_image image, t_vec2i p, t_vec2i s)
{
	t_vec2i	iter;

	iter[1] = -1;
	while (++iter[1] < s[1])
	{
		iter[0] = -1;
		while (++iter[0] < s[0])
		{
			sl_setpix(game,
				p[0] + iter[0], p[1] + iter[1],
				sl_getpix(&image, iter[0], iter[1])
				);
		}
	}
	return (1);
}

int	sl_unload_img(t_game *game, t_image *image)
{
	mlx_destroy_image(game->s_mlx.ptr, image->ptr);
	return (1);
}
