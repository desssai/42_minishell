SRCS	=	./sources/minishell_main.c \
			./sources/readline_prompt.c \
			./sources/command_parsing1.c \
			./sources/command_parsing2.c \
			./sources/environ_vars_utils1.c \
			./sources/environ_vars_utils2.c \

OBJS	=	$(SRCS:.c=.o)

HEADS	=	./includes

NAME	=	parser

LNAME	=	libft/libft.a

GCC		=	gcc

FLAGS	=	-Wall -Werror -Wextra

RM		=	rm -f

%.o: %.c ./inclues/minishell.h
	$(GCC) $(FLAGS) -I$(HEADS) -c $< -o $@ 

$(NAME): $(OBJS) ./libft/libft.h
	$(MAKE) -C libft all
	$(GCC) $(FLAGS) $(OBJS) $(LNAME) -o $(NAME) -lreadline

all:	$(NAME)

clean:
		$(MAKE) -C libft clean
		$(RM) $(OBJS)

fclean: clean
		$(RM) $(LNAME)
		$(RM) $(NAME)

re:		fclean all