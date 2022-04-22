/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susami <susami@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 18:17:52 by susami            #+#    #+#             */
/*   Updated: 2022/04/22 08:57:49 by susami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stdarg.h"
#include <unistd.h>
#include <limits.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int	ft_printf(char *format, ...);

int	ft_printf(char *format, ...)
{
	va_list	args;
	va_start(args,format);
	int ret = vprintf(format,args);
	va_end(args);
	return (ret);
}

#define BUF_SIZE 1024
#define FMT_WIDTH 50
#define F(...) ({\
	fflush(stdout);\
	char buf[BUF_SIZE];\
	bzero(buf, BUF_SIZE);\
	strcpy(buf, "F(");\
	strcpy(buf + 2, #__VA_ARGS__);\
	strcpy(buf + 2 + strlen(#__VA_ARGS__), ")");\
	printf("%-*s: stdout=[", FMT_WIDTH, buf);\
	fflush(stdout);\
    int ret = _F(__VA_ARGS__);\
	fflush(stdout);\
	write(STDOUT_FILENO, "], ", 3);\
	printf("ret=[%i]\n", ret);\
	fflush(stdout);\
})

#ifdef FT_PRINTF
# define _F(...) ft_printf(__VA_ARGS__);
#else
# define _F(...) printf(__VA_ARGS__);
#endif


int	main(void)
{
    F("hello world");
	F("%c", 'h');
	F("%s", "hello world");
	F("%p", (void *)42);
	F("%d", -42);
	F("%i", -42);
	F("%u", 42);
	F("%x", 42);
	F("%X", 42);
    F("%c %s", 'h', "hello world");
    F("%c %s %p %d %i %u %x %X", 'h', "hello world", (void *)42, -42, -42, 42, 42, 42);

	return (0);
}
