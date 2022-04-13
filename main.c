/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susami <susami@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 18:17:52 by susami            #+#    #+#             */
/*   Updated: 2022/04/13 19:08:27 by susami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "helpers.h"
#include "stdarg.h"
#include <limits.h>

//#ifdef FT_PRINTF
//# define F(...) 
//    printf("returned: %i\n", ft_printf(__VA_ARGS__));fflush(stdout);
//#else
//#define F(...)
//	    printf("returned: %i\n", printf(__VA_ARGS__))
//#endif
int	main(void)
{
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
	return (0);
}
