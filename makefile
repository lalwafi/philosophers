NAME    = philosophers
CC      = cc
CFLAGS  = -Wall -Werror -Wextra -g3 -fsanitize=address

# LIBFTLYALL = libft_lyall/libft.a

SRCS    = philo.c utils/ft_strdup.c utils/ft_atoi.c utils/ft_isdigit.c

OBJ     = $(SRCS:.c=.o)

%.o : %.c
	$(CC) -c $(CFLAGS) $< -o $@

all: $(NAME)

# $(LIBFTLYALL):
# 	make -C libft_lyall

$(NAME): $(OBJ) #$(LIBFTLYALL)
	$(CC) $(CFLAGS) $(OBJ) -o $@

clean: 
	rm -f $(OBJ)
#	make -C libft_lyall clean

fclean: clean
	rm -f $(NAME)
#	make -C libft_lyall fclean

re: fclean all

.PHONY : all clean fclean re