/* ************************************************************************** */
/*																			  */
/*														  :::	   ::::::::   */
/*	 so_long.c											:+:		 :+:	:+:   */
/*													  +:+ +:+		  +:+	  */
/*	 By: joleksia <marvin@42.fr>					+#+  +:+	   +#+		  */
/*												  +#+#+#+#+#+	+#+			  */
/*	 Created: 2025/01/06 08:14:05 by joleksia		   #+#	  #+#			  */
/*	 Updated: 2025/01/06 09:09:57 by joleksia		  ###	########.fr		  */
/*																			  */
/* ************************************************************************** */

#include "so_long.h"

int	main(int ac, char **av)
{
	t_game	game;

	if (ac < 2)
	{
		ft_printf("./so_long [ FILE ]\n");
		return (1);
	}
	if (!sl_readmap(&game, av[1])
		|| !sl_validate_map(&game))
	{
		sl_unload_map(&game);
		exit(1);
	}
	sl_init(&game,
		game.s_map.w * game.s_map.s, game.s_map.h * game.s_map.s,
		"42warsaw - so_long"
		);
	sl_init_assets(&game, 5);
	mlx_loop(game.s_mlx.ptr);
	return (0);
}

int	sl_init(t_game *game, int w, int h, char *t)
{
	game->s_mlx.ptr = mlx_init();
	game->s_mlx.wnd.ptr = mlx_new_window(game->s_mlx.ptr, w, h, t);
	game->s_mlx.data.ptr = mlx_new_image(game->s_mlx.ptr, w, h);
	game->s_mlx.data.pix = mlx_get_data_addr(
			game->s_mlx.data.ptr,
			&game->s_mlx.data.bits,
			&game->s_mlx.data.len,
			&game->s_mlx.data.endian
			);
	game->s_mlx.wnd.w = w;
	game->s_mlx.wnd.h = h;
	mlx_loop_hook(game->s_mlx.ptr, sl_update, game);
	mlx_hook(game->s_mlx.wnd.ptr, 2, 1L << 0, sl_input, game);
	mlx_hook(game->s_mlx.wnd.ptr, 17, 0, sl_close, game);
	return (1);
}

int	sl_input(int key, t_game *game)
{
	int	pmov;

	if (key == XK_w || key == XK_s || key == XK_a || key == XK_d)
	{
		pmov = sl_pmov(game,
				(t_vec2i){
				(key == XK_d) - (key == XK_a),
				(key == XK_s) - (key == XK_w)
			}
				);
	}
	if (key == XK_Escape || pmov == 2)
		sl_close(game);
	return (0);
}

int	sl_update(t_game *game)
{
	sl_clear(game, SO_LONG_BLACK);
	sl_dmap(game);
	mlx_put_image_to_window(
		game->s_mlx.ptr,
		game->s_mlx.wnd.ptr,
		game->s_mlx.data.ptr,
		0, 0
		);
	return (0);
}

int	sl_close(t_game *game)
{
	sl_unload_assets(game);
	sl_unload_map(game);
	mlx_loop_end(game->s_mlx.ptr);
	mlx_destroy_image(game->s_mlx.ptr, game->s_mlx.data.ptr);
	mlx_destroy_window(game->s_mlx.ptr, game->s_mlx.wnd.ptr);
	mlx_destroy_display(game->s_mlx.ptr);
	free(game->s_mlx.ptr);
	exit(0);
}
