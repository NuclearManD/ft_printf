/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbrophy <dbrophy@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 18:46:51 by dbrophy           #+#    #+#             */
/*   Updated: 2020/02/25 18:46:51 by dbrophy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

#include <stdarg.h>

int				ft_printf(const char *fmt, ...);
int				ft_fprintf(int fd, const char *fmt, ...);
int				ft_printfv(const char *fmt, va_list args);
int				ft_fprintfv(int fd, const char *fmt, va_list args);

#endif
