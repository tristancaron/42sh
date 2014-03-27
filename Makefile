#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tcaron <tcaron@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2013/12/26 11:52:41 by tcaron            #+#    #+#              #
#    Updated: 2013/12/26 11:52:42 by tcaron           ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME		= 42sh

LIB			= libft/

SRCS		= src/program_main/ft_add_elem.c \
			  src/builtin/ft_isbuiltin.c \
			  src/builtin/ft_cd.c \
			  src/builtin/ft_read.c \
			  src/builtin/ft_set.c \
			  src/builtin/ft_isbuiltin_init.c \
			  src/cleaner/ft_cleaner.c \
			  src/cpy_cut_paste/ft_main_escp_seq.c \
			  src/cursor_motion/ft_cursor_motion.c \
			  src/syntax/ft_first_control.c \
			  src/syntax/ft_exclamation.c \
			  src/touch_control/ft_keycatch.c \
			  src/error/ft_error.c \
			  src/exec/ft_exec.c \
			  src/exec/ft_gotredirection.c \
			  src/exec/ft_launch.c \
			  src/exec/ft_pipe.c \
			  src/exec/ft_redirection.c \
			  src/memlib/ft_ctrl_alloc.c \
			  src/history/ft_get_current.c \
			  src/globbing/glob.c \
			  src/lexer/ft_lexer.c \
			  src/lexer/ft_init_lexer.c \
			  src/parser/ft_intern_var.c \
			  src/parser/ft_parser_clean.c \
			  src/parser/ft_parse_elem.c \
			  src/parser/ft_init_parser.c \
			  src/parser/ft_check_env.c \
			  src/path_control/ft_path_tree.c \
			  src/touch_control/ft_keyopt.c \

SRCS_TERM	= src/builtin/ft_echo.c \
			  src/completion/ft_completion.c \
			  src/cursor_motion/ft_by_word_or_line.c \
			  src/cursor_motion/ft_word_insert.c \
			  src/path_control/ft_init_path.c \
			  src/program_main/ft_read_input.c \
			  src/program_main/main.c \
			  src/prompt/ft_prompt.c \
			  src/termods/ft_termods.c \
  			  src/termods/ft_signal.c \
			  src/touch_control/ft_keycatch_ud_wl.c \

LIB			= libft/libft.a

TERM_LIB	= -ltermcap

OBJS		= $(SRCS:.c=.o)

OBJS_TERM	= $(SRCS_TERM:.c=.o)

CFLAGS		= -Wall -Wextra -Werror -O3 -g

RM			= rm -rf

.PHONY: fclean clean all

.SILENT:

all: $(NAME)

$(NAME): $(OBJS) $(OBJS_TERM)
	@echo "\n\033[2K\033[1;31mLIBFT\033[0m"
	@make -C ./libft
	@echo "\033[A\033[2K\033[A\033[2K\033[1;31mLIBFT \033[1;32m√\033[0m"
	@echo "\033[2K\033[1;31m$(NAME)\033[0m"
	@$(CC) -o $(NAME) $(SRCS) $(SRCS_TERM) $(TERM_LIB) $(CFLAGS) $(LIB)
	@echo "\033[A\033[2K\033[1;31m$(NAME) \033[1;32m√\033[0m"

clean:
	@make -C libft/ clean
	@$(RM) $(OBJS) $(OBJS_TERM)
	@echo "\033[1;31mClean \033[1;32m √ \033[0m"

fclean:		clean
	@make -C libft/ fclean
	@$(RM) $(NAME)
	@$(RM) debug
	@$(RM) 42sh.dSYM
	@echo "\033[1;31mFclean \033[1;32m √ \033[0m"

re:			fclean $(NAME)
