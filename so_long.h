/* ************************************************************************** */
/*																			  */
/*														  :::	   ::::::::   */
/*	 so_long.h											:+:		 :+:	:+:   */
/*													  +:+ +:+		  +:+	  */
/*	 By: joleksia <marvin@42.fr>					+#+  +:+	   +#+		  */
/*												  +#+#+#+#+#+	+#+			  */
/*	 Created: 2025/01/06 08:14:29 by joleksia		   #+#	  #+#			  */
/*	 Updated: 2025/01/06 18:08:21 by joleksia		  ###	########.fr		  */
/*																			  */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

/*	SECTION:
 *		Inclusions
 * */
# include <X11/X.h>
# include <X11/keysym.h>
# include <stddef.h>
# include "./libft/libft.h"
# include "./libft/ft_printf.h"
# include "./minilibx/mlx.h"
# include "./minilibx/mlx_int.h"

/*	SECTION:
 *		Macro Definitions
 * */
# define SO_LONG_RED		0xfff54040
# define SO_LONG_DARKRED	0xff8a2020
# define SO_LONG_GREEN		0xffa0f00a
# define SO_LONG_DARKGREEN	0xff2e7010
# define SO_LONG_BLUE		0xff0ad4f0
# define SO_LONG_DARKBLUE	0xff0d0d3d
# define SO_LONG_WHITE		0xffffffff
# define SO_LONG_BLACK		0xff000000
# define SO_LONG_BLANK		0x00000000
# define SO_LONG_GOLD		0xffffb224

# define SO_LONG_SPRITE_EMPT	0
# define SO_LONG_SPRITE_WALL	1
# define SO_LONG_SPRITE_COLL	2
# define SO_LONG_SPRITE_PLAY	3
# define SO_LONG_SPRITE_EXIT	4

/*	SECTION:
 *		Typedefs
 * */
typedef int		t_vec2i[2];
typedef int		t_vec3i[3];

typedef int		t_pix;

typedef struct s_wnd
{
	void	*ptr;
	int		w;
	int		h;
}				t_wnd;

typedef struct s_image
{
	void	*ptr;
	char	*pix;
	int		bits;
	int		len;
	int		endian;
}				t_image;

typedef struct s_game
{
	struct
	{
		t_xvar	*ptr;
		t_wnd	wnd;
		t_image	data;
	}			s_mlx;
	struct
	{
		char	**data;
		int		w;
		int		h;
		int		s;
		t_vec3i	spots;
	}			s_map;
	struct
	{
		t_vec2i	pos;
		int		steps;
	}			s_player;
	struct
	{
		t_image	*imgs;
		size_t	c;
	}			s_assets;
}				t_game;

/*	SECTION:
 *		Function declarations
 * */

/* ./so_long.c */
int		sl_init(t_game *game, int w, int h, char *t);
int		sl_input(int key, t_game *game);
int		sl_update(t_game *game);
int		sl_close(t_game *game);

/* ./render.c */
t_pix	sl_getpix(t_image *img, int x, int y);
int		sl_setpix(t_game *game, int x, int y, t_pix pix);
int		sl_clear(t_game *game, t_pix pix);
int		sl_drect(t_game *game, t_vec2i p, t_vec2i s, t_pix pix);

/* ./map0.c ./map1.c ./map2.c */
int		sl_readmap(t_game *game, const char *path);
int		sl_validate_map(t_game *game);
int		sl_validate_path(t_game *game);
int		sl_dmap(t_game *game);
int		sl_unload_map(t_game *game);

/* ./io.c */
char	*sl_readfile(const char *path);
size_t	sl_fsize(const char *path);

/* ./player.c */
int		sl_pinit(t_game *game);
int		sl_ppos_x(t_game *game);
int		sl_ppos_y(t_game *game);
int		sl_pmov(t_game *game, t_vec2i dir);

/* ./assets.c */
int		sl_init_assets(t_game *game, size_t n);
t_image	*sl_getimgptr(t_game *game, int i);
int		sl_unload_assets(t_game *game);

/* ./img.c */
int		sl_load_img(t_game *game, t_image *img, char *path);
int		sl_dimg(t_game *game, t_image img, t_vec2i p, t_vec2i s);
int		sl_unload_img(t_game *game, t_image *img);

#endif
