NAME		:=	miniRT

CC			:=	cc
CFLAGS 		:=	-Wall -Werror -Wextra -MMD -MP

SRCS_DIR	:=	./src/
SRCS		:= 	$(SRCS_DIR)main.c \
				$(SRCS_DIR)exit.c \
				$(SRCS_DIR)parse/parse.c \
				$(SRCS_DIR)parse/parse_ACL.c \
				$(SRCS_DIR)parse/parse_shape.c \
				$(SRCS_DIR)parse/parse_utils.c \
				$(SRCS_DIR)parse/parse_vec3.c \
				$(SRCS_DIR)parse/init.c \
				$(SRCS_DIR)color/color.c \
				$(SRCS_DIR)raytrace/raytrace.c \
				$(SRCS_DIR)raytrace/shading.c \
				$(SRCS_DIR)raytrace/intersect.c \
				$(SRCS_DIR)shape/shape_utils.c \
				$(SRCS_DIR)shape/sphere.c \
				$(SRCS_DIR)shape/plane.c \
				$(SRCS_DIR)shape/cylinder.c \
				$(SRCS_DIR)shape/cone.c \
				$(SRCS_DIR)utils/utils.c \
				$(SRCS_DIR)vector/vector_calc_addsub.c \
				$(SRCS_DIR)vector/vector_calc_product.c \
				$(SRCS_DIR)key/key_handler.c \
				$(SRCS_DIR)key/key_utils.c
MLX_DIR		:= 	./minilibx
LIB_DIR		:= 	./libft
INCLUDES	:=	-I ./include -I$(MLX_DIR) -I$(LIB_DIR)
LIB			:=	./libft/libft.a
OBJS_DIR	:=	./obj/
OBJS		:=	$(SRCS:$(SRCS_DIR)%.c=$(OBJS_DIR)%.o)
DEPS		:=	$(SRCS:$(SRCS_DIR)%.c=$(OBJS_DIR)%.d)

ifeq ($(shell uname), Darwin)
	MLX_FLAGS = minilibx/libmlx.a -L/usr/X11R6/lib -lX11 -lXext
else
	MLX_FLAGS = minilibx/libmlx.a -lXext -lX11 -lm
endif


$(NAME): $(OBJS)
	make -C $(MLX_DIR)
	make -C $(LIB_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) $(OBJS) -o $(NAME) $(MLX_FLAGS) $(LIB)

$(OBJS_DIR)%.o: $(SRCS_DIR)%.c
	@mkdir -p $$(dirname $@)
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ -c $<

all: $(NAME)

clean:
	make -C $(MLX_DIR) clean
	make -C $(LIB_DIR) clean
	rm -rf $(OBJS_DIR)

fclean: clean
	rm -f $(NAME)
	rm -f $(MLX_DIR)/libmlx.a
	rm -f $(LIB_DIR)/libft.a

re: fclean all

sanitize: CFLAGS += -fsanitize=address
sanitize: re

norm:
	norminette $(SRCS_DIR)

normall:
	norminette $(SRCS_DIR) $(LIB_DIR) ./include

nof: CFLAGS :=	-MMD -MP
nof: all

run r: all
	./$(NAME) sample.rt

-include $(DEPS)

.PHONY: all clean fclean re sanitize norm no run r
