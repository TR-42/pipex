# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kfujita <kfujita@student.42tokyo.jp>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/26 22:05:10 by kfujita           #+#    #+#              #
#    Updated: 2023/01/30 14:02:11 by kfujita          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	pipex

SRC_DIR	=	./srcs
SRC_MAIN = main.c

SRCS_NOMAIN	=\
	env_util.c \
	parse_cmd.c \
	print_error.c \

SRCS	=\
	$(SRC_MAIN)\
	$(SRCS_NOMAIN)

SRCS_BONUS	=\

OBJ_DIR	=	./obj
OBJS	=	$(addprefix $(OBJ_DIR)/, $(SRCS:.c=.o))
OBJS_NOMAIN	=	$(addprefix $(OBJ_DIR)/, $(SRCS_NOMAIN:.c=.o))
OBJS_BONUS	=	$(addprefix $(OBJ_DIR)/, $(SRCS_BONUS:.c=.o))

LIBFT_DIR	=	./libft
LIBFT	=	$(LIBFT_DIR)/libft.a
LIBFT_MAKE	=	make -C $(LIBFT_DIR)

CFLAGS	=	-Wall -Wextra -Werror
INCLUDES	=	-I $(LIBFT_DIR) -I ./headers

CC		=	cc

all:	MAKE_BEFORE $(NAME)

ifdef WITH_BONUS
$(NAME):	$(LIBFT) $(OBJS_BONUS)
else
$(NAME):	$(LIBFT) $(OBJS)
endif
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ $^

MAKE_BEFORE:
ifdef WITH_BONUS
	@if [ -f "$(NAME)" ] && [ "`nm $(NAME) | grep _bonus`" = "" ]; then rm -f $(NAME) ; fi;
else
	@if [ -f "$(NAME)" ] && [ "`nm $(NAME) | grep _bonus`" != "" ]; then rm -f $(NAME) ; fi;
endif

$(OBJ_DIR)/%.o:	$(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c -o $@ $^

$(LIBFT):
	$(LIBFT_MAKE)

bonus:
	make WITH_BONUS=1

test_parse_cmd:	$(LIBFT) $(OBJS_NOMAIN) ./.tests/parse_cmd.c
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ $^

clean:
	$(LIBFT_MAKE) clean
	rm -f $(OBJS) $(OBJS_BONUS)
	rm -d $(OBJ_DIR) || exit 0

fclean:	clean
	$(LIBFT_MAKE) fclean
	rm -f $(NAME)

re:	fclean all

.PHONY:	clean MAKE_BEFORE bonus
