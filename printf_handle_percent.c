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

static unsigned	handle_flags(const char **fmtp)
{
	unsigned int out;

	out = 0;
	while (**fmtp)
	{
		if (**fmtp == '#')
			out |= FLAG_POUND;
		else if (**fmtp == ' ')
			out |= FLAG_SPCE;
		else if (**fmtp == '0')
			out |= FLAG_ZERO;
		else if (**fmtp == '-')
			out |= FLAG_MINUS;
		else if (**fmtp == '+')
			out |= FLAG_PLUS;
		else
			break ;
		(*fmtp)++;
	}
	return (out);
}

int				printf_handle_percent(const char **fmtp, int fd, va_list args)
{
	unsigned int flags;

	if (**fmtp == '%')
		return (write(fd, "%", 1));
	flags = handle_flags(fmtp);
	if (**fmtp == 's')
		return (printf_handle_string(fd, args));
	return (-1);
}
