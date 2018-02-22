NAME = BlackJack
CC = gcc
CFLAGS = -W -Wall -Wextra
FILE = BlackJack_3.c main.c
OBJ = $(FILE:.c=.o)
INCLUDE = BlackJack_3.h

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) -o $(NAME) $(OBJ)

$(OBJ): $(FILE) $(INCLUDE)
	$(CC) -c $(FILE) $(CFLAGS)

clean:
	rm $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all
