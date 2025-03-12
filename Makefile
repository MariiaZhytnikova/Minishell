
NAME		:= minishell

CC = cc
CFLAGS		:= -Wextra -Wall -Werror

HEADERS		:= -I ./inc

SRCS_PATH	:= ./src
OBJS_PATH	:= ./obj

SRCS := $(SRCS_PATH)/main.c \
		$(SRCS_PATH)/errors.c \
		$(SRCS_PATH)/promt.c \
		$(SRCS_PATH)/libft_utils.c


OBJS	:= $(SRCS:$(SRCS_PATH)/%.c=$(OBJS_PATH)/%.o)

NORM	:= norminette

all: $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(OBJS) $(HEADERS) -o $(NAME) -lreadline
	@echo "$(NAME) building completed ..."

$(OBJS_PATH):
	@mkdir -p $(OBJS_PATH)

$(OBJS_PATH)/%.o: $(SRCS_PATH)/%.c | $(OBJS_PATH)
	@$(CC) $(CFLAGS) $(HEADERS) -c $< -o $@

clean:
	@rm -rf $(OBJS_PATH)
	@echo "cleaning completed ..."

fclean: clean
	@rm -f $(NAME)
	@echo "force cleaning completed..."

re: fclean all

norm:
	@$(NORM) */*.h */*/*.c

.PHONY: all clean fclean re norm