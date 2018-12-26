
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kbatz <marvin@42.fr>                       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/12/02 04:16:06 by kbatz             #+#    #+#              #
#    Updated: 2018/12/26 18:12:55 by kbatz            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

PRJNAME	= fdf
LIB		= libft libmlx

# **************************************************************************** #

NAME	= $(PRJNAME)
SRCDIR	= srcs/
OBJDIR	= .objs/
HDRDIR	= includes/
TESTDIR	= test/
LIBDIR	= $(LIB)/
LHD		= $(LIBDIR)
SRC		= $(patsubst $(SRCDIR)%,%,$(wildcard $(SRCDIR)*.c))
OBJ		= $(SRC:%.c=%.o)
HDR		= $(wildcard $(HDRDIR)*.h)
TEST	= $(patsubst $(TESTDIR),%,$(wildcard $(TESTDIR)*))
LFLAG	= -I$(LHD) -L$(LIBDIR) -$(patsubst lib%,l%,$(LIB))
IFLAG	= -I$(HDRDIR) -I$(LHD)
CFLAG	= -Wall -Wextra -Werror

vpath %.c $(SRCDIR)
vpath %.o $(OBJDIR)

all: $(NAME)

$(NAME): $(LIB)all $(OBJDIR) $(OBJ)
	gcc $(addprefix $(OBJDIR), $(OBJ)) -o $(NAME) $(IFLAG) $(LFLAG)

$(OBJ): %.o: %.c $(HDR)
	gcc $(CFLAG) $(IFLAG) -c $< -o $(OBJDIR)$@

$(OBJDIR):
	mkdir $(OBJDIR)

clean: $(LIB)fclean
	rm -Rf $(OBJDIR)

fclean: clean
	rm -Rf $(NAME)

re: fclean all

$(LIB)%:
	make -C $(LIBDIR) $(patsubst $(LIB)%, %, $@)

norm:
	norminette $(addprefix $(SRCDIR), $(SRC))
	norminette $(addprefix $(HDRDIR), $(HDR))

t: all $(TEST)

$(TEST): %:
	@echo "--------------------------------------------------"
	@echo "| >>>>> TEST \""$@"\" START >>>>> |"
	@echo ""
	@./$(NAME) $(TESTDIR)$@
	@echo ""
	@echo "| <<<<< TEST \""$@"\" END <<<<< |"
	@echo "--------------------------------------------------"
