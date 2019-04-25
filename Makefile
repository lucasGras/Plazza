##
## EPITECH PROJECT, 2017
## Makefile
## File description:
## Made by developers
##

NAME_PLAZZA		=	plazza

NAME_KITCHEN	=	kitchen

all:
	mkdir -p build
	cd build && cmake .. && cd -
	make -C build && cp build/$(NAME_PLAZZA) . && cp build/$(NAME_KITCHEN) .


$(NAME_PLAZZA):
	mkdir -p build
	cd build && cmake .. && cd -
	make -C build $(NAME_PLAZZA) && cp build/$(NAME_PLAZZA) .

$(NAME_KITCHEN):
	mkdir -p build
	cd build && cmake .. && cd -
	make -C build $(NAME_KITCHEN) && cp build/$(NAME_KITCHEN) .

tests_run:
	mkdir -p build
	cd build && cmake .. && cd -
	make -C build Tests && cp build/Tests ./units && ./units

clean:
	rm -rf build/*

fclean: clean
	rm -f $(NAME_PLAZZA)
	rm -f $(NAME_KITCHEN)

re: fclean all

.PHONY: all clean fclean re $(NAME_PLAZZA)) $(NAME_KITCHEN)
