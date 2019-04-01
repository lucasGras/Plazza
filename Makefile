##
## EPITECH PROJECT, 2017
## Makefile
## File description:
## Made by developers
##

NAME	=	plazza

all: $(NAME)

$(NAME):
	mkdir -p build
	cd build && cmake .. && cd -
	make -C build && cp build/$(NAME) .

clean:
	rm -rf build/*

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re $(NAME)
