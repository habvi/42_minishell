NAME		:= a.out

CC			:= cc
CFLAGS		:= -Wall -Wextra -Werror

ifdef SANI
	CFLAGS	+= -g -fsanitize=address
endif

SRCS		= main.c \
			  tokenizer.c \
			  parser.c \
			  print.c \
			  tree.c \
			  calculator.c

OBJ_DIR		:= obj
OBJ			:= $(SRCS:%.c=%.o)
OBJS		:= $(addprefix $(OBJ_DIR)/, $(OBJ))

LIBFT_DIR	:= ../../../libft
LIBFT		:= $(LIBFT_DIR)/libft.a

.PHONY	:= all
all	:	$(NAME)

$(NAME)	: $(OBJS)
	@make -C $(LIBFT_DIR)
	$(CC) $(CFLAGS) -o $@ $^ $(LIBFT)

$(OBJ_DIR)/%.o	: %.c
	@mkdir -p $$(dirname $@)
	$(CC) $(CFLAGS) -o $@ $< -c

.PHONY	:= clean
clean	:
	@#make clean -C $(LIBFT_DIR)
	rm -rf $(OBJ_DIR)

.PHONY	:= fclean
fclean	: clean
	@#make fclean -C $(LIBFT_DIR)
	$(RM) $(NAME)

.PHONY	:= re
re	: fclean all

.PHONY	:= run
run	: re
	./$(NAME)

.PHONY	:= t1
t1	: re
	./$(NAME) "1 + 2"

.PHONY	:= t2
t2	: re
	./$(NAME) "1 * 2 + 3"

.PHONY	:= t3
t3	: re
	./$(NAME) "1 + 2 * 3"

.PHONY	:= t4
t4	: re
	./$(NAME) "1 * 2 + 3 * 4 * 5"

.PHONY	:= t5
t5	: re
	./$(NAME) "1 * 2"

.PHONY	:= t6
t6	: re
	./$(NAME) "1 * ( 2 + 3 )"

.PHONY	:= t7
t7	: re
	./$(NAME) "1 * 2 + 3 * 4 + 5 + 6 - 7 * 8"


.PHONY	:= print_tree
print_tree	: re
	@echo "[1] 1 + 2"
	@./$(NAME) "1 + 2" 1>/dev/null
	@echo ""
	@echo "[2] 1 * 2 + 3"
	@./$(NAME) "1 * 2 + 3" 1>/dev/null
	@echo ""
	@echo "[3] 1 + 2 * 3"
	@./$(NAME) "1 + 2 * 3" 1>/dev/null
	@echo ""
	@echo "[4] 1 * 2 + 3 * 4 * 5"
	@./$(NAME) "1 * 2 + 3 * 4 * 5" 1>/dev/null
	@echo ""
	@echo "[5] 1 * 2"
	@./$(NAME) "1 * 2" 1>/dev/null
	@echo ""
	@echo "[6] 1 * ( 2 + 3 )"
	@./$(NAME) "1 * ( 2 + 3 )" 1>/dev/null
	@echo ""
	@echo "[7] 1 * 2 + 3 * 4 + 5 + 6 - 7 * 8"
	@./$(NAME) "1 * 2 + 3 * 4 + 5 + 6 - 7 * 8" 1>/dev/null

.PHONY	:= test
test	: re
	./test.sh 2>/dev/null

.PHONY	:= test_with_stdout
test_with_stdout	: re
	./test.sh

