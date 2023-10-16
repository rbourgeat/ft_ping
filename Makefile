# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rbourgea <rbourgea@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/24 16:00:27 by rbourgea          #+#    #+#              #
#    Updated: 2023/10/16 17:34:44 by rbourgea         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# **************************************************************************** #
# 🎨 COLORS
# **************************************************************************** #

GREY    	=	\033[030m
RED     	=	\033[031m
GREEN   	=	\033[032m
YELLOW  	=	\033[033m
BLUE    	=	\033[034m
MAGENTA 	=	\033[035m
CYAN		=	\033[036m
BOLD		=	\033[1m
RESET   	=	\033[0m

# **************************************************************************** #
# 💾 VARIABLES
# **************************************************************************** #

NAME		=	ft_ping
CC		=	gcc

INC_FILES	=	ft_ping.h

SRC_FILES	=	main.c \
			parse.c

INC_DIR		=	inc
SRC_DIR		=	src
OBJ_DIR		=	obj

INC		=	$(addprefix $(INC_DIR)/, $(INC_FILES))
SRC		=	$(addprefix $(SRC_DIR)/, $(SRC_FILES))
OBJ		=	$(addprefix $(OBJ_DIR)/, $(SRC_FILES:.c=.o))

DEPENDS		=	$(INC) Makefile

CFLAGS		=	-Wall -Werror -Wextra # -g3 -ggdb -fsanitize=address

# **************************************************************************** #
# 📖 RULES
# **************************************************************************** #

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(CFLAGS) $(IFLAGS) -c $< -o $@

all:	$(NAME)

$(NAME)	: $(DEPENDS) $(OBJ)
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJ)
	@echo "$(BOLD)$(GREEN)[✓] $(NAME) BUILD DONE$(RESET)"

clean:
	@rm -rf $(OBJ_DIR)
	@echo "$(BOLD)$(RED)[♻︎] DELETE $(OBJ_DIR)/ DONE$(RESET)"

fclean: clean
	@rm -rf $(NAME)
	@echo "$(BOLD)$(RED)[♻︎] DELETE $(NAME) DONE$(RESET)"

re: fclean all

.PHONY: all clean fclean re