CC= \
	cc
CFLAGS= \
	-Wall \
	-Wextra \
	-Werror \
	-g
SRCS= \
	./so_long.c \
	./map0.c \
	./map1.c \
	./map2.c \
	./io.c \
	./player.c \
	./image.c \
	./assets.c \
	./render.c
OBJS= \
	$(SRCS:.c=.o)
MINILIBX= \
	./minilibx/libmlx.a
LIBFT= \
	./libft/libft.a
LDFLAGS= \
	-L ./minilibx -L ./libft
LFLAGS= \
	-lm \
	-lz \
	-lft \
	-lmlx \
	-lX11 \
	-lXext
NAME= \
	so_long

all: $(NAME)

$(NAME): $(OBJS) $(MINILIBX) $(LIBFT)
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS) $(LFLAGS)

$(OBJS): %.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(MINILIBX):
	make -C ./minilibx

$(LIBFT):
	make -C ./libft

.PHONY: clean fclean re

clean:
	make -C ./libft clean
	make -C ./minilibx clean
	rm -f $(OBJS)

fclean: clean
	make -C ./libft fclean
	make -C ./minilibx clean
	rm -f $(NAME)

re: fclean all
