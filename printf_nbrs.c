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

static int	wr_digit(int fd, int d, char use_caps)
{
	if (use_caps)
		return (write(fd, &("0123456789ABCDEF"[d]), 1));
	return (write(fd, &("0123456789abcdef"[d]), 1));
}

static int	rec_pn_base(int fd, uintmax_t nb, char base, char caps)
{
	int i;

	if (nb < (unsigned char)base)
		return (wr_digit(fd, nb, caps));
	else
	{
		i = rec_pn_base(fd, nb / base, base, caps);
		return (i + wr_digit(fd, nb % base, caps));
	}
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

	len = /*num < 0 ||*/ (data->flags & (FLAG_PLUS | FLAG_SPCE));
	if (num == 0)
		len++;
	while (num != 0)
	{
		num = num / base;
		len++;
	}
	return (len);
}

int			printf_handle_number(int fd, va_list args, t_fmt_data *data)
{
	int					len;
	uintmax_t			num;
	char				base;

	if (data->type == MOD_UNSPECIFIED)
		num = va_arg(args, unsigned int);
	else if (data->type == MOD_CHAR)
		num = va_arg(args, unsigned int) & 255;
	else if (data->type == MOD_SHORT)
		num = va_arg(args, unsigned int) & 65335;
	else if (data->type == MOD_LONG)
		num = va_arg(args, unsigned long);
	else if (data->type == MOD_LONG_LONG)
		num = va_arg(args, unsigned long long);
	else if (data->type == MOD_INTMAX_T)
		num = va_arg(args, intmax_t);
	else
		num = va_arg(args, size_t);
	if (data->cnvrt == 'd' || data->cnvrt == 'i' || data->cnvrt == 'u')
		base = 10;
	if (data->cnvrt == 'o')
		base = 8;
	if (data->cnvrt == 'x' || data->cnvrt == 'X')
		base = 16;
	len = printf_fill(fd, get_num_len(num, base, data), data);
	len += putnbr_base(fd, num, base, data->cnvrt == 'X');
	return (len + printf_put_many(fd, -data->min_width - len, ' '));
}
