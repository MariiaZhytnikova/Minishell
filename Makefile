# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mzhitnik <mzhitnik@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/17 16:25:58 by mzhitnik          #+#    #+#              #
#    Updated: 2025/04/12 13:47:56 by mzhitnik         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		:= minishell

CC = cc
CFLAGS		:= -Wextra -Wall -Werror

HEADERS		:= -I ./inc

SRCS_PATH	:= ./src
OBJS_PATH	:= ./obj
LIBFT_PATH	:= ./libft
LIBFT		:= $(LIBFT_PATH)/libft.a

BUILTINS = cd echo env exit export export2 pwd unset

EXEC = exec processing pipe and_or open redirect

MAIN = main errors signals

TOKENS = prompt parsing quotes token_check here_doc here_doc_lim skip_quotes\
			delimiters tokens_parsing numbers redirection expansion wild_cards wild_utils history

UTILS = utils linked_list_utils free

SRCS := $(addsuffix .c, $(addprefix src/, $(MAIN))) \
	  $(addsuffix .c, $(addprefix src/execution/, $(EXEC))) \
	  $(addsuffix .c, $(addprefix src/builtins/, $(BUILTINS))) \
	  $(addsuffix .c, $(addprefix src/tokenization/, $(TOKENS))) \
	  $(addsuffix .c, $(addprefix src/utils/, $(UTILS)))

OBJS	:= $(SRCS:$(SRCS_PATH)/%.c=$(OBJS_PATH)/%.o)

NORM	:= norminette

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	@$(CC) $(OBJS) $(HEADERS) $(LIBFT) -o $(NAME) -lreadline -fsanitize=address
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
