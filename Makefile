# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rkirszba <rkirszba@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/11/18 20:33:55 by rkirszba          #+#    #+#              #
#    Updated: 2020/11/19 15:10:02 by rkirszba         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= libASM.a
TESTOR		= lib_testor.out

CC			= gcc
AR			= ar -rcs
NS			= nasm -fmacho64

CFLAGS		= -Wall -Werror -Wextra

#For developping purposes:
# CFLAGS 		+= -fsanitize=address,undefined -g3
CFLAGS 		+= -g

SRCS_DIR	= srcs/
SRCS_NAMES	= ft_strlen.s\
			  ft_strcpy.s\
			  ft_strcmp.s

OBJS_DIR	= objs/

$(shell mkdir -p $(OBJS_DIR))
SRCS		= $(addprefix $(SRCS_DIR)/,$(SRCS_NAMES))
OBJS		= $(SRCS:$(SRCS_DIR)%.s=$(OBJS_DIR)%.o)


all: $(NAME)

$(NAME): $(OBJS)
	$(AR) $(NAME) $(OBJS)

$(OBJS_DIR)%.o: $(SRCS_DIR)%.s Makefile
	$(NS) $< -o $@

test: $(NAME) main.c
	$(CC) $(CFLAGS) main.c $(OBJS) -o $(TESTOR) -L. -lASM
	@ ./$(TESTOR)

clean:
	rm -rf $(OBJS)
	rm -rf $(OBJS_DIR)
	rm -rf $(EXEM)

fclean: clean
	rm -rf $(NAME) $(TESTOR)

re : fclean
	$(MAKE) all

.PHONY: clean fclean
