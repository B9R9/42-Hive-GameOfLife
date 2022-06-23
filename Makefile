# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: briffard <briffard@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/01 15:35:11 by mde-maul          #+#    #+#              #
#    Updated: 2022/06/23 11:11:34 by briffard         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME_REF	=	life
NAME_OPT	= 	life2.0

#COMPILATION
CC		=	gcc
CCFLAGS	=	-Werror -Wextra -Wall

#INCLUDE
INCL_LFT	= -I ./libft/includes/
INCL_GOL	= -I ./includes/ 

#LIBRAIRIE
LIB		= -L ./libft/ -lft

#CLEAN & FCLEAN
RM_DIR	=	rm -rf
RM		=	rm	-f

#SOURCE FILES
SRC_DIR	=	./srcs/
FILES	= 	rushes_main.c
		
#SOURCE OPT FILES
SRC_DIR_OPT	=	./srcs_opt/
FILES_OPT	= 	rushes_main_opt.c

#OBJECT FILES
OBJ_DIR			=	./objectFiles/
OBJS			=	$(addprefix $(OBJ_DIR), $(FILES:%.c=%.o))

#OBJECT FILES OPT
OBJ_DIR_OPT			=	./objectFiles_opt/
OBJS_OPT			=	$(addprefix $(OBJ_DIR_OPT), $(FILES_OPT:%.c=%.o))

all: $(NAME_REF) $(NAME_OPT) $(LIBFT)

$(NAME_OPT): $(OBJS_OPT)
	@$(CC) $(CCFLAGS) -o $(NAME_OPT) $(OBJS_OPT) $(LIB)

$(OBJ_DIR_OPT)%.o:$(SRC_DIR_OPT)%.c
	@mkdir -p $(OBJ_DIR_OPT)
	@$(CC) $(CCFLAGS) $(INCL_LFT) $(INCL_GOL) -o $@ -c $<

$(NAME_REF): $(OBJS)
	@$(CC) $(CCFLAGS) -o $(NAME_REF) $(OBJS) $(LIB)
	
$(OBJ_DIR)%.o:$(SRC_DIR)%.c
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(CCFLAGS) $(INCL_LFT) $(INCL_GOL) -o $@ -c $<

$(LIBFT):
	@make -sC ./libft/ all
lft:
	@make -sC ./libft/ all

lft_reboot:
	@make -sC ./libft/ re

lft_clean:
	@make -sC ./libft/ clean

lft_fclean:
	@make -sC ./libft/ fclean

clean:
	@$(RM_DIR) $(OBJ_DIR)
	@$(RM_DIR) $(OBJ_DIR_OPT)
	@echo "Object Files have been deleted"

fclean: clean
	@$(RM) $(NAME_REF)
	@$(RM) $(NAME_OPT)
	@echo "Life file has been deleted"

re: fclean all

.PHONY: all re clean fclean
