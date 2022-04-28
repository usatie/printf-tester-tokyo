/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susami <susami@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 18:17:52 by susami            #+#    #+#             */
/*   Updated: 2022/04/28 10:11:31 by susami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stdarg.h"
#include <unistd.h>
#include <limits.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "ft_printf.h"


#define BUF_SIZE 1024
#define FMT_WIDTH 50
#define F(...) ({\
	char buf[BUF_SIZE];\
	bzero(buf, BUF_SIZE);\
	strcpy(buf, "F(");\
	strcpy(buf + 2, #__VA_ARGS__);\
	strcpy(buf + 2 + strlen(#__VA_ARGS__), ")");\
	printf("%-*s: stdout=[", FMT_WIDTH, buf);\
    int ret = _F(__VA_ARGS__);\
	write(STDOUT_FILENO, "], ", 3);\
	printf("ret=[%i]", ret);\
	if (ret < 0)\
		printf(", \e[31merrno=[%i]\e[0m", errno);\
	printf("\n");\
	errno = 0;\
})
#ifdef FT_PRINTF
# define _F(...) ft_printf(__VA_ARGS__);
#else
# define _F(...) printf(__VA_ARGS__);
#endif


int	main(void)
{
	// No I/O buffering
	setvbuf(stdout, (char *)NULL, _IONBF, 0);

	// Basic Part Test cases
    F("hello world");
	F("%%");
	F("%%%%");
	F("%c", 'h');
	F("%s", "hello world");
	F("%s", "");
	F("%s", (char *)NULL);
	F("%c %c", 'h', 'e');
	F("%p", (void *)42);
	F("%p", (void *)19827492);
	F("%d", -42);
	F("%i", -42);
	F("%d", INT_MAX);
	F("%i", INT_MIN);
	F("%u", 42);
	F("%x", 42);
	F("%X", 42);
    F("%c %s", 'h', "hello world");
    F("%c %s %p %d %i %u %x %X", 'h', "hello world", (void *)42, -42, -42, 42, 42, 42);

	/* SLOW OVERFLOW tests
	size_t n = INT_MAX;
	n += 5;
	char *very_long_str;
	very_long_str = malloc(sizeof(char) * (n + 1));
	memset(very_long_str, 'a', n);
	very_long_str[n] = '\0';
	F("%s", very_long_str);
	// Warning because of non literal format
	// F(very_long_str);
	// Fails because of buffering
	F("hello world%s", very_long_str);

	// outputs too many string so don't run this line.
	//F("hello world%s", very_long_str + 10);
	*/

	// Bonus Part Test cases
	F("%20s", "hello world");
	F("%5s", "hello world");

	F("%20s", (char *)NULL);
	F("%5s", (char *)NULL);

	F("%-s", "hello world");
	//F("%0s", "hello world");
	F("%.s", "hello world");

	F("%-20s", "hello world");
	//F("%20-s", "hello world");
	//F("%020s", "hello world");
	F("%200s", "hello world");
	F("%.20s", "hello world");
	F("%20.s", "hello world");

	F("%-5s", "hello world");
	//F("%05s", "hello world");
	F("%.5s", "hello world");

	F("%20u", 42);
	F("%5u", 42);

	F("%-u", 42);
	F("%0u", 42);
	F("%.u", 42);

	F("%-20u", 42);
	F("%020u", 42);
	F("%.20u", 42);

	F("%-5u", 42);
	F("%05u", 42);
	F("%.5u", 42);

	F("%20%");
	F("%5%");

	F("%-%");
	F("%0%");
	F("%.%");

	F("%-5%");
	F("%05%");
	F("%.5%");

	F("%20i", -42);
	F("%5i", -42);

	F("%-i", -42);
	F("%0i", -42);
	F("%.i", -42);

	F("%-20i", -42);
	F("%020i", -42);
	F("%.20i", -42);

	F("%-5i", -42);
	F("%05i", -42);
	F("%.5i", -42);

	F(" % d ", 0);
	F(" % d ", -1);
	F(" % d ", 1);
	F(" % d ", 9);
	F(" % d ", 10);
	F(" % d ", 11);
	F(" % d ", 15);
	F(" % d ", 16);
	F(" % d ", 17);
	F(" % d ", 99);
	F(" % d ", 100);
	F(" % d ", 101);
	F(" % d ", -9);
	F(" % d ", -10);
	F(" % d ", -11);
	F(" % d ", -14);
	F(" % d ", -15);
	F(" % d ", -16);
	F(" % d ", -99);
	F(" % d ", -100);
	F(" % d ", -101);

	F(" %2p ", (void *)-1);
	F(" %-2p ", (void *)-1);
	F(" %-2p ", (void *)1);
	F(" %-2p ", (void *)15);
	F(" %-3p ", (void *)16);
	F(" %-4p ", (void *)17);
	F(" %-9p %-10p ", (void *)LONG_MIN, (void *)LONG_MAX);
	F(" %-11p %-12p ", (void *)INT_MIN, (void *)INT_MAX);
	F(" %-13p %-14p ", (void *)ULONG_MAX, (void *)-ULONG_MAX);
	F(" %-1p %-2p ", (void *)0, (void *)0);

	F(" %#x ", 0);
	F(" %#x ", -1);
	F(" %#x ", 1);
	F(" %#x ", 9);
	F(" %#x ", 10);
	F(" %#x ", 11);
	F(" %#x ", 15);
	F(" %#x ", 16);
	F(" %#x ", 17);
	F(" %#x ", 99);
	F(" %#x ", 100);
	F(" %#x ", 101);
	F(" %#x ", -9);
	F(" %#x ", -10);
	F(" %#x ", -11);
	F(" %#x ", -14);
	F(" %#x ", -15);
	F(" %#x ", -16);
	F(" %#x ", -99);
	F(" %#x ", -100);
	F(" %#x ", -101);
	F(" %#x ", INT_MAX);
	F(" %#x ", INT_MIN);
	//F(" %#x ", LONG_MAX);
	//F(" %#x ", LONG_MIN);
	F(" %#x ", UINT_MAX);
	//F(" %#x ", ULONG_MAX);
	//F(" %#x ", 9223372036854775807LL);
	//F(" %#x %#x %#x %#x %#x %#x %#x", INT_MAX, INT_MIN, LONG_MAX, LONG_MIN, ULONG_MAX, 0, -42);
	F(" %#x%#x ", INT_MAX, INT_MIN);

	F(" %#X ", 0);
	F(" %#X ", -1);
	F(" %#X ", 1);
	F(" %#X ", 9);
	F(" %#X ", 10);
	F(" %#X ", 11);
	F(" %#X ", 15);
	F(" %#X ", 16);
	F(" %#X ", 17);
	F(" %#X ", 99);
	F(" %#X ", 100);
	F(" %#X ", 101);
	F(" %#X ", -9);
	F(" %#X ", -10);
	F(" %#X ", -11);
	F(" %#X ", -14);
	F(" %#X ", -15);
	F(" %#X ", -16);
	F(" %#X ", -99);
	F(" %#X ", -100);
	F(" %#X ", -101);
	F(" %#X ", INT_MAX);
	F(" %#X ", INT_MIN);
	//F(" %#X ", LONG_MAX);
	//F(" %#X ", LONG_MIN);
	F(" %#X ", UINT_MAX);
	//F(" %#X ", ULONG_MAX);
	//F(" %#X ", 9223372036854775807LL);
	//F(" %#X %#X %#X %#X %#X %#X %#X", INT_MAX, INT_MIN, LONG_MAX, LONG_MIN, ULONG_MAX, 0, -42);
	F(" %#X%#X ", INT_MAX, INT_MIN);

	F("%#20.10x", 42);
	F("%#20.10x", -42);
	F("%#20.20x", 42);
	F("%#20.20x", -42);
	F("%#20.30x", 42);
	F("%#20.30x", -42);

	F("%.0i", 0);
	F("%.i", 0);
	F("%.20i", 0);
	F("%20.10i", 42);

	F("%.50i", 42);
	F("%.100i", 42);
	F("%30000000000000i", 42);
	F("%.30000000000000i", 42);
	F("%4294967284i", 42);
	F("%.4294967284i", 42);
	F("%4294967304i", 42);
	F("%.4294967304i", 42);

	F("%.50x", 42);
	F("%.100x", 42);
	F("%30000000000000x", 42);
	F("%.30000000000000x", 42);
	F("%4294967284x", 42);
	F("%.4294967284x", 42);
	F("%4294967304x", 42);
	F("%.4294967304x", 42);

	F("%#.50x", 42);
	F("%#.100x", 42);
	F("%#30000000000000x", 42);
	F("%#.30000000000000x", 42);
	F("%#4294967284x", 42);
	F("%#.4294967284x", 42);
	F("%#4294967304x", 42);
	F("%#.4294967304x", 42);

	F("%30000000000000s", "hello");
	F("%.30000000000000s", "hello");
	F("%4294967284s", "hello");
	F("%.4294967284s", "hello");
	F("%4294967304s", "hello");
	F("%.4294967304s", "hello");

	// Fail because of buffering
	// F("hello%.2147483647i", 42);
	//F(NULL);
	/*
	*/
	return (0);
}
