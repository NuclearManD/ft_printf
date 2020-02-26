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

#include <unistd.h>
#include <stdarg.h>

int				printf_handle_string(int fd, va_list args)
{
	const char	*str;
	int			len;

	str = va_arg(args, const char*);
	if (str == NULL)
		str = "null";
	len = 0;
	while (str[len])
		len++;
	return (write(fd, str, len));
}
