# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kbatz <marvin@42.fr>                       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/11/20 17:33:15 by kbatz             #+#    #+#              #
#    Updated: 2019/02/01 10:21:24 by kbatz            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	libft.a
HDRDIR	=	include/
OBJDIR	=	.obj/
SRCDIR	=	src/

# **************************************************************************** #

SRC		=	$(patsubst $(SRCDIR)%,%,$(wildcard $(SRCDIR)*))
HDR 	=	$(wildcard $(HDRDIR)*)
FLAG	=	-Wall -Wextra -Werror

vpath %.o $(OBJDIR)

OBJ		=	$(SRC:%.c=%.o)

# **************************************************************************** #

vpath %.c $(SRCDIR)
vpath %.o $(OBJDIR)

# **************************************************************************** #

all: $(NAME)

$(NAME): $(OBJDIR) $(OBJ)
	ar rc $(NAME) $(addprefix $(OBJDIR), $(OBJ))

$(OBJ): %.o: %.c $(HDR)
	gcc $(FLAG) -c -I$(HDRDIR) $< -o $(OBJDIR)$@

clean:
	rm -Rf $(OBJDIR)

fclean: clean
	rm -Rf $(NAME)

re: fclean all

$(OBJDIR):
	mkdir $(OBJDIR)

norm:
	norminette *.c *.h
