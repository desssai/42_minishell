SRCS	=	./parser.c \
			./parser_main.c \
			./parser_envp.c \
			./parser_envs_init.c \
			./parser_envs_struct.c \

OBJS	=	$(SRCS:.c=.o)

HEADS	=	./

NAME	=	parser

LNAME	=	libft/libft.a

GCC		=	gcc

FLAGS	=	-Wall -Werror -Wextra

RM		=	rm -f

%.o: %.c ./minishell.h
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