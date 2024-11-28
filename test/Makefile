NAME = test_malloc

SRCS = main.c

OBJS = $(SRCS:.c=.o)

CFLAGS = -Wall -Wextra -Werror

LDFLAGS = -L.. -Wl,-rpath=.. -lft_malloc

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@ -I ../inc

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all clean
