NAME = ft_select
COM = gcc
HEAD_SELECT = ./includes/
HEAD_L = ./libft/
HEAD_LIB = libft.h
HEAD_H = ft_select.h
HEAD_F = $(HEAD_SELECT) \
		$(HEAD_L)
HEADS = $(addprefix -I, $(HEAD_F))
LIB_F = ./libft/
LIB = libft.a
LIB_D = $(addprefix $(LIB_F), $(LIB))
LIB_C = -L $(LIB_F) -lft -ltermcap
SOUS = ./src/
SOUS_FIL =	main.c \
			handle_errors.c
OBJS = $(SOUS_FIL:.c=.o)
SOUS_F = $(addprefix $(SOUS), $(SOUS_FIL))
OBJS_F = $(addprefix $(BIN), $(OBJS))
BIN = ./bin/
TRASH = ft_select.h.gch \
		ft_select.dSYM
FLAGS = -g
REMOVE = rm -rf

.PHONY: all clean re

all: $(NAME)
$(NAME): $(OBJS_F) $(HEAD_SELECT)$(HEAD_H) $(LIB_D)
	$(COM) $(FLAGS) -o $@ $(OBJS_F) $(HEADS) $(LIB_C)
$(LIB_D): $(LIB_F)
	$(MAKE) -sC $(LIB_F) all
$(BIN)%.o: $(SOUS)%.c
	mkdir -p $(BIN) && \
	$(COM) $(FLAGS) -c $< -o $@ $(HEADS)
clean:
	@$(REMOVE) $(OBJS_F) $(BIN) $(TRASH)
	@make -sC $(LIB_F) clean
fclean: clean
	@$(REMOVE) $(NAME)
	@make -sC $(LIB_F) fclean
re: fclean all
