
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kbatz <marvin@42.fr>                       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/12/02 04:16:06 by kbatz             #+#    #+#              #
#    Updated: 2019/01/06 10:37:26 by kbatz            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

PRJNAME	= fdf
LIB		= libft #libmlx

# **************************************************************************** #

NAME	= $(PRJNAME)
SRCDIR	= src/
OBJDIR	= .obj/
HDRDIR	= include/
TESTDIR	= test/
LIBDIR	= $(addsuffix /,$(LIB))
LHD		= $(LIBDIR)
SRC		= $(patsubst $(SRCDIR)%,%,$(wildcard $(SRCDIR)*.c))
OBJ		= $(SRC:%.c=%.o)
HDR		= $(wildcard $(HDRDIR)*.h)
TEST	= $(patsubst $(TESTDIR),%,$(wildcard $(TESTDIR)*))
LFLAG   = $(addprefix -L,$(LIBDIR)) $(addprefix -,$(patsubst lib%,l%,$(LIB))) -lmlx -framework OpenGL -framework AppKit
IFLAG   = $(addprefix -I,$(HDRDIR)) $(addprefix -I,$(LHD))
CFLAG	= -Wall -Wextra -Werror

vpath %.c $(SRCDIR)
vpath %.o $(OBJDIR)

all: $(addsuffix .all,$(LIB)) $(NAME)

$(NAME): $(OBJDIR) $(OBJ)
	gcc $(addprefix $(OBJDIR), $(OBJ)) -o $(NAME) $(IFLAG) $(LFLAG)

$(OBJ): %.o: %.c $(HDR)
	gcc $(CFLAG) $(IFLAG) -c $< -o $(OBJDIR)$@

$(OBJDIR):
	mkdir $(OBJDIR)

clean:
	rm -Rf $(OBJDIR)

fclean: clean
	rm -Rf $(NAME)

re: fclean all

lib%:
	make -C $(subst .,/ ,$@)

norm:
	norminette $(SRCDIR)
	norminette $(HDRDIR)

t: all $(TEST)

$(TEST): %:
	@echo "--------------------------------------------------"
	@echo "| >>>>> TEST \""$@"\" START >>>>> |"
	@echo ""
	@./$(NAME) $(TESTDIR)$@
	@echo ""
	@echo "| <<<<< TEST \""$@"\" END <<<<< |"
	@echo "--------------------------------------------------"
