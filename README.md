# printf-tester

## How to test your ft_printf
1. Clone tester to your ft_printf directory
```
$ cd /path/to/your/ft_printf
$ git clone https://github.com/usatie/printf-tester-tokyo.git
```

2. Run the tester
```
$ make test -C printf-tester-tokyo
```
or
```
$ cd printf-tester-tokyo
$ make test
```

## If your printf is included in libft.a
1. Clone tester to your libft directory
```
$ cd /path/to/your/libft
$ git clone https://github.com/usatie/printf-tester-tokyo.git
```

2. Run the tester
```
$ make test -C printf-tester-tokyo FT_PRINTF=../libft.a
```
or
```
$ cd printf-tester-tokyo
$ make test FT_PRINTF=../libft.a
```
