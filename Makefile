# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rbourgea <rbourgea@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/24 16:00:27 by rbourgea          #+#    #+#              #
#    Updated: 2022/06/02 12:31:33 by rbourgea         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# **************************************************************************** #
# 🎨 COLORS
# **************************************************************************** #

GREY    	=	\033[030m
RED     	=	\033[031m # Error or Clean
GREEN   	=	\033[032m # Done
YELLOW  	=	\033[033m # Info
BLUE    	=	\033[034m
MAGENTA 	=	\033[035m # Build or Loading
CYAN		=	\033[036m # End
BOLD		=	\033[1m
RESET   	=	\033[0m

# **************************************************************************** #
# 💾 VARIABLES
# **************************************************************************** #

NAME		=	ft_ping
CC		=	gcc
FLAGS		=	-Wall -Wextra -Werror -g

INC_PATH	=	inc/
SRC_PATH	=	src/
OBJ_PATH	=	obj/

INC_NAME	=	ft_ping.h
SRC_NAME	=	main.c \
			parsing.c \
			libft.c \
			utils.c \
			ping.c
OBJ_NAME	=	$(SRC_NAME:.c=.o)

INC		=	-I inc/
SRC		=	$(addprefix $(SRC_PATH), $(SRC_NAME))
OBJ		=	$(addprefix $(OBJ_PATH), $(OBJ_NAME))

# **************************************************************************** #
# 📖 RULES
# **************************************************************************** #

all: $(NAME)
	@echo "$(BOLD)$(CYAN)[✓] $(NAME) READY$(RESET)"

$(NAME): $(OBJ_PATH) $(OBJ)
	@echo -n ' DONE'
	@echo "$(RESET)\n$(BOLD)$(GREEN)[✓] GENERATE OBJS DONE$(RESET)"
	@$(CC) $(FLAGS) -o $(NAME) $(OBJ) $(INC)
	@echo "$(BOLD)$(GREEN)[✓] $(NAME) BUILD DONE$(RESET)"

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	@$(CC) $(FLAGS) $(INC) -o $@ -c $<
	@echo -n '#'

$(OBJ_PATH):
	@mkdir $(OBJ_PATH) 2> /dev/null || true
	@echo "$(BOLD)$(MAGENTA)"
	@clear
	@echo -n ' [☛] Building: '

clean:
	@clear
	@rm -rf $(OBJ_PATH)
	@echo "$(BOLD)$(RED)[♻︎] DELETE OBJS DONE$(RESET)"

fclean: clean
	@rm -rf $(NAME)
	@echo "$(BOLD)$(RED)[♻︎] DELETE BINARY FILE DONE$(RESET)"

re: fclean all

.PHONY: all clean fclean re