CC		=	gcc
CFLAGS	=	-Wall -Werror -Wextra

LIBFTDIR = ../libft
LIBFT = $(LIBFTDIR)/libft.a
SRCS	=	ft_printf.c
OBJS	=	$(SRCS:%.c=%.o)

all: $(OBJS)
	gcc ft_printf.c -c
	ar -rc libftprintf.a ft_printf.o

test:
	@printf -- \
		"---------------------------------------Run the tests with standard printf...---------------------------------------\n"
	$(CC) main.c ft_printf.c $(LIBFT) -I $(LIBFTDIR)
	./a.out >printf.log
	@rm a.out
	@printf -- \
		"\n\n---------------------------------------Run the tests with your ft_printf...---------------------------------------\n"
	$(CC) main.c ft_printf.c $(LIBFT) -I $(LIBFTDIR) -D FT_PRINTF
	./a.out >ft_printf.log
	@rm a.out
	@printf -- \
		"\n\n---------------------------Compare the results by standard printf and your ft_printf...---------------------------\n"
	@diff -U 3 ft_printf.log printf.log && \
		printf -- \
		"\e[32m\n\n------------------------------------------------------------------------------------------------------------------\
		\nAll tests passed successfully! Congratulations :D\n\e[m" ||\
		printf -- \
		"\e[31m\n\n------------------------------------------------------------------------------------------------------------------\
		\nSome tests failed. Please see ft_printf.log and printf.log for more detailed information.\n\e[m"
