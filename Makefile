FT_PRINTFDIR = ..
FT_PRINTF = $(FT_PRINTFDIR)/libftprintf.a

CC		=	gcc
CFLAGS	=	-I $(FT_PRINTFDIR)/include

SRCS	=	main.c
OBJS	=	$(SRCS:%.c=%.o)

test:
	@printf -- \
		"---------------------------------------Run the tests with standard printf...---------------------------------------\n"
	$(CC) $(SRCS) $(FT_PRINTF) $(CFLAGS)
	./a.out >printf.log
	@rm a.out
	@printf -- \
		"\n\n---------------------------------------Run the tests with your ft_printf...---------------------------------------\n"
	$(CC) $(SRCS) $(FT_PRINTF) $(CFLAGS) -D FT_PRINTF
	./a.out >ft_printf.log
	@rm a.out
	@printf -- \
		"\n\n---------------------------Compare the results by standard printf and your ft_printf...---------------------------\n"
	@diff -U 0 ft_printf.log printf.log && \
		printf -- \
		"\e[32m\n\n------------------------------------------------------------------------------------------------------------------\
		\nAll tests passed successfully! Congratulations :D\n\e[m" ||\
		printf -- \
		"\e[31m\n\n------------------------------------------------------------------------------------------------------------------\
		\nSome tests failed. Please see ft_printf.log and printf.log for more detailed information.\n\e[m"
