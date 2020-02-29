/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbrophy <dbrophy@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/26 17:36:59 by dbrophy           #+#    #+#             */
/*   Updated: 2020/02/26 17:36:59 by dbrophy          ###   ########.fr       */
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

# define MOD_UNSPECIFIED 0
# define MOD_CHAR 1
# define MOD_SHORT 2
# define MOD_LONG 3
# define MOD_LONG_LONG 4
# define MOD_INTMAX_T 5
# define MOD_SIZE_T 6

# define UNSIGNED_FLAG_MASK (FLAG_POUND | FLAG_ZERO | FLAG_MINUS)

typedef struct	s_fmt_d {
	unsigned int	flags;
	char			type;
	int				min_width;
	int				precision;
	char			cnvrt;
}				t_fmt_d;

int				ft_printf(const char *fmt, ...);
int				ft_fprintf(int fd, const char *fmt, ...);
int				ft_printfv(const char *fmt, va_list args);
int				ft_fprintfv(int fd, const char *fmt, va_list args);
int				printf_handle_char(int fd, va_list args, t_fmt_d *data);
void			scan_nums(const char **fmtp, int *min_width, int *precision);
char			in_str(char c, const char *s);
int				printf_handle_percent(const char **fmtp, int fd, va_list args);
int				printf_handle_number(int fd, va_list args, t_fmt_d *data);
int				printf_handle_string(int fd, va_list args, t_fmt_d *data);
int				printf_fill(int fd, int dlen, t_fmt_d *f);
int				printf_put_many(int fd, int sz, char c);
int				printf_num_fill(int fd, int dlen, t_fmt_d *f, int is_zero);

#endif
