CC=gcc


all:
	 $(CC) main.c libassert.c
	 ./a.out >printf.log
	 rm a.out
	 $(CC) main.c libassert.c -D FT_PRINTF
	 ./a.out >ft_printf.log
	 rm a.out
	 diff -U 3 ft_printf.log printf.log
	 @echo "diff OK :D"
