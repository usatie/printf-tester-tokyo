/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susami <susami@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 18:17:52 by susami            #+#    #+#             */
/*   Updated: 2022/04/13 23:24:01 by susami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libassert.h"
#include "stdarg.h"
#include <limits.h>
#include <stdio.h>
#include <string.h>

int	ft_printf(char *format, ...);

int	ft_printf(char *format, ...)
{
	va_list	args;
	va_start(args,format);
	write(STDOUT_FILENO, "%", 1);
	int ret = vprintf(format,args);
	va_end(args);
	return (ret);
}

#ifdef FT_PRINTF
# define F(format, ...) ({\
	fflush(stdout);\
	write(STDOUT_FILENO, "F(\"", 3);\
	write(STDOUT_FILENO, format, strlen(format));\
	write(STDOUT_FILENO, "\"): [", 5);\
    int ret = ft_printf(format, __VA_ARGS__);\
	fflush(stdout);\
	write(STDOUT_FILENO, "]\n", 2);\
	fflush(stdout);\
	printf("returned: [%i]\n", ret);\
	fflush(stdout);\
})
#else
#define F(format, ...) ({\
	fflush(stdout);\
	write(STDOUT_FILENO, "F(\"", 3);\
	write(STDOUT_FILENO, format, strlen(format));\
	write(STDOUT_FILENO, "\"): [", 5);\
    int ret = printf(format, __VA_ARGS__);\
	fflush(stdout);\
	write(STDOUT_FILENO, "]\n", 2);\
	fflush(stdout);\
	printf("returned: [%i]\n", ret);\
	fflush(stdout);\
})
#endif

int	main(void)
{
	/*
	ASSERT_TRUE(true);
	ASSERT_TRUE(false);
	ASSERT_EQ_I(INT_MAX, INT_MIN);
	ASSERT_EQ_I(10, 10);
	ASSERT_EQ_UI(11, 13);
	ASSERT_EQ_UI(3, 3);
	ASSERT_EQ_L(LONG_MAX, LONG_MIN);
	ASSERT_EQ_L(10, 10);
	ASSERT_EQ_UL((unsigned long)LONG_MAX + 2, (unsigned long)LONG_MAX + 3);
	ASSERT_EQ_UL(3, 3);
	ASSERT_EQ_MEM("1234567890qwertyuiop", "1234567890asdfghjkl:", 21);
	ASSERT_EQ_STR("1234567890qwertyuiop", "1234567890asdfghjkl:", 20);
	*/

	F("%s", "hello world");
	F("%i", -42);
	F("%d", -42);
	F("%u", 42);
	F("%p", (void *)42);

	return (0);
}
