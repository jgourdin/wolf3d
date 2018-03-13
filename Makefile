SRCS = src/vapor.c src/hook.c src/sound_text.c src/main.c src/move.c src/factory.c src/text.c src/map.c src/wallfloor.c src/thegame.c src/gun.c

OBJS = $(SRCS:.c=.o)

CFLAGS = -Wall -Wextra -Werror

CC = gcc

NAME = wolf3d

LIBS = libft/libft.a\

all: $(NAME)

$(NAME): $(OBJS)
	@echo "${Y}Lib loading${NC}"
		make -C ./libft
		make -C ./minilibx_macos
		$(CC) $(CFLAGS) $(OBJS) -I libft -L./libft -lft -o $(NAME) -framework OpenGL -framework AppKit -I minilibx_macos -L./minilibx_macos/ -lmlx
%.o: %.c
	@echo "${G}[OK]${NC}	${Y}Compiling:${NC}" $<
	gcc $< $(CFLAGS) -I libft -I includes -c -o $@

clean: 
		rm -f $(OBJS)
		make -C ./libft clean
		make -C ./minilibx_macos clean 
		@echo "${R}target eliminated${NC}"
fclean: clean
		rm -f $(NAME)
		make -C ./libft fclean
		@echo "${Y}$(NAME) ${R}Nuke perfectly done${NC}"

re: fclean all
