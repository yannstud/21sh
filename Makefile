NAME		=	21sh
FLAG		=	-Werror -Wall -Wextra -g3
PTH_LIBFT	=	libft/
LIBFT		=	$(PTH_LIBFT)libft.a
LNK_LIBFT	=	-L. $(LIBFT)

SRCS		=	srcs/main.c srcs/parsing.c srcs/error_file.c \
				srcs/cd_file.c srcs/env_file.c srcs/cmd.c srcs/utils.c\
				history/history.c history/create_history.c  \
				ft_select/dellistselect.c ft_select/lists.c ft_select/moove.c \
				ft_select/print_select.c ft_select/size_term.c\
				ft_select/autocompletion.c ft_select/parsing_select.c \
				ft_select/end_select.c \
				line_editing/termcapsactions.c line_editing/process_arrows.c\
				line_editing/stractions.c line_editing/signal.c\
				line_editing/cursoractions.c line_editing/cursormoove.c \
				line_editing/processing_line.c \
				line_editing/strdeletting.c line_editing/deletting.c \
				line_editing/copy.c \
				lexer/lexer.c lexer/lexer_handler1.c lexer/lexer_handler2.c lexer/lexer_handler3.c \
				lexer/lexer_print.c lexer/lexer_utils.c \
				parser/parser.c parser/parser_quote.c \
				ast/ast.c ast/ast_tree.c ast/ast_print.c ast/ast_operat.c ast/ast_redir.c \
				exec/exec.c exec/heredoc.c exec/exec_redir.c exec/exec_operat.c exec/exec_core.c \
				exec/exec_utils.c exec/exec_redir2.c \
				builtins/builtin_echo.c builtins/builtin_env.c builtins/builtin_setenv.c builtins/builtin_unsetenv.c \
				builtins/builtin_cd.c builtins/builtin_exit.c \
				print/print.c print/print_err.c print/print_err2.c \
				utils/gnl.c utils/utils.c utils/utils2.c utils/free.c utils/fds.c utils/env_parse.c utils/shlvl.c

OBJ 		=	$(SRCS:.c=.o)

INCLDS		=	-I $(PTH_LIBFT) 

HEADER		=	vingtetunsh.h

all: $(NAME)

$(NAME): $(LIBFT) $(OBJ)
	gcc $(FLAG) -o $@ $^ $(LNK_LIBFT) -ltermcap

$(LIBFT):
	make re -C $(PTH_LIBFT)

%.o: %.c $(HEADER)
	gcc $(FLAG) $(INCLDS) -c -o $@ $<

clean:
	rm -rf $(OBJ)
	make -C $(PTH_LIBFT) clean

fclean: clean
	rm -rf $(NAME)
	make -C $(PTH_LIBFT) fclean

re: fclean all

.PHONY: all clean fclean re
