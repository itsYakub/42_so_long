/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assets.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joleksia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 12:46:50 by joleksia          #+#    #+#             */
/*   Updated: 2025/01/15 10:06:25 by joleksia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	sl_init_assets(t_game *game, size_t n)
{
	game->s_assets.imgs = ft_calloc(n, sizeof(t_image));
	if (!game->s_assets.imgs)
		return (0);
	game->s_assets.c = n;
	sl_load_img(game, &game->s_assets.imgs[0], "./textures/sprite_grass.xpm");
	sl_load_img(game, &game->s_assets.imgs[1], "./textures/sprite_bush.xpm");
	sl_load_img(game, &game->s_assets.imgs[2], "./textures/sprite_tomato.xpm");
	sl_load_img(game, &game->s_assets.imgs[3], "./textures/sprite_ghost.xpm");
	sl_load_img(game, &game->s_assets.imgs[4], "./textures/sprite_carrot.xpm");
	return (1);
}

t_image	*sl_getimgptr(t_game *game, int i)
{
	if (i >= (int) game->s_assets.c)
		return (NULL);
	return (&(game->s_assets.imgs[i]));
}

int	sl_unload_assets(t_game *game)
{
	size_t	iter;

	iter = -1;
	while (++iter < game->s_assets.c)
		sl_unload_img(game, &game->s_assets.imgs[iter]);
	free(game->s_assets.imgs);
	return (1);
}
