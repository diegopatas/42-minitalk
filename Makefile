# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ddiniz <ddiniz@student.42sp.org.br>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/10 17:02:41 by ddiniz            #+#    #+#              #
#    Updated: 2022/11/10 17:51:50 by ddiniz           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#include Makefile_setup

LINKER			= gcc
COMPILER		= $(LINKER) -c

REMOVE			= rm
REMOVE_FORCE	= $(REMOVE) -rf
MAKE_DIR		= mkdir -p
DEBUG			= gdb -q -tui
MEMCHECK		= valgrind

FLAG_C			= -Wall -Wextra -Werror
FLAG_LEAK		= --leak-check=full --show-leak-kinds=all --track-origins=yes
FLAG_LEAK		+= -s

PATH_INCLUDES	= includes
PATH_SOURCES	= sources
PATH_CLIENT_OBJECTS	= objects_client
PATH_SERVER_OBJECTS	= objects_server
PATH_BONUS_CLIENT_OBJECTS	= objects_bonus_client
PATH_BONUS_SERVER_OBJECTS	= objects_bonus_server
PATH_LIBRARIES	= libraries
PATH_TESTS		= tests
PATH_LIBFT		= $(PATH_LIBRARIES)/libft

LIBFT			= $(PATH_LIBFT)/libft.a
INCLUDES		= -I$(PATH_INCLUDES) -I$(PATH_LIBFT)

NAME_CLIENT					= client
FILE_CLIENT_SOURCES			= client.c
CLIENT_SOURCES				= $(addprefix $(PATH_SOURCES)/, $(FILE_CLIENT_SOURCES))
FILE_CLIENT_OBJECTS			= $(CLIENT_SOURCES:$(PATH_SOURCES)/%.c=$(PATH_CLIENT_OBJECTS)/%.o)

NAME_SERVER					= server
FILE_SERVER_SOURCES			= server.c
SERVER_SOURCES				= $(addprefix $(PATH_SOURCES)/, $(FILE_SERVER_SOURCES))
FILE_SERVER_OBJECTS			= $(SERVER_SOURCES:$(PATH_SOURCES)/%.c=$(PATH_SERVER_OBJECTS)/%.o)

NAME_BONUS_CLIENT			= client_bonus
FILE_BONUS_CLIENT			= client_bonus.c
BONUS_CLIENT_SOURCES		= $(addprefix $(PATH_SOURCES)/, $(FILE_BONUS_CLIENT))
FILE_BONUS_CLIENT_OBJECTS	= $(BONUS_CLIENT_SOURCES:$(PATH_SOURCES)/%.c=$(PATH_BONUS_CLIENT_OBJECTS)/%.o)

NAME_BONUS_SERVER			= server_bonus
FILE_BONUS_SERVER			= server_bonus.c
BONUS_SERVER_SOURCES		= $(addprefix $(PATH_SOURCES)/, $(FILE_BONUS_SERVER))
FILE_BONUS_SERVER_OBJECTS	= $(BONUS_SERVER_SOURCES:$(PATH_SOURCES)/%.c=$(PATH_BONUS_SERVER_OBJECTS)/%.o)

FILE_HEADER					= $(PATH_INCLUDES)/minitalk.h
FILE_BONUS_HEADER			= $(PATH_INCLUDES)/minitalk_bonus.h

## ----- MANDATORY SETTINGS ------

all: $(NAME_CLIENT) $(NAME_SERVER)

$(LIBFT):
	@$(MAKE) -C $(PATH_LIBFT) all

## ----- CLIENT SETTINGS ------

$(NAME_CLIENT): $(LIBFT) $(PATH_CLIENT_OBJECTS) $(FILE_CLIENT_OBJECTS) $(FILE_HEADER)
	$(LINKER) $(FLAG_C) $(FILE_CLIENT_OBJECTS) $(LIBFT) -o $@

$(PATH_CLIENT_OBJECTS)/%.o: $(PATH_SOURCES)/$(FILE_CLIENT_SOURCES) $(FILE_HEADER)
	$(COMPILER) $(FLAG_C) $(INCLUDES) $< -o $@

$(PATH_CLIENT_OBJECTS):
	$(MAKE_DIR) $(PATH_CLIENT_OBJECTS)

## ----- SERVER SETTINGS ------

$(NAME_SERVER): $(LIBFT) $(PATH_SERVER_OBJECTS) $(FILE_SERVER_OBJECTS) $(FILE_HEADER)
	$(LINKER) $(FLAG_C) $(FILE_SERVER_OBJECTS) $(LIBFT) -o $@

$(PATH_SERVER_OBJECTS)/%.o: $(PATH_SOURCES)/$(FILE_SERVER_SOURCES) $(FILE_HEADER)
	$(COMPILER) $(FLAG_C) $(INCLUDES) $< -o $@

$(PATH_SERVER_OBJECTS):
	$(MAKE_DIR) $(PATH_SERVER_OBJECTS)

## ----- BONUS SETTINGS ------

bonus: $(NAME_BONUS_CLIENT) $(NAME_BONUS_SERVER)

## ----- CLIENT SETTINGS ------

$(NAME_BONUS_CLIENT): $(LIBFT) $(PATH_BONUS_CLIENT_OBJECTS) $(FILE_BONUS_CLIENT_OBJECTS) $(FILE_BONUS_HEADER)
	$(LINKER) $(FLAG_C) $(FILE_BONUS_CLIENT_OBJECTS) $(LIBFT) -o $@

$(PATH_BONUS_CLIENT_OBJECTS)/%.o: $(PATH_SOURCES)/$(FILE_BONUS_CLIENT) $(FILE_BONUS_HEADER)
	$(COMPILER) $(FLAG_C) $(INCLUDES) $< -o $@

$(PATH_BONUS_CLIENT_OBJECTS):
	$(REMOVE_FORCE) $(NAME_CLIENT) $(NAME_SERVER)
	$(REMOVE_FORCE) $(PATH_CLIENT_OBJECTS) $(PATH_SERVER_OBJECTS)
	$(MAKE_DIR) $(PATH_BONUS_CLIENT_OBJECTS)

## ----- SERVER SETTINGS ------

$(NAME_BONUS_SERVER): $(LIBFT) $(PATH_BONUS_SERVER_OBJECTS) $(FILE_BONUS_SERVER_OBJECTS) $(FILE_BONUS_HEADER)
	$(LINKER) $(FLAG_C) $(FILE_BONUS_SERVER_OBJECTS) $(LIBFT) -o $@

$(PATH_BONUS_SERVER_OBJECTS)/%.o: $(PATH_SOURCES)/$(FILE_BONUS_SERVER) $(FILE_BONUS_HEADER)
	$(COMPILER) $(FLAG_C) $(INCLUDES) $< -o $@

$(PATH_BONUS_SERVER_OBJECTS):
	$(MAKE_DIR) $(PATH_BONUS_SERVER_OBJECTS)

# --------------------------------------

clean:
	$(REMOVE_FORCE) $(PATH_CLIENT_OBJECTS) $(PATH_SERVER_OBJECTS)
	$(REMOVE_FORCE) $(PATH_BONUS_CLIENT_OBJECTS) $(PATH_BONUS_SERVER_OBJECTS)
	@$(MAKE) -C $(PATH_LIBFT) clean

fclean: clean
	$(REMOVE_FORCE) $(NAME_CLIENT) $(NAME_SERVER)
	$(REMOVE_FORCE) $(NAME_BONUS_CLIENT) $(NAME_BONUS_SERVER)
	@$(MAKE) -C $(PATH_LIBFT) fclean

re: fclean all

.PHONY: all fclean clean re run leak test debug
