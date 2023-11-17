# Compiler flags
CC 		= gcc

CFLAGS 		= -Wall -Wextra -Werror

# Source files
SRC_FILES 	= pipex.c 		

# Object files
OBJ_FILES 	= $(SRC_FILES:.c=.o)

# Library name
NAME 		= pipex

# Targets
all:		$(NAME)
				
$(NAME):	ft_printf $(OBJ_FILES);
		@echo "Building $(NAME)"
		$(CC) $(CFLAGS) -o $(NAME) $(OBJ_FILES) -L./ft_printf -lftprintf
		
ft_printf: 
		@echo "Building ft_printf and libft"
		@cd ft_printf && make -C ./ft_printf
						
clean:		
	rm -f $(NAME)
	make clean -C ./ft_printf

fclean:		clean 
	rm -f $(MAKE)
	make fclean -C ./ft_printf

re:		fclean all

.PHONY:		all clean fclean re


