# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cadenegr <neo_dgri@hotmail.com>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/11 12:24:18 by cadenegr          #+#    #+#              #
#    Updated: 2024/06/11 12:26:14 by cadenegr         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

SRCDIR = src
OBJDIR = obj

SRC_FILES = $(wildcard $(SRCDIR)/*.c)
#SRC = $(addprefix $(SRCDIR)/, $(SRC_FILES))
OBJ = $(patsubst $(SRCDIR)/%.c,$(OBJDIR)/%.o,$(SRC_FILES))

INCLUDES = -I./include

CC = cc
CFLAGS = -Wall -Wextra -Werror
#LDFLAGS = -L$(LIBFTDIR) -lft_printf
RM = rm -rf

.PHONY: all clean fclean re

all: $(NAME)
$(NAME): $(OBJDIR) $(OBJ)
	$(CC) $(CFLAGS) $(INCLUDES) -o $(NAME) $(OBJ)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJDIR):
	mkdir -p $(OBJDIR)

clean:
	$(RM) $(OBJDIR)

fclean: clean
	$(RM) $(NAME)

re: fclean all