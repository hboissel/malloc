ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

NAME = libft_malloc_$(HOSTTYPE).so
LIB_NAME = libft_malloc.so

DBG		=	$(DBG_DIR)/$(NAME)

SRC_DIR =	src

BIN_DIR =	obj

DBG_DIR =	dbg

SRC = $(SRC_DIR)/free.c\
	  $(SRC_DIR)/realloc.c\
	  $(SRC_DIR)/calloc.c\
	  $(SRC_DIR)/show_alloc_mem.c\
	  $(SRC_DIR)/malloc.c

OBJ = $(SRC:$(SRC_DIR)/%.c=$(BIN_DIR)/%.o)

DBG_OBJ = $(SRC:$(SRC_DIR)/%.c=$(DBG_DIR)/%.o)

DEPS = $(SRC:$(SRC_DIR)/%.c=$(BIN_DIR)/%.d)

DBG_DEPS = $(SRC:$(SRC_DIR)/%.c=$(DBG_DIR)/%.d)

LIBFT_PATH = ./libft

LIBFT = -L$(LIBFT_PATH) -lft

LIBFT_MALLOC = -L. -lft_malloc

INCLUDES = ./inc

CFLAGS = -Werror -Wextra -Wall -I$(INCLUDES) -I$(LIBFT_PATH) -fPIC

LFLAGS = -shared

all :	$(NAME)

debug	:	$(DBG)

$(BIN_DIR) $(DBG_DIR):
	@ mkdir -p $@

$(DBG_OBJ) : $(DBG_DIR)/%.o: $(SRC_DIR)/%.c | $(DBG_DIR)
	@ $(CC) $(CFLAGS) -g3 -MMD -c $< -o $@

$(OBJ) : $(BIN_DIR)/%.o: $(SRC_DIR)/%.c | $(BIN_DIR)
	@ $(CC) $(CFLAGS) -MMD -c $< -o $@

$(DBG) : $(DBG_OBJ)
	@ $(MAKE) -sC $(LIBFT_PATH)
	@ $(CC) $(CFLAGS) $(LFLAGS) -g3 $(DBG_OBJ) $(LIBFT) -o $(DBG)
	@ln -sf $(DBG) $(DBG_DIR)/$(LIB_NAME)
	@ echo "\e[33m\e[1m\tMake\e[0m [🗿] : \e[1mDone ! ✅"

$(NAME) : $(OBJ)
	@ $(MAKE) -sC $(LIBFT_PATH)
	@ $(CC) $(CFLAGS) $(LFLAGS) $(OBJ) $(LIBFT) -o $(NAME)
	@ln -sf $(NAME) $(LIB_NAME)
	@ echo "\e[33m\e[1m\tMake\e[0m [🗿] : \e[1mDone ! ✅"

test: $(NAME)
	@ $(MAKE) -sC test
	@ cd test && ./test_malloc

clean :
	@ $(MAKE) -sC $(LIBFT_PATH) clean
	@ $(MAKE) -sC test clean
	@ rm -f $(OBJ)
	@ rm -f $(OBJ:.o=.d)
	@ rm -rf $(BIN_DIR) $(DBG_DIR)
	@echo "\e[33m\e[1m\tMake\e[0m [🗿] : \e[1mRemove binary files .. 🧹"

fclean : clean
	@ $(MAKE) -sC $(LIBFT_PATH) fclean
	@ $(MAKE) -sC test fclean
	@ rm -f $(NAME)
	@ rm -f $(LIB_NAME)
	@ echo "\e[33m\e[1m\tMake\e[0m [🗿] : \e[1mRemove executable .. 🗑️"

re : fclean all

-include	${DEPS} ${DBG_DEPS}

.PHONY: all clean fclean re debug test
