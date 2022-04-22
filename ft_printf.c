/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susami <susami@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 09:04:10 by susami            #+#    #+#             */
/*   Updated: 2022/04/22 20:44:36 by susami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include <stdio.h>
#include <unistd.h>
#include "libft.h"

static int out_size = 0;
static const char g_hex_lower[] = "0123456789abcdef";
static const char g_hex_upper[] = "0123456789ABCDEF";

void printf_c(char **format_ptr, va_list *ap)
{
    char    c;
    c = va_arg(*ap, int);
    (*format_ptr)++;
    out_size += write(STDOUT_FILENO, &c, 1);
}

void printf_s(char **format_ptr, va_list *ap)
{
    char    *s;
    s = va_arg(*ap, char *);
    (*format_ptr)++;
    out_size += write(STDOUT_FILENO, s, ft_strlen(s));
}

static void putull_lower(unsigned long long n)
{
	char	c;

	if (n >= 16)
		putull_lower(n / 16);
	c = g_hex_lower[n % 16];
    out_size += write(STDOUT_FILENO, &c, 1);
}

static void putull_upper(unsigned long long n)
{
	char	c;

	if (n >= 16)
		putull_upper(n / 16);
	c = g_hex_upper[n % 16];
    out_size += write(STDOUT_FILENO, &c, 1);
}

void printf_p(char **format_ptr, va_list *ap)
{
    unsigned long long  p;

    (*format_ptr)++;
    p = va_arg(*ap, unsigned long long);
    out_size += write(STDOUT_FILENO, "0x", 2);
    putull_lower(p);
}

static void	putui(unsigned int n)
{
	char	c;

	if (n >= 10)
		putui(n / 10);
	c = n % 10 + '0';
    out_size += write(STDOUT_FILENO, &c, 1);
}

// putui(-INT_MIN) works fine.
// Because... -INT_MIN -> INT_MIN -> ((unsigned int)INT_MAX + 1)
void	puti(int n)
{
	if (n < 0)
	{
        out_size += write(STDOUT_FILENO, "-", 1);
		putui(-n);
	}
	else
		putui(n);
}

void printf_di(char **format_ptr, va_list *ap)
{
    int     x;
    size_t  i;

    (*format_ptr)++;
    x = va_arg(*ap, int);
    puti(x);
}

void printf_u(char **format_ptr, va_list *ap)
{
    unsigned int     x;
    size_t  i;

    (*format_ptr)++;
    x = va_arg(*ap, unsigned int);
    putui(x);
}

void printf_x(char **format_ptr, va_list *ap)
{
    unsigned int     x;
    size_t  i;

    (*format_ptr)++;
    x = va_arg(*ap, unsigned int);
    putull_lower(x);
}

void printf_X(char **format_ptr, va_list *ap)
{
    unsigned int     x;
    size_t  i;

    (*format_ptr)++;
    x = va_arg(*ap, unsigned int);
    putull_upper(x);
}

void printf_one(char **format_ptr, va_list *args)
{
    if (**format_ptr == '%')
        out_size += write(STDOUT_FILENO, *format_ptr++, 1);
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
        printf_x(format_ptr, args);
    else if (**format_ptr == 'X')
        printf_X(format_ptr, args);
}

int ft_printf(const char *format, ...)
{
    out_size = 0;
	va_list	ap;
	va_start(ap,format);
    while (*format)
    {
        if (*format == '%')
        {
            format++;
            printf_one((char **)&format, &ap);
        }
        else
            out_size += write(STDOUT_FILENO, format++, 1);
    }
	va_end(ap);
	return (out_size);
}
