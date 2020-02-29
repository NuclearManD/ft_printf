/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_strs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbrophy <dbrophy@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/26 15:06:47 by dbrophy           #+#    #+#             */
/*   Updated: 2020/02/26 15:06:47 by dbrophy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <unistd.h>
#include <stdarg.h>
#include <wchar.h>

int			printf_handle_string(int fd, va_list args, t_fmt_d *data)
{
	const char	*str;
	wchar_t		*wstr;
	int			len;
	int			printed;

	if (data->cnvrt == 'S' || data->type == MOD_LONG)
	{
		wstr = va_arg(args, wchar_t*);
		if (wstr == NULL)
			wstr = L"(null)";
		len = 0;
		while (wstr[len])
			len++;
		printed = printf_fill(fd, len, data);
		return (printed + write(fd, wstr, len * sizeof(wchar_t)));
	}
	str = va_arg(args, const char*);
	if (str == NULL)
		str = "(null)";
	len = 0;
	while (str[len])
		len++;
	printed = printf_fill(fd, len, data);
	return (printed + write(fd, str, len));
}
