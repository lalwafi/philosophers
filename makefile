NAME    = philosophers
CC      = cc
CFLAGS  = -Wall -Werror -Wextra -g3 -fsanitize=address

SRCS    = philo.c utils/ft_strdup.c utils/ft_atoi.c utils/ft_isdigit.c

OBJ     = $(SRCS:.c=.o)

%.o : %.c
	$(CC) -c $(CFLAGS) $< -o $@

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $@

clean: 
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY : all clean fclean re