NAME		:= a.out

CC			:= cc
CFLAGS		:= -Wall -Wextra -Werror

ifdef SANI
	CFLAGS	+= -g -fsanitized=address
endif

SRCS		= main.c \
			  tokenizer.c \
			  parser.c

OBJ_DIR		:= obj
OBJ			:= $(SRCS:%.c=%.o)
OBJS		:= $(addprefix $(OBJ_DIR)/, $(OBJ))

LIBFT_DIR	:= ../../../libft
LIBFT		:= $(LIBFT_DIR)/libft.a

.PHONY	:= all
all	:	$(NAME)

$(NAME)	: $(OBJS)
	@make -C $(LIBFT_DIR)
	$(CC) $(CFLAGS) -o $@ $(LIBFT) $^

$(OBJ_DIR)/%.o	: %.c
	@mkdir -p $$(dirname $@)
	$(CC) $(CFLAGS) -o $@ $< -c

.PHONY	:= clean
clean	:
	rm -rf $(OBJ_DIR)

.PHONY	:= fclean
fclean	: clean
	$(RM) $(NAME)

.PHONY	:= re
re	: fclean
	@make all

.PHONY	:= run
run	: re
	./$(NAME)

t1	: re
	./$(NAME) "1 + 2"

t2	: re
	./$(NAME) "1 * 2 + 3"

t3	: re
	./$(NAME) "1 + 2 * 3"

t4	: re
	./$(NAME) "1 * 2 + 3 * 4 * 5"

t5	: re
	./$(NAME) "1 * 2"

t6	: re
	./$(NAME) "1 * ( 2 + 3 )"

t7	: re
	./$(NAME) "1 * 2 + 3 * 4 + 5 + 6 - 7 * 8"