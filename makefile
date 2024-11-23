NAME    = philo
CC      = cc
CFLAGS  = -Wall -Werror -Wextra -g3 -fsanitize=address

SRCS    = philo.c utils/ft_strdup.c utils/ft_atoi.c \
			utils/ft_isdigit.c free.c init.c time.c \
			fork.c process.c
		
OBJ     = $(SRCS:.c=.o)

PRINTF  = ft_printf_copy/libftprintf.a

%.o : %.c
	$(CC) -c $(CFLAGS) $< -o $@

all: $(NAME)

$(PRINTF):
	make -C ft_printf_copy

$(NAME): $(OBJ) $(PRINTF)
	$(CC) $(CFLAGS) $(OBJ) -o $@ $(PRINTF)

clean: 
	make -C ft_printf_copy clean
	rm -f $(OBJ)

fclean: clean
	make -C ft_printf_copy fclean
	rm -f $(NAME)

re: fclean all

.PHONY : all clean fclean re