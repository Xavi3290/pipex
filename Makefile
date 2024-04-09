# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: xavi <xavi@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/04 12:29:05 by xroca-pe          #+#    #+#              #
#    Updated: 2024/04/09 13:45:20 by xavi             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex
CC = cc
CFLAGS = -Wall -Werror -Wextra
RM = rm -f
INCLUDE = pipex_bonus.h pipex.h Makefile

SRC = ft_substr.c \
	  ft_split.c \
	  ft_strjoin.c \
	  pipex.c \
	  utils.c 
	  
SRC_BONUS = ft_substr.c \
	  		ft_split.c \
	  		ft_strjoin.c \
			pipex_bonus.c \
			utils_bonus.c \
			get_next_line.c \
			get_next_line_utils.c

OBJ := $(SRC:.c=.o)

OBJ_BONUS := $(SRC_BONUS:.c=.o)

all: $(NAME)

$(NAME): $(OBJ) $(INCLUDE)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ)

%.o: %.c $(INCLUDE)
	$(CC) $(CFLAGS) -c -o $@ $<

bonus: $(OBJ_BONUS) $(INCLUDE)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ_BONUS)

clean:
	$(RM) $(OBJ) $(OBJ_BONUS)

fclean: clean
	$(RM) $(NAME) 

re: fclean all

.PHONY: all clean fclean re bonus