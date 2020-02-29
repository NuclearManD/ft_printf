/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_nbrs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbrophy <dbrophy@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/26 17:29:35 by dbrophy           #+#    #+#             */
/*   Updated: 2020/02/26 17:29:35 by dbrophy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <unistd.h>
#include <stdarg.h>
#include <stdint.h>

static int	rec_pn_base(int fd, uintmax_t nb, char base, char caps)
{
	int i;
	int d;

	i = 0;
	if (nb < (unsigned char)base)
		d = nb;
	else
	{
		i = rec_pn_base(fd, nb / base, base, caps);
		d = nb % base;
	}
	if (caps)
		return (i + write(fd, &("0123456789ABCDEF"[d]), 1));
	return (i + write(fd, &("0123456789abcdef"[d]), 1));
}

static int	putnbr_base(int fd, uintmax_t nb, char base, char caps)
{
	int i;

	/*if (nb < 0)
	{
		i = write(fd, "-", 1);
		if (-nb >= base)
			i += rec_pn_base(fd, -(nb / base), base, caps);
		i += wr_digit(fd, nb % base, caps);
	}
	else*/
		i = rec_pn_base(fd, nb, base, caps);
	return (i);
}

static int	get_num_len(uintmax_t num, char base, t_fmt_data *data)
{
	int len;

	if (data->precision <= 0 && num == 0)
		return (0);
	len = /*num < 0 ||*/ (data->flags & (FLAG_PLUS | FLAG_SPCE));
	if (num == 0)
		len++;
	if (data->flags & FLAG_POUND)
	{
		if ((data->cnvrt | 32) == 'x' && num != 0)
			len += 2;
		else if (data->cnvrt == 'o')
			len++;
	}
	while (num != 0)
	{
		num = num / base;
		len++;
	}
	return (len);
}

uintmax_t	pullnum(int type, va_list args)
{
	uintmax_t			num;

	if (type == MOD_UNSPECIFIED)
		num = va_arg(args, unsigned int);
	else if (type == MOD_CHAR)
		num = va_arg(args, unsigned int) & 255;
	else if (type == MOD_SHORT)
		num = va_arg(args, unsigned int) & 65335;
	else if (type == MOD_LONG)
		num = va_arg(args, unsigned long);
	else if (type == MOD_LONG_LONG)
		num = va_arg(args, unsigned long long);
	else if (type == MOD_INTMAX_T)
		num = va_arg(args, intmax_t);
	else
		num = va_arg(args, size_t);
	return (num);
}

int			printf_handle_number(int fd, va_list args, t_fmt_data *data)
{
	int					len;
	int					i;
	uintmax_t			num;
	char				base;

	num = pullnum(data->type, args);
	if (data->cnvrt == 'd' || data->cnvrt == 'i' || data->cnvrt == 'u')
		base = 10;
	if (data->cnvrt == 'o')
		base = 8;
	if (data->cnvrt == 'x' || data->cnvrt == 'X')
		base = 16;
	i = get_num_len(num, base, data);
	len = printf_num_fill(fd, i, data, num == 0);
	if (data->precision != 0 || num != 0)
		len += putnbr_base(fd, num, base, data->cnvrt == 'X');
	return (len + printf_put_many(fd, -data->min_width - len, ' '));
}
