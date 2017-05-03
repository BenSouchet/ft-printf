# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bsouchet <bsouchet@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/01/28 18:36:22 by angavrel          #+#    #+#              #
#    Updated: 2017/05/03 15:16:45 by bsouchet         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

C = clang

NAME = libftprintf.a

FLAGS = -Wall -Wextra -Werror -O2

LIBFT = libft

DIR_S = sources

DIR_O = temporary

HEADER = include

SOURCES = ft_printf.c \
		  parsing.c \
		  number.c \
		  string.c \
		  buffer.c \
		  bonus.c

SRCS = $(addprefix $(DIR_S)/,$(SOURCES))

OBJS = $(addprefix $(DIR_O)/,$(SOURCES:.c=.o))

all: temporary $(NAME)

$(NAME): $(OBJS)
	@make -C $(LIBFT)
	@cp libft/libft.a ./$(NAME)
	@ar rc $(NAME) $(OBJS)
	@ranlib $(NAME)

temporary:
	@mkdir -p temporary

$(DIR_O)/%.o: $(DIR_S)/%.c
	@$(CC) $(FLAGS) -I $(HEADER) -o $@ -c $<

norme:
	norminette ../libft/$(HEADER)
	@echo
	norminette ../libft/$(DIR_S)

clean:
	@rm -f $(OBJS)
	@rm -rf $(DIR_O)
	@make clean -C $(LIBFT)

fclean: clean
	@rm -f $(NAME)
	@make fclean -C $(LIBFT)

re: fclean all
