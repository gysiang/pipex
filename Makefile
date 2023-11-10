# Compiler flags
CC 		= gcc

CFLAGS 		= -Wall -Wextra -Werror

# Source files
SRC_FILES 	= src/pipex.c 		

# Object files
OBJ_FILES 	= $(SRC_FILES:.c=.o)

# Library name
NAME 		= pipex

# Targets
all:		$(NAME)
			
$(NAME):	make all -C libft
			gcc $(CLAGS) $(SRC_FILES) -o $(NAME);
						
clean:		
	rm -f $(NAME)
	make clean -C libft

fclean:		clean 
	rm -f $(name)
	make fclean -C libft

re:		fclean all

.PHONY:		all clean fclean re
