/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joleksia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 10:27:55 by joleksia          #+#    #+#             */
/*   Updated: 2025/01/15 08:16:36 by joleksia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static int	__sl_validate_exit(t_game *game, int x, int y);
static int	__sl_validate_coll(t_game *game, int x, int y);

int	sl_validate_path(t_game *game)
{
	return (
		__sl_validate_exit(game, sl_ppos_x(game), sl_ppos_y(game))
		&& __sl_validate_coll(game, sl_ppos_x(game), sl_ppos_y(game))
	);
}

static int	__sl_validate_exit(t_game *game, int x, int y)
{
	if (x < 0 || y < 0 || x >= game->s_map.w || y >= game->s_map.h)
		return (0);
	else if (game->s_map.data[y][x] == 'E')
		return (1);
	else if (ft_strchr("*1", game->s_map.data[y][x]))
		return (0);
	if (game->s_map.data[y][x] == '0')
		game->s_map.data[y][x] = '*';
	return (
		__sl_validate_exit(game, x, y + 1)
		|| __sl_validate_exit(game, x + 1, y)
		|| __sl_validate_exit(game, x, y - 1)
		|| __sl_validate_exit(game, x - 1, y)
	);
}

static int	__sl_validate_coll(t_game *game, int x, int y)
{
	static size_t	i = 0;

	if (x < 0 || y < 0 || x >= game->s_map.w || y >= game->s_map.h)
		return (0);
	else if (game->s_map.data[y][x] == 'C')
	{
		i++;
		game->s_map.data[y][x] = 'c';
	}
	else if (ft_strchr(".1Ec", game->s_map.data[y][x]))
		return (0);
	if (ft_strchr("0*", game->s_map.data[y][x]))
		game->s_map.data[y][x] = '.';
	return (
		(int) i == game->s_map.spots[0]
		|| __sl_validate_coll(game, x, y + 1)
		|| __sl_validate_coll(game, x + 1, y)
		|| __sl_validate_coll(game, x, y - 1)
		|| __sl_validate_coll(game, x - 1, y)
	);
}
