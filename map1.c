/* ************************************************************************** */
/*																			  */
/*														  :::	   ::::::::   */
/*	 map1.c												:+:		 :+:	:+:   */
/*													  +:+ +:+		  +:+	  */
/*	 By: joleksia <marvin@42.fr>					+#+  +:+	   +#+		  */
/*												  +#+#+#+#+#+	+#+			  */
/*	 Created: 2025/01/11 08:58:42 by joleksia		   #+#	  #+#			  */
/*	 Updated: 2025/01/11 08:59:11 by joleksia		  ###	########.fr		  */
/*																			  */
/* ************************************************************************** */

#include "so_long.h"

static int	__sl_validate_spots(t_game *game);
static int	__sl_validate_size(t_game *game);
static int	__sl_validate_walls(t_game *game);

int	sl_validate_map(t_game *game)
{
	if (!__sl_validate_size(game))
	{
		ft_printf("Error\nType: Invalid size\n");
		return (0);
	}
	if (!__sl_validate_walls(game))
	{
		ft_printf("Error\nType: Map isn't rectangular\n");
		return (0);
	}
	if (!__sl_validate_spots(game))
	{
		ft_printf("Error\nType: Incorrect distribution of objects\n");
		return (0);
	}
	sl_pinit(game);
	if (!sl_validate_path(game))
	{
		ft_printf("Error\nType: Invalid map path\n");
		return (0);
	}
	return (1);
}

static int	__sl_validate_spots(t_game *game)
{
	t_vec2i	iter;

	iter[1] = -1;
	while (++iter[1] < game->s_map.h)
	{
		iter[0] = -1;
		while (++iter[0] < game->s_map.w)
		{
			if (ft_strchr("01CEP", game->s_map.data[iter[1]][iter[0]]))
			{
				if (game->s_map.data[iter[1]][iter[0]] == 'C')
					game->s_map.spots[0]++;
				else if (game->s_map.data[iter[1]][iter[0]] == 'P')
					game->s_map.spots[1]++;
				else if (game->s_map.data[iter[1]][iter[0]] == 'E')
					game->s_map.spots[2]++;
			}
			else
				return (0);
		}
	}
	return (game->s_map.spots[0]
		&& game->s_map.spots[1] == 1 && game->s_map.spots[2] == 1
	);
}

static int	__sl_validate_size(t_game *game)
{
	size_t	i;

	game->s_map.h = 0;
	while (game->s_map.data[game->s_map.h])
		game->s_map.h++;
	if (game->s_map.h <= 2)
		return (0);
	game->s_map.w = ft_strlen(game->s_map.data[0]);
	if (game->s_map.w <= 2)
		return (0);
	i = 0;
	while ((int)++i < game->s_map.h)
	{
		if (ft_strlen(game->s_map.data[i]) != game->s_map.w)
			return (0);
	}
	return (1);
}

static int	__sl_validate_walls(t_game *game)
{
	t_vec2i	iter;

	iter[1] = -1;
	while (++iter[1] < game->s_map.h)
	{
		if (iter[1] == 0 || iter[1] == game->s_map.h - 1)
		{
			iter[0] = -1;
			while (++iter[0] < game->s_map.w)
			{
				if (game->s_map.data[iter[1]][iter[0]] != '1')
					return (0);
			}
		}
		else
		{
			if (game->s_map.data[iter[1]][0] != '1' ||
				game->s_map.data[iter[1]][game->s_map.w - 1] != '1')
				return (0);
		}
	}
	return (1);
}
