# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ekashirs <ekashirs@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/17 16:25:58 by mzhitnik          #+#    #+#              #
#    Updated: 2025/04/25 15:15:23 by ekashirs         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		:= minishell

CC = cc
CFLAGS		:= -Wextra -Wall -Werror -Wunused

HEADERS		:= -I ./inc

SRCS_PATH	:= ./src
OBJS_PATH	:= ./obj
LIBFT_PATH	:= ./libft
LIBFT		:= $(LIBFT_PATH)/libft.a

BUILTINS = cd echo env exit export export2 export3 pwd unset

EXEC = exec processing pipe and_or open redirect

MAIN = main errors signals

TOKENS = prompt parsing quotes token_check here_doc here_doc_lim skip_quotes\
			delimiters command_utils numbers redirection expansion \
			split wild_cards wild_utils history print

UTILS = utils_one utils_two ll_utils_one ll_utils_two free exec_utils

SRCS := $(addsuffix .c, $(addprefix src/, $(MAIN))) \
	  $(addsuffix .c, $(addprefix src/execution/, $(EXEC))) \
	  $(addsuffix .c, $(addprefix src/builtins/, $(BUILTINS))) \
	  $(addsuffix .c, $(addprefix src/tokenization/, $(TOKENS))) \
	  $(addsuffix .c, $(addprefix src/utils/, $(UTILS)))

OBJS	:= $(SRCS:$(SRCS_PATH)/%.c=$(OBJS_PATH)/%.o)

NORM	:= norminette

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	@$(CC) $(CFLAGS) $(OBJS) $(HEADERS) $(LIBFT) -o $(NAME) -lreadline 
#-fsanitize=address
	@echo "$(NAME) building completed ..."

$(OBJS_PATH):
	@mkdir -p $(OBJS_PATH)

$(OBJS_PATH)/%.o: $(SRCS_PATH)/%.c | $(OBJS_PATH)
	@$(CC) $(CFLAGS) $(HEADERS) -c $< -o $@

$(LIBFT):
	@$(MAKE) -C $(LIBFT_PATH) > /dev/null 2>&1

clean:
	@rm -rf $(OBJS_PATH)
	@$(MAKE) -C $(LIBFT_PATH) clean > /dev/null 2>&1
	@echo "cleaning completed ..."

fclean: clean
	@rm -f $(NAME)
	@$(MAKE) -C $(LIBFT_PATH) fclean > /dev/null 2>&1
	@echo "force cleaning completed..."

re: fclean all

norm:
	@$(NORM) */*.h */*/*.c

.PHONY: all clean fclean re norm
