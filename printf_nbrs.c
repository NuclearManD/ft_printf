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

int			printf_handle_number(int fd, va_list args, t_fmt_data *data)
{
	int len = 0;

	len += va_arg(args, int);
	return (printf_fill(fd, len, data));
}
