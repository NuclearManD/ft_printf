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

# include <stdarg.h>

# define FLAG_POUND 1
# define FLAG_ZERO 2
# define FLAG_MINUS 4
# define FLAG_PLUS 8
# define FLAG_SPCE 16

int				ft_printf(const char *fmt, ...);
int				ft_fprintf(int fd, const char *fmt, ...);
int				ft_printfv(const char *fmt, va_list args);
int				ft_fprintfv(int fd, const char *fmt, va_list args);
int				printf_handle_percent(const char **fmtp, int fd, va_list  args);
int				printf_handle_string(int fd, va_list args);

#endif
