/* ************************************************************************** */
/*																			  */
/*														  :::	   ::::::::   */
/*	 io.c												:+:		 :+:	:+:   */
/*													  +:+ +:+		  +:+	  */
/*	 By: joleksia <marvin@42.fr>					+#+  +:+	   +#+		  */
/*												  +#+#+#+#+#+	+#+			  */
/*	 Created: 2025/01/11 09:02:58 by joleksia		   #+#	  #+#			  */
/*	 Updated: 2025/01/11 09:02:59 by joleksia		  ###	########.fr		  */
/*																			  */
/* ************************************************************************** */

#include "so_long.h"

size_t	sl_fsize(const char *path)
{
	size_t	flen;
	char	c;
	int		fd;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (0);
	flen = 0;
	while (read(fd, &c, 1))
		flen++;
	close(fd);
	return (flen);
}

char	*sl_readfile(const char *path)
{
	char	*str;
	size_t	flen;
	int		fd;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (NULL);
	flen = sl_fsize(path);
	str = ft_calloc(flen + 1, sizeof(char));
	if (!str)
	{
		close(fd);
		return (NULL);
	}
	if (read(fd, str, flen) < 0)
	{
		close(fd);
		return (NULL);
	}
	close(fd);
	return (str);
}
