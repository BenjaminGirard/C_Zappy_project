##
## Makefile for  in /home/tetard/eptechY2/PSU/PSU_2016_zappy
##
## Made by girard
## Login   <benjamin.girard@epitech.eu>
##
## Started on  Thu Jun 22 12:39:12 2017 girard
## Last update Mon Jul  3 22:33:10 2017 fourni_2
##

DIR_COMMON_INC	=	common_srcs/includes/

DIR_SERVER_INC	=	server_srcs/includes/

DIR_COMMON	=	common_srcs/

DIR_SERVER	=	server_srcs/

SRC_SERVER	=	$(DIR_COMMON)fd_tools.c			\
			$(DIR_COMMON)init_common.c		\
			$(DIR_COMMON)check_int.c		\
			$(DIR_COMMON)string_tools.c		\
			$(DIR_COMMON)ring_buffer.c		\
			$(DIR_COMMON)circular_buffer_tool.c	\
			$(DIR_SERVER)init_server_tools.c	\
			$(DIR_SERVER)eggs_tools.c		\
			$(DIR_SERVER)loop_action.c		\
			$(DIR_SERVER)server_execution.c		\
			$(DIR_SERVER)client_data_tools.c	\
			$(DIR_SERVER)erase_clients.c		\
			$(DIR_SERVER)player_data_tools.c	\
			$(DIR_SERVER)send_graphical_msg.c	\
			$(DIR_SERVER)handle_args.c		\
			$(DIR_SERVER)init_teams.c		\
			$(DIR_SERVER)args_functions.c		\
			$(DIR_SERVER)write_usage.c		\
			$(DIR_SERVER)client_reader.c		\
			$(DIR_SERVER)client_writer.c		\
			$(DIR_SERVER)handle_clients_cmd.c	\
			$(DIR_SERVER)timer.c			\
			$(DIR_SERVER)try_team_assignation.c	\
			$(DIR_SERVER)update_team_nb.c		\
			$(DIR_SERVER)cmd_broadcast_tools.c	\
			$(DIR_SERVER)cmd_forward.c		\
			$(DIR_SERVER)cmd_right.c		\
			$(DIR_SERVER)cmd_left.c			\
			$(DIR_SERVER)cmd_look.c			\
			$(DIR_SERVER)cmd_look_tools.c		\
			$(DIR_SERVER)get_tiles.c		\
			$(DIR_SERVER)cmd_inventory.c		\
			$(DIR_SERVER)cmd_broadcast.c		\
			$(DIR_SERVER)cmd_connect_nbr.c		\
			$(DIR_SERVER)cmd_eject.c		\
			$(DIR_SERVER)cmd_eject_tools.c		\
			$(DIR_SERVER)cmd_fork.c			\
			$(DIR_SERVER)cmd_take_object.c		\
			$(DIR_SERVER)cmd_take_object_tools.c	\
			$(DIR_SERVER)cmd_set_object.c		\
			$(DIR_SERVER)cmd_set_object_tools.c	\
			$(DIR_SERVER)cmd_incantation.c		\
			$(DIR_SERVER)cmd_incantation_tools.c	\
			$(DIR_SERVER)send_to_graphic.c		\
			$(DIR_SERVER)send_to_graphic_tools.c	\
			$(DIR_SERVER)get_graphic_client.c	\
			$(DIR_SERVER)send_map_size.c		\
			$(DIR_SERVER)server.c

OBJS_SERVER	=	$(SRC_SERVER:.c=.o)

NAME_SERVER	=	zappy_server

DIR_CLIENT	=	client_srcs/

SRC_CLIENT_CPP	=	$(DIR_CLIENT)main.cpp			\
			$(DIR_CLIENT)socket.cpp			\
			$(DIR_CLIENT)Select.cpp			\
			$(DIR_CLIENT)Player.cpp			\
			$(DIR_CLIENT)Case.cpp			\
			$(DIR_CLIENT)Inventory.cpp		\
			$(DIR_CLIENT)PlayerSendCommands.cpp	\
			$(DIR_CLIENT)PlayerIncantation.cpp	\
			$(DIR_CLIENT)PlayerCore.cpp		\
			$(DIR_CLIENT)CheckPlayerInventory.cpp	\
			$(DIR_CLIENT)CheckPlayerVision.cpp	\
			$(DIR_CLIENT)CmdHandler.cpp		\

SRC_CLIENT_C	=	$(DIR_COMMON)ring_buffer.c		\
			$(DIR_COMMON)circular_buffer_tool.c

OBJS_CLIENT_C	=	$(SRC_CLIENT_C:.c=.o)

OBJS_CLIENT_CPP	=	$(SRC_CLIENT_CPP:.cpp=.o)

NAME_CLIENT	=	zappy_ai

DIR_GRAPHIC	=	graphic_srcs/

SRC_GRAPHIC_CPP	=	$(DIR_GRAPHIC)main.cpp			\
			$(DIR_GRAPHIC)socket.cpp			\
			$(DIR_GRAPHIC)Select.cpp			\
			$(DIR_GRAPHIC)Player.cpp			\
			$(DIR_GRAPHIC)Case.cpp			\
			$(DIR_GRAPHIC)Inventory.cpp		\
			$(DIR_GRAPHIC)PlayerSendCommands.cpp	\
			$(DIR_GRAPHIC)PlayerIncantation.cpp	\
			$(DIR_GRAPHIC)PlayerCore.cpp		\
			$(DIR_GRAPHIC)CheckPlayerInventory.cpp	\
			$(DIR_GRAPHIC)CheckPlayerVision.cpp	\
			$(DIR_GRAPHIC)CmdHandler.cpp		\

SRC_GRAPHIC_C	=	$(DIR_COMMON)ring_buffer.c		\
			$(DIR_COMMON)circular_buffer_tool.c

OBJS_GRAPHIC_C	=	$(SRC_GRAPHIC_C:.c=.o)

OBJS_GRAPHIC_CPP	=	$(SRC_GRAPHIC_CPP:.cpp=.o)

NAME_GRAPHIC	=	zappy_graphic

CFLAGS		+=	-W -Wall -Wextra -Werror -I$(DIR_COMMON_INC)
CFLAGS		+=	-I$(DIR_SERVER_INC)

CXXFLAGS	+=	-std=gnu++14 -W -Wall -Wextra -Werror
CXXFLAGS	+=	-I$(DIR_COMMON_INC)

RM		=	rm -f

CC		=	gcc

CPP		=	g++

all: $(NAME_SERVER) $(NAME_CLIENT) $(NAME_GRAPHIC)

$(NAME_SERVER): $(OBJS_SERVER)
	$(CC) -o $(NAME_SERVER) $(OBJS_SERVER)

$(NAME_CLIENT): $(OBJS_CLIENT_CPP) $(OBJS_CLIENT_C)
		$(CPP) -o $(NAME_CLIENT) $(OBJS_CLIENT_C) $(OBJS_CLIENT_CPP)

$(NAME_GRAPHIC): $(OBJS_GRAPHIC_CPP) $(OBJS_GRAPHIC_C)
		$(CPP) -o $(NAME_GRAPHIC) $(OBJS_GRAPHIC_C) $(OBJS_GRAPHIC_CPP)

clean:
	$(RM) $(OBJS_CLIENT_C) $(OBJS_CLIENT_CPP) $(OBJS_GRAPHIC_CPP) $(OBJS_GRAPHIC_C) $(OBJS_SERVER)

fclean: clean
	$(RM) $(NAME_SERVER) $(NAME_CLIENT) $(NAME_GRAPHIC)

re: fclean all

.PHONY: all clean fclean re
