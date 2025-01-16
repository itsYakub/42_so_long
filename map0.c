/* ************************************************************************** */
/*																			  */
/*														  :::	   ::::::::   */
/*	 map0.c												:+:		 :+:	:+:   */
/*													  +:+ +:+		  +:+	  */
/*	 By: joleksia <marvin@42.fr>					+#+  +:+	   +#+		  */
/*												  +#+#+#+#+#+	+#+			  */
/*	 Created: 2025/01/11 09:02:14 by joleksia		   #+#	  #+#			  */
/*	 Updated: 2025/01/11 09:02:15 by joleksia		  ###	########.fr		  */
/*																			  */
/* ************************************************************************** */

#include "so_long.h"

static t_image	*__sl_map_getimg(t_game *game, t_vec2i p);
static int		__sl_map_dcell(t_game *game, t_vec2i p);

int	sl_readmap(t_game *game, const char *path)
{
	char	*fstr;

	if (!ft_strchr(path, '.') || ft_memcmp(ft_strchr(path, '.'), ".ber", 5))
	{
		ft_printf("Error\nType: Invalid filepath: %s\n", path);
		game->s_map.data = NULL;
		return (0);
	}
	fstr = sl_readfile(path);
	if (!fstr)
	{
		ft_printf("Error\nType:File processing error\n");
		game->s_map.data = NULL;
		return (0);
	}
	game->s_map.data = ft_split(fstr, '\n');
	free(fstr);
	game->s_map.s = 32;
	game->s_map.spots[0] = 0;
	game->s_map.spots[1] = 0;
	game->s_map.spots[2] = 0;
	return (1);
}

int	sl_dmap(t_game *game)
{
	t_vec2i	iter;

	iter[1] = -1;
	while (++iter[1] < game->s_map.h)
	{
		iter[0] = -1;
		while (++iter[0] < game->s_map.w)
		{
			__sl_map_dcell(game, iter);
		}
	}
	return (1);
}

int	sl_unload_map(t_game *game)
{
	size_t	i;

	if (!game->s_map.data)
		return (0);
	i = -1;
	while (game->s_map.data[++i])
		free(game->s_map.data[i]);
	free(game->s_map.data);
	return (1);
}

static t_image	*__sl_map_getimg(t_game *game, t_vec2i p)
{
	char	c;

	c = game->s_map.data[p[1]][p[0]];
	if (c == '1')
		return (&game->s_assets.imgs[SO_LONG_SPRITE_WALL]);
	else if (c == 'C' || c == 'c')
		return (&game->s_assets.imgs[SO_LONG_SPRITE_COLL]);
	else if (c == 'E')
		return (&game->s_assets.imgs[SO_LONG_SPRITE_EXIT]);
	else if (c == 'P')
		return (&game->s_assets.imgs[SO_LONG_SPRITE_PLAY]);
	else
		return (&game->s_assets.imgs[SO_LONG_SPRITE_EMPT]);
}

static int	__sl_map_dcell(t_game *game, t_vec2i p)
{
	t_vec2i	pos;
	t_vec2i	siz;
	t_image	*img;

	img = __sl_map_getimg(game, p);
	siz[0] = game->s_map.s;
	siz[1] = game->s_map.s;
	pos[0] = p[0] * game->s_map.s;
	pos[1] = p[1] * game->s_map.s;
	return (sl_dimg(game, *img, pos, siz));
}
