#--------------------------------------------
# ft_ascii
#--------------------------------------------
ASCII_DIR	:=	ft_ascii
ASCII_SRC	:=	$(ASCII_DIR)/ft_isalnum.c \
				$(ASCII_DIR)/ft_isalpha.c \
				$(ASCII_DIR)/ft_isascii.c \
				$(ASCII_DIR)/ft_isdigit.c \
				$(ASCII_DIR)/ft_isprint.c \
				$(ASCII_DIR)/ft_tolower.c \
				$(ASCII_DIR)/ft_toupper.c

#--------------------------------------------
# ft_lib
#--------------------------------------------
LIB_DIR		:=	ft_lib
LIB_SRC		:=	$(LIB_DIR)/ft_atoi_old.c \
				$(LIB_DIR)/ft_atoi_strictly.c \
				$(LIB_DIR)/ft_atoi.c \
				$(LIB_DIR)/ft_itoa_int.c \
				$(LIB_DIR)/ft_itoa.c

#--------------------------------------------
# ft_list
#--------------------------------------------
LIST_DIR	:=	ft_list
LIST_SRC	:=	$(LIST_DIR)/ft_lstadd_back.c \
				$(LIST_DIR)/ft_lstadd_front.c \
				$(LIST_DIR)/ft_lstclear.c \
				$(LIST_DIR)/ft_lstdelone.c \
				$(LIST_DIR)/ft_lstiter.c \
				$(LIST_DIR)/ft_lstlast.c \
				$(LIST_DIR)/ft_lstmap.c \
				$(LIST_DIR)/ft_lstnew.c \
				$(LIST_DIR)/ft_lstsize.c

#--------------------------------------------
# ft_math
#--------------------------------------------
MATH_DIR	:=	ft_math
MATH_SRC	:=	$(MATH_DIR)/ft_max.c \
				$(MATH_DIR)/ft_min.c

#--------------------------------------------
# ft_mem
#--------------------------------------------
MEM_DIR		:=	ft_mem
MEM_SRC		:=	$(MEM_DIR)/ft_bzero.c \
				$(MEM_DIR)/ft_calloc.c \
				$(MEM_DIR)/ft_memchr.c \
				$(MEM_DIR)/ft_memcmp.c \
				$(MEM_DIR)/ft_memcpy.c \
				$(MEM_DIR)/ft_memmove.c \
				$(MEM_DIR)/ft_memset.c

#--------------------------------------------
# ft_put
#--------------------------------------------
PUT_DIR		:=	ft_put
PUT_SRC		:=	$(PUT_DIR)/ft_putchar_fd.c \
				$(PUT_DIR)/ft_putendl_fd.c \
				$(PUT_DIR)/ft_putnbr_fd.c \
				$(PUT_DIR)/ft_putstr_fd.c

#--------------------------------------------
# ft_string
#--------------------------------------------
STRING_DIR	:=	ft_string
STRING_SRC	:=	$(STRING_DIR)/ft_free.c \
				$(STRING_DIR)/ft_split.c \
				$(STRING_DIR)/ft_strchr.c \
				$(STRING_DIR)/ft_strdup.c \
				$(STRING_DIR)/ft_striteri.c \
				$(STRING_DIR)/ft_strjoin.c \
				$(STRING_DIR)/ft_strlcat.c \
				$(STRING_DIR)/ft_strlcpy_void.c \
				$(STRING_DIR)/ft_strlcpy.c \
				$(STRING_DIR)/ft_strlen.c \
				$(STRING_DIR)/ft_strmapi.c \
				$(STRING_DIR)/ft_strncmp.c \
				$(STRING_DIR)/ft_strndup.c \
				$(STRING_DIR)/ft_strnlen.c \
				$(STRING_DIR)/ft_strnstr.c \
				$(STRING_DIR)/ft_strrchr.c \
				$(STRING_DIR)/ft_strtrim.c \
				$(STRING_DIR)/ft_substr.c

#--------------------------------------------
NAME		:=	libft.a

SRC_DIR		:=	src
OBJ_DIR		:=	obj
OBJS		:=	$(ASCII_SRC:%.c=$(OBJ_DIR)/%.o) \
				$(LIB_SRC:%.c=$(OBJ_DIR)/%.o) \
				$(LIST_SRC:%.c=$(OBJ_DIR)/%.o) \
				$(MATH_SRC:%.c=$(OBJ_DIR)/%.o) \
				$(MEM_SRC:%.c=$(OBJ_DIR)/%.o) \
				$(PUT_SRC:%.c=$(OBJ_DIR)/%.o) \
				$(STRING_SRC:%.c=$(OBJ_DIR)/%.o)

#--------------------------------------------
INCLUDE_DIR	:=	includes
INCLUDES	:=	-I$(INCLUDE_DIR)/

DEPS		:=	$(OBJS:.o=.d)

#--------------------------------------------
CC			:=	cc
CFLAGS		:=	-Wall -Wextra -Werror -MMD -MP
ARFLAGS		:=	rcs
MKDIR		:=	mkdir -p

# ifeq ($(MAKECMDGOALS), gcc)
# 	CC	:=	gcc
# endif

# ifeq ($(MAKECMDGOALS), clang)
# 	CC	:=	clang
# endif

#--------------------------------------------
all: $(NAME)

-include $(DEPS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@$(MKDIR) $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(NAME): $(OBJS)
	$(AR) $(ARFLAGS) $(NAME) $(OBJS)

clean:
	$(RM) -r $(OBJ_DIR)

fclean: clean
	$(RM) $(NAME)

re: fclean all

#--------------------------------------------
info:
	$(info >>> default goal : $(.DEFAULT_GOAL))
	$(info >>> obj : $(OBJS))

.PHONY: all clean fclean re info


# gcc: re
# .PHONY: gcc

# clang: re
# .PHONY: clang
