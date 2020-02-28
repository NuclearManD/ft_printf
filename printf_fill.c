/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_fill.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbrophy <dbrophy@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/27 13:43:21 by dbrophy           #+#    #+#             */
/*   Updated: 2020/02/27 13:43:21 by dbrophy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "unistd.h"

int			printf_put_many(int fd, int sz, char c)
{
	int res;

	res = 0;
	while (sz-- > 0)
		res += write(fd, &c, 1);
	return (res);
}

int			printf_fill(int fd, int dlen, t_fmt_data *f)
{
	int size;

	size = 0;
	/*if ((f->flags & (FLAG_ZERO | FLAG_MINUS)) == FLAG_ZERO && !(f->precision))
		size += printf_put_many(fd, f->min_width - size - dlen, '0');
	else */if (f->min_width > 0)
		size += printf_put_many(fd, f->min_width - size - dlen, ' ');
	if (f->cnvrt == 'x' && (f->flags & FLAG_POUND))
		size += write(fd, "0x", 2);
	else if (f->cnvrt == 'X' && (f->flags & FLAG_POUND))
		size += write(fd, "0X", 2);
	return (size);
}
