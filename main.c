/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susami <susami@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 18:17:52 by susami            #+#    #+#             */
/*   Updated: 2022/04/21 23:05:45 by susami           ###   ########.fr       */
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
	if (strchr(format, 's'))
		write(STDOUT_FILENO, "\\", 1);
	va_end(args);
	return (ret);
}

#define F(...) ({\
	fflush(stdout);\
	char s[30];\
	memset(s, ' ', 30);\
	strcpy(s, "F(");\
	strcpy(s + 2, #__VA_ARGS__);\
	strcpy(s + 2 + strlen(#__VA_ARGS__), ")");\
	printf("%-30s: stdout=[", s);\
	fflush(stdout);\
    int ret = _F(__VA_ARGS__);\
	fflush(stdout);\
	write(STDOUT_FILENO, "], ", 3);\
	printf("ret=[%i]\n", ret);\
	fflush(stdout);\
})

#ifdef FT_PRINTF
# define _F(...) ({ft_printf(__VA_ARGS__);})
#else
# define _F(...) ({printf(__VA_ARGS__);})
#endif

int	main(void)
{
	F("%s", "hello world");
	F("%i", -42);
	F("%d", -42);
	F("%u", 42);
	F("%p", (void *)42);

	return (0);
}
