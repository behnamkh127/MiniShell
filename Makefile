NAME = minishell
LIBFT = libft/libft.a
HEADER = ./inc/
CC = cc
FLAGS = -Iinc -I/usr/local/opt/readline/include/ -Wall -Werror -Wextra
LINK_RL = /usr/local/opt/readline/lib
INCL_RL = /usr/local/opt/readline/include/

SRCS = src/bultins.c src/cd.c src/echo.c src/echo_print.c src/echo_print2.c src/env.c src/exec.c src/exit_utils.c src/utils.c \
		src/exit.c src/export_var.c src/export.c src/fork_pipe.c src/here_doc.c src/input.c src/main.c src/mini_exit.c src/output.c \
		src/parsing_utils.c src/parsing.c src/process.c src/scan_line.c src/scan_line_utils.c src/signal.c src/unset.c src/var.c 
OBJECTS = $(SRCS:.c=.o)

GREEN	=	\e[0;32m
YELLOW	=	\e[0;33m
CYAN	=	\e[0;36m
RESET	=	\e[0m

all: $(NAME)

$(NAME): $(LIBFT) $(OBJECTS)
	@$(CC) $(FLAGS) $(LIBFT) $(OBJECTS) -lcurses -ltermcap -lreadline -L $(LINK_RL) -o $(NAME) 
	@printf "$(GREEN)Executable created$(RESET)\n"

$(LIBFT):
	@make -C ./libft
	@printf "$(GREEN)Compiling libraries...$(RESET)\n"

%.o: %.c
	@$(CC) $(FLAGS) -I $(INCL_RL) -I $(HEADER) -c $< -o $@

clean:
	@rm -f $(OBJECTS)
	@make clean -C ./libft
	@printf "$(CYAN)Cleaning object files...$(RESET)\n"

fclean: clean
	@rm -f $(NAME)
	@make fclean -C ./libft
	@printf "$(CYAN)Cleaning executables...$(RESET)\n"

re: fclean all

.PHONY: all clean fclean re