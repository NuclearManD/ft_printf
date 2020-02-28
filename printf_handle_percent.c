/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_handle_percent.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbrophy <dbrophy@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 21:51:18 by dbrophy           #+#    #+#             */
/*   Updated: 2020/02/25 21:51:18 by dbrophy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "unistd.h"
#include <stdarg.h>

static unsigned	handle_flags_set_1(const char **fmtp)
{
	unsigned int out;

	out = 0;
	while (**fmtp)
	{
		if (**fmtp == '#' && !(out & FLAG_POUND))
			out |= FLAG_POUND;
		else if (**fmtp == ' ' && !(out & FLAG_SPCE))
			out |= FLAG_SPCE;
		else if (**fmtp == '0' && !(out & FLAG_ZERO))
			out |= FLAG_ZERO;
		else if (**fmtp == '-' && !(out & FLAG_MINUS))
			out |= FLAG_MINUS;
		else if (**fmtp == '+' && !(out & FLAG_PLUS))
			out |= FLAG_PLUS;
		else
			break ;
		(*fmtp)++;
	}
	return (out);
}

static char		handle_length_mod(const char **fmtp)
{
	char out;

	if (**fmtp == 'h' && *(*fmtp + 1) != 'h')
		out = MOD_SHORT;
	else if (**fmtp == 'h' && *(*fmtp + 1) == 'h')
	{
		(*fmtp)++;
		out = MOD_CHAR;
	}
	else if (**fmtp == 'l' && *(*fmtp + 1) != 'l')
		out = MOD_LONG;
	else if (**fmtp == 'l' && *(*fmtp + 1) == 'l')
	{
		(*fmtp)++;
		out = MOD_LONG_LONG;
	}
	else if (**fmtp == 'j')
		out = MOD_INTMAX_T;
	else if (**fmtp == 'z')
		out = MOD_SIZE_T;
	else
		return (MOD_UNSPECIFIED);
	(*fmtp)++;
	return (out);
}

/*
** Scan width and precision bro :dab:
*/

void			scan_nums(const char **fmtp, int *min_width, int *precision)
{
	int isneg;

	*min_width = 0;
	isneg = 1 - 2 * (**fmtp == '-');
	if (**fmtp == '-' || **fmtp == '+')
		(*fmtp)++;
	while ((**fmtp <= '9') && (**fmtp >= '0'))
		*min_width = ((*min_width) * 10) + isneg * (*((*fmtp)++) - '0');
	if (**fmtp == '.')
	{
		*precision = 0;
		(*fmtp)++;
		while ((**fmtp <= '9') && (**fmtp >= '0'))
			*precision = ((*precision) * 10) + *((*fmtp)++) - '0';
	}
	else
		*precision = 0;
}

char			in_str(char c, const char *s)
{
	while (*s)
		if (c == *(s++))
			return (1);
	return (0);
}

int				printf_handle_percent(const char **fmtp, int fd, va_list args)
{
	t_fmt_data data;

	if (**fmtp == '%')
		return (write(fd, "%", 1));
	data.flags = handle_flags_set_1(fmtp);
	scan_nums(fmtp, &data.min_width, &data.precision);
	data.type = handle_length_mod(fmtp);
	data.cnvrt = **fmtp;
	if (data.cnvrt == 'D' || data.cnvrt == 'O' || data.cnvrt == 'U')
	{
		data.cnvrt += 32;
		data.type = MOD_LONG;
	}
	if (data.cnvrt == 's' || data.cnvrt == 'S')
		return (printf_handle_string(fd, args, &data));
	else if (in_str(data.cnvrt, "pdDioOuUxX"))
		return (printf_handle_number(fd, args, &data));
	else
		return (printf_handle_char(fd, args, &data));
}
