#  |  |  ___ \    \  |         |
#  |  |     ) |  |\/ |   _  |  |  /   _ 
# ___ __|  __/   |   |  (   |    <    __/ 
#    _|  _____| _|  _| \__,_| _|\_\ \___|
#                              by jcluzet
################################################################################
#                                     CONFIG                                   #
################################################################################

NAME        := pipex
CC        := gcc
FLAGS    := -Wall -Wextra -Werror 
################################################################################
#                                 PROGRAM'S SRCS                               #
################################################################################

SRCS        :=      ft_printf/ft_int_putchar_fd.c \
                          ft_printf/ft_int_putnbr_fd.c \
                          ft_printf/ft_int_putstr_fd.c \
                          ft_printf/ft_intohex.c \
                          ft_printf/ft_numlen.c \
                          ft_printf/ft_printf.c \
                          ft_printf/ft_putnbr_unsigned.c \
                          ft_printf/ft_voidtohex.c \
                          ft_printf/libft/ft_atoi.c \
                          ft_printf/libft/ft_bzero.c \
                          ft_printf/libft/ft_calloc.c \
                          ft_printf/libft/ft_isalnum.c \
                          ft_printf/libft/ft_isalpha.c \
                          ft_printf/libft/ft_isascii.c \
                          ft_printf/libft/ft_isdigit.c \
                          ft_printf/libft/ft_isprint.c \
                          ft_printf/libft/ft_itoa.c \
                          ft_printf/libft/ft_lstadd_back.c \
                          ft_printf/libft/ft_lstadd_front.c \
                          ft_printf/libft/ft_lstclear.c \
                          ft_printf/libft/ft_lstdelone.c \
                          ft_printf/libft/ft_lstiter.c \
                          ft_printf/libft/ft_lstlast.c \
                          ft_printf/libft/ft_lstmap.c \
                          ft_printf/libft/ft_lstnew.c \
                          ft_printf/libft/ft_lstsize.c \
                          ft_printf/libft/ft_memchr.c \
                          ft_printf/libft/ft_memcmp.c \
                          ft_printf/libft/ft_memcpy.c \
                          ft_printf/libft/ft_memmove.c \
                          ft_printf/libft/ft_memset.c \
                          ft_printf/libft/ft_putchar_fd.c \
                          ft_printf/libft/ft_putendl_fd.c \
                          ft_printf/libft/ft_putnbr_fd.c \
                          ft_printf/libft/ft_putstr_fd.c \
                          ft_printf/libft/ft_split.c \
                          ft_printf/libft/ft_strchr.c \
                          ft_printf/libft/ft_strdup.c \
                          ft_printf/libft/ft_striteri.c \
                          ft_printf/libft/ft_strjoin.c \
                          ft_printf/libft/ft_strlcat.c \
                          ft_printf/libft/ft_strlcpy.c \
                          ft_printf/libft/ft_strlen.c \
                          ft_printf/libft/ft_strmapi.c \
                          ft_printf/libft/ft_strncmp.c \
                          ft_printf/libft/ft_strnstr.c \
                          ft_printf/libft/ft_strrchr.c \
                          ft_printf/libft/ft_strtrim.c \
                          ft_printf/libft/ft_substr.c \
                          ft_printf/libft/ft_tolower.c \
                          ft_printf/libft/ft_toupper.c \
                          pipex.c \
                          pipex_utils.c \
                          
OBJS        := $(SRCS:.c=.o)

.c.o:
	${CC} ${FLAGS} -c $< -o ${<:.c=.o}

################################################################################
#                                  Makefile  objs                              #
################################################################################


CLR_RMV		:= \033[0m
RED		    := \033[1;31m
GREEN		:= \033[1;32m
YELLOW		:= \033[1;33m
BLUE		:= \033[1;34m
CYAN 		:= \033[1;36m
RM		    := rm -f

${NAME}:	${OBJS}
			@echo "$(GREEN)Compilation ${CLR_RMV}of ${YELLOW}$(NAME) ${CLR_RMV}..."
			${CC} ${FLAGS} -o ${NAME} ${OBJS}
			@echo "$(GREEN)$(NAME) created[0m ✔️"

all:		${NAME}

bonus:		all

clean:
			@ ${RM} *.o */*.o */*/*.o
			@ echo "$(RED)Deleting $(CYAN)$(NAME) $(CLR_RMV)objs ✔️"

fclean:		clean
			@ ${RM} ${NAME}
			@ echo "$(RED)Deleting $(CYAN)$(NAME) $(CLR_RMV)binary ✔️"

re:			fclean all

.PHONY:		all clean fclean re


