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

static int	putnbr_base(int fd, intmax_t n, char base, char caps, t_fmt_d *f)
{
	int i;

	if (n < 0 && base == 10 && f->cnvrt != 'u')
	{
		if (-n >= base)
			i = rec_pn_base(fd, -(n / base), base, caps);
		else
			i = 0;
		i += rec_pn_base(fd, (-n) % base, base, caps);
	}
	else
	{
		i = rec_pn_base(fd, n, base, caps);
	}
	return (i);
}

static int	get_num_len(intmax_t num, char base, t_fmt_d *data)
{
	int len;

	if (data->precision <= 0 && num == 0)
		return (0);
	len = (num < 0 && base == 10) || (data->flags & (FLAG_PLUS | FLAG_SPCE));
	if (data->cnvrt == 'u')
		len = 0;
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

intmax_t	pullnum(int type, va_list args, int is_unsigned)
{
	if (type == MOD_UNSPECIFIED && is_unsigned)
		return (va_arg(args, unsigned int));
	else if (type == MOD_UNSPECIFIED && !is_unsigned)
		return ((intmax_t)va_arg(args, int));
	else if (type == MOD_CHAR && is_unsigned)
		return (va_arg(args, unsigned int) & 255);
	else if (type == MOD_CHAR && !is_unsigned)
		return ((char)(va_arg(args, unsigned int) & 255));
	else if (type == MOD_SHORT && is_unsigned)
		return (va_arg(args, unsigned int) & 65335);
	else if (type == MOD_SHORT && !is_unsigned)
		return ((short)(va_arg(args, unsigned int) & 65335));
	else if (type == MOD_LONG && is_unsigned)
		return (va_arg(args, unsigned long));
	else if (type == MOD_LONG && !is_unsigned)
		return (va_arg(args, long));
	else if (type == MOD_LONG_LONG && is_unsigned)
		return (va_arg(args, unsigned long long));
	else if (type == MOD_LONG_LONG && !is_unsigned)
		return (va_arg(args, long long));
	else if (type == MOD_INTMAX_T)
		return (va_arg(args, intmax_t));
	else
		return (va_arg(args, size_t));
}

int			printf_handle_number(int fd, va_list args, t_fmt_d *data)
{
	int					len;
	int					i;
	intmax_t			num;
	char				base;

	if (data->cnvrt == 'd' || data->cnvrt == 'i' || data->cnvrt == 'u')
		base = 10;
	if (data->cnvrt == 'o')
		base = 8;
	if (data->cnvrt == 'x' || data->cnvrt == 'X')
		base = 16;
	if (base != 10 || data->cnvrt == 'u')
		data->flags &= UNSIGNED_FLAG_MASK;
	num = pullnum(data->type, args, base != 10 || data->cnvrt == 'u');
	i = get_num_len(num, base, data);
	len = printf_num_fill(fd, i, data, num, base);
	if (data->precision != 0 || num != 0)
		len += putnbr_base(fd, num, base, data->cnvrt == 'X', data);
	return (len + printf_put_many(fd, -data->min_width - len, ' '));
}
