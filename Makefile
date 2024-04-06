NAME = pipex
CC = cc
CFLAGS = -Wall -Werror -Wextra
RM = rm -f
INCLUDE = pipex.h Makefile

SRC = ft_substr.c \
	  ft_split.c \
	  ft_strjoin.c \
	  pipex.c \
	  utils.c 
	  
SRC_BONUS = 

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