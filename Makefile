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
PARSER_DIR = mandatory/parsing/
RAYCASTING_DIR = mandatory/ray_casting/
KEYHANDLE_DIR = mandatory/key_handle/
CORE_DIR = mandatory/core/
OBJS_DIR = obj/

BPARSER_DIR = bonus/parsing/
BRAYCASTING_DIR = bonus/ray_casting/
BKEYHANDLE_DIR = bonus/key_handle/
BCORE_DIR = bonus/core/
# BONUS_DIR = bonus/
BOBJS_DIR = bonus_obj/

#Sources by folder
_RAYCASTING := ray_casting.c \
				texturing.c
_KEYHANDLE := key_handle.c \
				movement.c
_PARSER := parsing.c error.c set_elements.c check_elements.c \
				get_map.c map_check.c valid_chars_check.c flood_fill.c helpers.c
_CORE := cub3d.c init.c
B_RAYCASTING := $(subst .c,_bonus.c,$(_RAYCASTING)) minimap_bonus.c sprite_bonus.c
B_KEYHANDLE := $(subst .c,_bonus.c,$(_KEYHANDLE)) mouse_bonus.c
B_PARSER := $(subst .c,_bonus.c,$(_PARSER))
B_CORE := $(subst .c,_bonus.c,$(_CORE))

SRCS = $(_RAYCASTING) $(_PARSER) $(_KEYHANDLE) $(_CORE)
BSRCS = $(B_RAYCASTING) $(B_KEYHANDLE) $(B_PARSER) $(B_CORE)
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
	@rm -f $(NAME_BONUS)
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

$(BOBJS_DIR)%.o: $(BRAYCASTING_DIR)%.c
	@cc $(FLAGS) -c $< -o $@ 
	@echo "$(COLOUR_BLUE)$@ created$(COLOUR_END)"

$(BOBJS_DIR)%.o: $(BKEYHANDLE_DIR)%.c
	@cc $(FLAGS) -c $< -o $@ 
	@echo "$(COLOUR_BLUE)$@ created$(COLOUR_END)"

$(BOBJS_DIR)%.o: $(BCORE_DIR)%.c
	@cc $(FLAGS) -c $< -o $@ 
	@echo "$(COLOUR_BLUE)$@ created$(COLOUR_END)"

$(BOBJS_DIR)%.o: $(BPARSER_DIR)%.c
	@cc $(FLAGS) -c $< -o $@ 
	@echo "$(COLOUR_BLUE)$@ created$(COLOUR_END)"