/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joleksia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 08:58:08 by joleksia          #+#    #+#             */
/*   Updated: 2025/01/15 08:18:17 by joleksia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static int	__sl_pobjcheck(t_game *game, t_vec2i dir, char c);

int	sl_pinit(t_game *game)
{
	t_vec2i	iter;

	iter[1] = -1;
	while (++iter[1] < game->s_map.h)
	{
		iter[0] = -1;
		while (++iter[0] < game->s_map.w)
		{
			if (game->s_map.data[iter[1]][iter[0]] == 'P')
			{
				game->s_player.pos[0] = iter[0];
				game->s_player.pos[1] = iter[1];
				iter[1] = game->s_map.h;
				break ;
			}
		}
	}
	game->s_player.steps = 0;
	return (1);
}

int	sl_ppos_x(t_game *game)
{
	return (game->s_player.pos[0]);
}

int	sl_ppos_y(t_game *game)
{
	return (game->s_player.pos[1]);
}

int	sl_pmov(t_game *game, t_vec2i dir)
{
	if (__sl_pobjcheck(game, dir, '1'))
		return (0);
	else if (__sl_pobjcheck(game, dir, 'C') || __sl_pobjcheck(game, dir, 'c'))
		game->s_map.spots[0]--;
	else if (__sl_pobjcheck(game, dir, 'E'))
	{
		if (game->s_map.spots[0])
		{
			ft_printf("WARN.: You must collect all the collectibles!\n");
			return (0);
		}
		ft_printf("INFO.: Game over!\n");
		return (2);
	}
	game->s_map.data[game->s_player.pos[1]][game->s_player.pos[0]] = '0';
	game->s_player.pos[0] += dir[0];
	game->s_player.pos[1] += dir[1];
	game->s_map.data[game->s_player.pos[1]][game->s_player.pos[0]] = 'P';
	ft_printf("INFO.: Player steps: %d\n", ++game->s_player.steps);
	return (1);
}

static int	__sl_pobjcheck(t_game *game, t_vec2i dir, char c)
{
	int	x;
	int	y;

	x = game->s_player.pos[0] + dir[0];
	y = game->s_player.pos[1] + dir[1];
	if (game->s_map.data[y][x] == c)
		return (1);
	return (0);
}
