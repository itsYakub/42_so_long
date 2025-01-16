/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joleksia <joleksia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 08:12:14 by joleksia          #+#    #+#             */
/*   Updated: 2025/01/15 08:21:36 by joleksia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

/* SECTION: File inclusions */
# include <unistd.h>
# include <stdlib.h>
# include <stdarg.h>
# include "./libft.h"

/* SECTION: Function declarations */
int	ft_printf(const char *s, ...);

#endif
