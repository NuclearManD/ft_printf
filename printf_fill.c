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

int			printf_num_fill(int fd, int dlen, t_fmt_data *f, int is_zero)
{
	int size_out;
	int i;

	i = dlen;
	if (f->precision > i)
		i = f->precision;
	size_out = printf_fill(fd, dlen, f);
	if (!is_zero && f->cnvrt == 'x' && (f->flags & FLAG_POUND))
		size_out += write(fd, "0x", 2);
	else if (!is_zero && f->cnvrt == 'X' && (f->flags & FLAG_POUND))
		size_out += write(fd, "0X", 2);
	else if (f->cnvrt == 'o' && (f->flags & FLAG_POUND))
		size_out += write(fd, "0", 1);
	if (f->precision > 0)
		size_out += printf_put_many(fd, f->precision - dlen, '0');
	else if ((f->flags & (FLAG_ZERO | FLAG_MINUS)) == FLAG_ZERO)
		size_out += printf_put_many(fd, f->min_width - i, '0');
	return (size_out);
}

int			printf_fill(int fd, int dlen, t_fmt_data *f)
{
	int size;

	size = 0;
	if ((f->flags & (FLAG_ZERO | FLAG_MINUS)) == FLAG_ZERO && f->precision <= 0)
		;
	else if (f->min_width > 0)
		size += printf_put_many(fd, f->min_width - size - dlen, ' ');
	return (size);
}
