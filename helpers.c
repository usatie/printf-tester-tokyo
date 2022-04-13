/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susami <susami@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 17:34:09 by susami            #+#    #+#             */
/*   Updated: 2022/04/13 19:09:30 by susami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <stdio.h>
#include <string.h>

void	ASSERT_TRUE(bool actual,
	char *caller_file, const char *caller_func, int caller_line)
{
	if (actual == false)
	{
		printf("%s failed: ", __func__);
		printf("func %s at file %s, line %d\n",
			caller_func, caller_file, caller_line);
	}
}

void	ASSERT_EQ_I(int actual, int expected,
	char *caller_file, const char *caller_func, int caller_line)
{
	if (actual != expected)
	{
		printf("%s failed: (\"%i\") is not equal to expected (\"%i\"). ",
			__func__, actual, expected);
		printf("func %s at file %s, line %d\n",
			caller_func, caller_file, caller_line);
	}
}

void	ASSERT_EQ_UI(unsigned int actual, unsigned int expected,
	char *caller_file, const char *caller_func, int caller_line)
{
	if (actual != expected)
	{
		printf("%s failed: (\"%u\") is not equal to expected (\"%u\"). ",
			__func__, actual, expected);
		printf("func %s at file %s, line %d\n",
			caller_func, caller_file, caller_line);
	}
}

void	ASSERT_EQ_L(long actual, long expected,
	char *caller_file, const char *caller_func, int caller_line)
{
	if (actual != expected)
	{
		printf("%s failed: (\"%li\") is not equal to expected (\"%li\"). ",
			__func__, actual, expected);
		printf("func %s at file %s, line %d\n",
			caller_func, caller_file, caller_line);
	}
}

void	ASSERT_EQ_UL(unsigned long actual, unsigned long expected,
	char *caller_file, const char *caller_func, int caller_line)
{
	if (actual != expected)
	{
		printf("%s failed: (\"%lu\") is not equal to expected (\"%lu\"). ",
			__func__, actual, expected);
		printf("func %s at file %s, line %d\n",
			caller_func, caller_file, caller_line);
	}
}

void	ASSERT_EQ_STR(char *actual, char *expected, size_t size,
	char *caller_file, const char *caller_func, int caller_line)
{
	if (strncmp(actual, expected, size) != 0)
	{
		printf("%s failed: (\"%s\") is not equal to expected (\"%s\"). ",
			__func__, actual, expected);
		printf("func %s at file %s, line %d\n",
			caller_func, caller_file, caller_line);
	}
}

const char	*g_base16 = "0123456789abcdef";

static void	hexdump(void *p, size_t size)
{
	unsigned char	*ptr;
	size_t			i;
	char			c;
	char			hex[2];

	ptr = (unsigned char *)p;
	i = 0;
	while (i < size)
	{
		c = *(ptr + i);
		printf("%c%c", g_base16[(c >> 4) & 0x0f], g_base16[c & 0x0f]);
		i++;
	}
}

void	ASSERT_EQ_MEM(void *actual, void *expected, size_t size,
	char *caller_file, const char *caller_func, int caller_line)
{
	if (memcmp(actual, expected, size) != 0)
	{
		printf("%s failed: (\"", __func__);
		hexdump(actual, size);
		printf("\") is not equal to expected (\"");
		hexdump(expected, size);
		printf("\"). ");
		printf("func %s at file %s, line %d\n",
			caller_func, caller_file, caller_line);
	}
}
