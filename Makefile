NAME		:=	miniRT

CC			:=	gcc
CFLAGS 		:=	-Wall -Werror -Wextra -MMD -MP
SRCS		:= 	main.c
MLX_DIR		:= 	./minilibx
LIB_DIR		:= 	./libft
LIB			:=	./libft/libft.a
OBJS_DIR	:=	./obj/
OBJS		:=	$(SRCS:%.c=$(OBJS_DIR)%.o)
INCLUDES	:=	-I./include -I$(MLX_DIR) -I$(LIB_DIR)

ifeq ($(shell uname), Darwin)
	MLX_FLAGS = minilibx/libmlx.a -L/usr/X11R6/lib -lX11 -lXext
else
	MLX_FLAGS = minilibx/libmlx.a -lXext -lX11 -lm
endif

$(NAME): $(OBJS)
#	make -C $(MLX_DIR)
#	make -C $(LIB_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) $(OBJS) -o $(NAME) $(MLX_FLAGS) $(LIB)

$(OBJS_DIR)%.o: %.c
	mkdir -p $(OBJS_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ -c $<

all: $(NAME)

clean:
#	make -C $(MLX_DIR) clean
#	make -C $(LIB_DIR) clean
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)
#	rm -f $(MLX_DIR)/libmlx.a
#	rm -f $(LIB_DIR)/libft.a

re: fclean all

sanitize: CFLAGS += -fsanitize=address
sanitize: re

norm:
	norminette $(SRCS) include

normaall:
	norminette $(SRCS) include $(LIB_DIR)

.PHONY: all clean fclean re sanitize norm no
