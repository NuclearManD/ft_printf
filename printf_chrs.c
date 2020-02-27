/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_chrs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbrophy <dbrophy@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/26 17:30:38 by dbrophy           #+#    #+#             */
/*   Updated: 2020/02/26 17:30:38 by dbrophy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <unistd.h>
#include <stdarg.h>
#include <wchar.h>

int			printf_handle_char(int fd, va_list args, t_fmt_data *data)
{
	char	c;
	wint_t	wc;

	if (data->cnvrt == 'c')
	{
		c = (char)va_arg(args, int);
		return (write(fd, &c, 1));
	}
	else if (data->cnvrt == 'C')
	{
		wc = va_arg(args, wint_t);
		return (write(fd, &wc, sizeof(wint_t)));
	}
	return (-1);
}
