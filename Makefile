include Makefile_setup

NAME			=
SOURCE			= $(addprefix $(PATH_SOURCES)/, $(FILE_SOURCES))
FILE_HEADER		=
FILE_OBJECTS	= $(SOURCE:$(PATH_SOURCES)/%.c=$(PATH_OBJECTS)/%.o)

FILE_SOURCES	=

all:

$(NAME):
	$(LINKER) $(FLAG_C) $(FILE_OBJECTS) $(LIBFT) -o $@

$(LIBFT):

$(PATH_OBJECTS)/%.o: $(PATH_SOURCES)/%.c $(FILE_HEADER)

$(PATH_OBJECTS):
	$(MAKE_DIR) $(PATH_OBJECTS)

clean:
	$(REMOVE_FORCE) $(PATH_OBJECTS)
	@$(MAKE) -C $(PATH_LIBFT) clean

fclean: clean
	$(REMOVE_FORCE) $(NAME)
	@$(MAKE) -C $(PATH_LIBFT) fclean

re: fclean all

.PHONY: all fclean clean re run leak test debug
