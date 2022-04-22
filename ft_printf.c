/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susami <susami@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 09:04:10 by susami            #+#    #+#             */
/*   Updated: 2022/04/23 08:23:13 by susami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include <stdio.h>
#include <unistd.h>

static const char	*g_hex_lower = "0123456789abcdef";
static const char	*g_hex_upper = "0123456789ABCDEF";

static int			g_out_size = 0;
void	put_str_buf(char *str, size_t len)
{
	g_out_size += write(STDOUT_FILENO, str, len);
}

static int	ft_strlen(char *str)
{
	size_t	cnt;

	cnt = 0;
	while (*str++)
		cnt++;
	return (cnt);
}

void	printf_c(char **format_ptr, va_list *ap)
{
	char	c;

	c = va_arg(*ap, int);
	(*format_ptr)++;
	put_str_buf(&c, 1);
}

void	printf_s(char **format_ptr, va_list *ap)
{
	char	*s;

	s = va_arg(*ap, char *);
	(*format_ptr)++;
	if (s == NULL)
		put_str_buf("(null)", 6);
	else
		put_str_buf(s, ft_strlen(s));
}

static void	puthex_lower(unsigned long long n)
{
	char	c;

	if (n >= 16)
		puthex_lower(n / 16);
	c = g_hex_lower[n % 16];
	put_str_buf(&c, 1);
}

static void	puthex_upper(unsigned long long n)
{
	char	c;

	if (n >= 16)
		puthex_upper(n / 16);
	c = g_hex_upper[n % 16];
	put_str_buf(&c, 1);
}

void	printf_p(char **format_ptr, va_list *ap)
{
	unsigned long long	p;

	(*format_ptr)++;
	p = va_arg(*ap, unsigned long long);
	put_str_buf("0x", 2);
	puthex_lower(p);
}

static void	putui(unsigned int n)
{
	char	c;

	if (n >= 10)
		putui(n / 10);
	c = n % 10 + '0';
	put_str_buf(&c, 1);
}

// putui(-INT_MIN) works fine.
// Because... -INT_MIN -> INT_MIN -> ((unsigned int)INT_MAX + 1)
void	puti(int n)
{
	if (n < 0)
	{
		put_str_buf("-", 1);
		putui(-n);
	}
	else
		putui(n);
}

void	printf_di(char **format_ptr, va_list *ap)
{
	int		x;
	size_t	i;

	(*format_ptr)++;
	x = va_arg(*ap, int);
	puti(x);
}

void	printf_u(char **format_ptr, va_list *ap)
{
	unsigned int	x;
	size_t			i;

	(*format_ptr)++;
	x = va_arg(*ap, unsigned int);
	putui(x);
}

void	printf_x_lower(char **format_ptr, va_list *ap)
{
	unsigned int	x;
	size_t			i;

	(*format_ptr)++;
	x = va_arg(*ap, unsigned int);
	puthex_lower(x);
}

void	printf_x_upper(char **format_ptr, va_list *ap)
{
	unsigned int	x;
	size_t			i;

	(*format_ptr)++;
	x = va_arg(*ap, unsigned int);
	puthex_upper(x);
}

void	printf_percent(char **format_ptr)
{
	(*format_ptr)++;
	put_str_buf("%", 1);
}

void	printf_one(char **format_ptr, va_list *args)
{
	if (**format_ptr == '%')
		printf_percent(format_ptr);
	else if (**format_ptr == 'c')
		printf_c(format_ptr, args);
	else if (**format_ptr == 's')
		printf_s(format_ptr, args);
	else if (**format_ptr == 'p')
		printf_p(format_ptr, args);
	else if (**format_ptr == 'd' || **format_ptr == 'i')
		printf_di(format_ptr, args);
	else if (**format_ptr == 'u')
		printf_u(format_ptr, args);
	else if (**format_ptr == 'x')
		printf_x_lower(format_ptr, args);
	else if (**format_ptr == 'X')
		printf_x_upper(format_ptr, args);
}

int	ft_printf(const char *format, ...)
{
	va_list	ap;

	g_out_size = 0;
	va_start(ap, format);
	while (*format)
	{
		if (*format == '%')
		{
			format++;
			printf_one((char **)&format, &ap);
		}
		else
			put_str_buf((char *)format++, 1);
	}
	va_end(ap);
	return (g_out_size);
}
