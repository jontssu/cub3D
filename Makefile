#Target Binary Program
NAME = cub3D
NAME_BONUS = cub3D_bonus

#Color scheme
COLOUR_GREEN=\033[0;32m
COLOUR_RED=\033[0;31m
COLOUR_BLUE=\033[0;34m
COLOUR_END=\033[0m

#Flags -O2
FLAGS = -Wall -Werror -Wextra -g -I inc -I libft

#Direcory locations
PARSER_DIR = parsing/
RAYCASTING_DIR = ray_casting/
KEYHANDLE_DIR = key_handle/
CORE_DIR = core/
BONUS_DIR = bonus/
OBJS_DIR = obj/
BOBJS_DIR = bonus_obj/

#Sources by folder
_RAYCASTING := ray_casting.c \
				texturing.c
_KEYHANDLE := key_handle.c \
				movement.c
_PARSER := parsing.c error.c set_elements.c check_elements.c \
				get_map.c map_check.c valid_chars_check.c flood_fill.c helpers.c
_CORE := cub3d.c init.c
_BONUS := parsing.c error.c set_elements.c check_elements.c \
				get_map.c map_check.c valid_chars_check.c flood_fill.c helpers.c \
				mouse.c

SRCS = $(_RAYCASTING) $(_PARSER) $(_KEYHANDLE) $(_CORE)
BSRCS = $(_RAYCASTING) $(_BONUS) $(_KEYHANDLE) $(_CORE)
OBJS = $(patsubst %, $(OBJS_DIR)%, $(SRCS:.c=.o))
BOBJS = $(patsubst %, $(BOBJS_DIR)%, $(BSRCS:.c=.o))
LIB = libft/libft.a

all: $(NAME)

$(LIB):
	@make all -C libft
	@echo "$(COLOUR_GREEN)libft compilation completed$(COLOUR_END)"

# @make bonus -C libft
$(NAME):  $(LIB) $(OBJS_DIR) $(OBJS)
	@cc $(FLAGS) $(OBJS) -lmlx -framework OpenGL -framework AppKit -o $@ -L ./libft -lft
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

$(OBJS_DIR)%.o: $(KEYHANDLE_DIR)%.c
	@cc $(FLAGS) -c $< -o $@ 
	@echo "$(COLOUR_BLUE)$@ created$(COLOUR_END)"

$(OBJS_DIR)%.o: $(CORE_DIR)%.c
	@cc $(FLAGS) -c $< -o $@ 
	@echo "$(COLOUR_BLUE)$@ created$(COLOUR_END)"

clean:
	@make clean -C libft
	@echo "$(COLOUR_BLUE)libft object files cleaned$(COLOUR_END)"
	@rm -f $(OBJS)
	@rm -f $(BOBJS)
	@echo "$(COLOUR_BLUE)object directory cleaned$(COLOUR_END)"

fclean: clean
	@rm -rf $(OBJS_DIR)
	@rm -rf $(BOBJS_DIR)
	@rm -f $(LIB)
	@echo "$(COLOUR_RED)libft.a removed$(COLOUR_END)"
	@rm -f $(NAME)
	@echo "$(COLOUR_RED)$(NAME) removed$(COLOUR_END)"

re: fclean all

bonus: $(NAME_BONUS)

$(NAME_BONUS):  $(LIB) $(BOBJS_DIR) $(BOBJS)
	@cc $(FLAGS) $(BOBJS) -lmlx -framework OpenGL -framework AppKit -o $@ -L ./libft -lft
	@echo "$(COLOUR_GREEN)$@ created$(COLOUR_END)"

$(BOBJS_DIR):
	@mkdir -p $(BOBJS_DIR)
	@echo $(BSRCS) $(BOBJS) $(BOBJ_FILES)
	@echo "$(COLOUR_BLUE)object directory created$(COLOUR_END)"

$(BOBJS_DIR)%.o: $(RAYCASTING_DIR)%.c
	@cc $(FLAGS) -c $< -o $@ 
	@echo "$(COLOUR_BLUE)$@ created$(COLOUR_END)"

$(BOBJS_DIR)%.o: $(KEYHANDLE_DIR)%.c
	@cc $(FLAGS) -c $< -o $@ 
	@echo "$(COLOUR_BLUE)$@ created$(COLOUR_END)"

$(BOBJS_DIR)%.o: $(CORE_DIR)%.c
	@cc $(FLAGS) -c $< -o $@ 
	@echo "$(COLOUR_BLUE)$@ created$(COLOUR_END)"

$(BOBJS_DIR)%.o: $(BONUS_DIR)%.c
	@cc $(FLAGS) -c $< -o $@ 
	@echo "$(COLOUR_BLUE)$@ created$(COLOUR_END)"