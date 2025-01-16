/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joleksia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 10:02:05 by joleksia          #+#    #+#             */
/*   Updated: 2025/01/15 08:18:46 by joleksia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

t_pix	sl_getpix(t_image *img, int x, int y)
{
	char	*dst;
	int		pos;

	pos = y * img->len + x * (img->bits / 8);
	dst = img->pix + pos;
	return (*(unsigned int *) dst);
}

int	sl_setpix(t_game *game, int x, int y, t_pix pix)
{
	char	*dst;
	int		pos;

	pos = y * game->s_mlx.data.len + x * (game->s_mlx.data.bits / 8);
	dst = game->s_mlx.data.pix + pos;
	*(unsigned int *) dst = pix;
	return (1);
}

int	sl_clear(t_game *game, t_pix pix)
{
	int	x;
	int	y;

	y = -1;
	while (++y < game->s_mlx.wnd.h)
	{
		x = -1;
		while (++x < game->s_mlx.wnd.w)
		{
			if (!sl_setpix(game, x, y, pix))
				return (0);
		}
	}
	return (1);
}

int	sl_drect(t_game *game, t_vec2i p, t_vec2i s, t_pix pix)
{
	int	y;
	int	x;

	y = p[1];
	while (y < p[1] + s[1])
	{
		x = p[0];
		while (x < p[0] + s[0])
		{
			if (!sl_setpix(game, x, y, pix))
				return (0);
			x++;
		}
		y++;
	}
	return (1);
}
