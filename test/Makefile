# Name of the final executable
NAME = test

# Source file(s)
SRCS = main.c

# Object file(s)
OBJS = $(SRCS:.c=.o)

# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -Werror

# Linking options
LDFLAGS = -L.. -Wl,-rpath=.. -lft_malloc

# Rule to make the executable
all: $(NAME)

# Rule to create the object files and link them to create the executable
$(NAME): $(OBJS)
	# compile with the library
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LDFLAGS)

# Rule to compile the object files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@ -I ../inc

# Clean up object files
clean:
	rm -f $(OBJS)

# Clean up object files and executable
fclean: clean
	rm -f $(NAME)

# Recompile everything
re: fclean all
