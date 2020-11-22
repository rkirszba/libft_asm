# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rkirszba <rkirszba@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/11/18 20:33:55 by rkirszba          #+#    #+#              #
#    Updated: 2020/11/21 19:50:23 by rkirszba         ###   ########.fr        #
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

EXT	= .s

SRCS_DIR	= srcs/
SRCS_NAMES	= ft_strlen.s\
			  ft_strcpy.s\
			  ft_strcmp.s\
			  ft_write.s\
			  ft_read.s\
			  ft_strdup.s\
			  ft_atoi_base.s\
			  ft_check_dup.s\
			  ft_get_index.s\
			  ft_create_elem.s\
			  ft_list_push_front.s\
			  ft_list_size.s\
			  ft_list_sort.s

#BONUS_EXT			= _bonus
#BONUS_SRCS_DIR		= srcs_bonus
#BONUS_SRCS_NAMES	= ft_atoi_base


OBJS_DIR		= objs/
#BONUS_OBJS_DIR	= objs_bonus

$(shell mkdir -p $(OBJS_DIR))
#$(shell mkdir -p $(OBJS_BONUS_DIR))
SRCS		= $(addprefix $(SRCS_DIR),$(SRCS_NAMES))
OBJS		= $(SRCS:$(SRCS_DIR)%.s=$(OBJS_DIR)%.o)

#BONUS_SRCS	= $(addprefix $(BONUS_RCS_DIR)/,$(BONUS_SRCS_NAMES)$(BONUS_EXT)$(EXT))
#BONUS_OBJS	= $(BONUS_SRCS:$(BONUS_SRCS_DIR)%$(EXT)=$(BONUS_OBJS_DIR)%.o)


all: $(NAME)

$(NAME): $(OBJS)
	$(AR) $(NAME) $(OBJS)

$(OBJS_DIR)%.o: $(SRCS_DIR)%.s Makefile
	$(NS) $< -o $@

#bonus: $(OBJS) $(BONUS_OBJS)
#	$(AR) $(NAME) $(OBJS) $(BONUS_OBJS)

#$(BONUS_OBJS_DIR)%.o: $(BONUS_SRCS_DIR)%$(EXT) Makefile
#	$(NS) $< -o $@

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
