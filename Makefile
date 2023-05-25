#Target Binary Program
NAME = cub3D

#Color scheme
COLOUR_GREEN=\033[0;32m
COLOUR_RED=\033[0;31m
COLOUR_BLUE=\033[0;34m
COLOUR_END=\033[0m

#Flags
FLAGS = -Wall -Werror -Wextra -g -I inc -I libft

#Direcory locations
PARSER_DIR = parsing/
RAYCASTING_DIR = ray_casting/
CORE_DIR = core/
OBJS_DIR = obj/

#Sources by folder
_PARSER := parsing.c error.c set_elements.c check_elements.c \
get_map.c map_check.c valid_chars_check.c flood_fill.c
_RAYCASTING := ray_casting.c
_CORE := cub3d.c

SRCS = $(_RAYCASTING) $(_PARSER) $(_CORE)
OBJS = $(patsubst %, $(OBJS_DIR)%, $(SRCS:.c=.o))

LIB = libft/libft.a

all: $(NAME)

$(LIB):
	@make all -C libft
	@echo "$(COLOUR_GREEN)libft compilation completed$(COLOUR_END)"

# @make bonus -C libft
$(NAME):  $(LIB) $(OBJS_DIR) $(OBJS)
	@cc $(FLAGS) $(OBJS) -o $@ -L ./libft -lft
	@echo "$(COLOUR_GREEN)$@ created$(COLOUR_END)"

$(OBJS_DIR):
	@mkdir -p $(OBJS_DIR)
	@echo $(SRCS) $(OBJS) $(OBJ_FILES)
	@echo "$(COLOUR_BLUE)object directory created$(COLOUR_END)"

$(OBJS_DIR)%.o: $(PARSER_DIR)%.c
	@cc $(FLAGS) -c $< -o $@ 
	@echo "$(COLOUR_BLUE)$@ created$(COLOUR_END)"

$(OBJS_DIR)%.o: $(RAYCASTING_DIR)%.c
	@cc $(FLAGS) -c $< -o $@ 
	@echo "$(COLOUR_BLUE)$@ created$(COLOUR_END)"

$(OBJS_DIR)%.o: $(CORE_DIR)%.c
	@cc $(FLAGS) -c $< -o $@ 
	@echo "$(COLOUR_BLUE)$@ created$(COLOUR_END)"

clean:
	@make clean -C libft
	@echo "$(COLOUR_BLUE)libft object files cleaned$(COLOUR_END)"
	@rm -f $(OBJS)
	@echo "$(COLOUR_BLUE)object directory cleaned$(COLOUR_END)"

fclean: clean
	@rm -rf $(OBJS_DIR)
	@rm -f $(LIB)
	@echo "$(COLOUR_RED)libft.a removed$(COLOUR_END)"
	@rm -f $(NAME)
	@echo "$(COLOUR_RED)$(NAME) removed$(COLOUR_END)"

re: fclean all

bonus: fclean all
