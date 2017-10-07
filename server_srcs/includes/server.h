/*
** server.h for  in /home/tetard/eptechY2/PSU/PSU_2016_zappy
**
** Made by girard
** Login   <benjamin.girard@epitech.eu>
**
** Started on  Thu Jun 22 12:41:43 2017 girard
** Last update Sun Jul  2 20:51:11 2017 girard
*/

#ifndef SERVER_H_
# define SERVER_H_

# include <sys/select.h>
# include <stdlib.h>
# include "timer.h"
# include "args.h"
# include "common.h"
# include "ring_buffer.h"

# define XOSUPXT(x1, x2)	((x1 > x2) ? (1) : (x2 > x1 ? (2) : (0)))
# define YOSUPYT(y1, y2)	((y1 > y2) ? (1) : (y2 > y1 ? (2) : (0)))

static const char * const	GRAPHIC = "GRAPHIC";
static const int		LIFE_UNIT = 126000000;
static const int		LIMIT_FORK = 12;

typedef struct			s_broad_res
{
  unsigned int			x_sup;
  unsigned int			y_sup;
  double			coef_min;
  double			coef_max;
  int				res;
}				t_broad_res;

typedef enum			s_direction
  {
    UP = 0,
    LEFT,
    DOWN,
    RIGHT
  }				t_direction;

typedef struct			s_ctrl
{
  int				key;
  int				deep;
}				t_ctrl;

typedef enum			s_action_type
  {
    FORWARD_ACTION = 0,
    RIGHT_ACTION,
    LEFT_ACTION,
    LOOK_ACTION,
    INVENTORY_ACTION,
    BROADCAST_ACTION,
    CONNECT_NBR_ACTION,
    FORK_ACTION,
    EJECT_ACTION,
    TAKE_ACTION,
    SET_ACTION,
    INCANTATION_ACTION,
    DEFAULT_ACTION
  }				t_action_type;

typedef struct			s_ressources t_ressources;
typedef struct			s_action t_action;
typedef struct			s_client_data t_client_data;
typedef struct			s_select_data t_select_data;
typedef struct			s_server_data t_server_data;

typedef struct			s_ressources
{
  long long			life;
  unsigned int			food;
  unsigned int			linemate;
  unsigned int			deraumere;
  unsigned int			sibur;
  unsigned int			mendiane;
  unsigned int			phiras;
  unsigned int			thystame;
}				t_ressources;

typedef struct			s_action
{
  double			cooldown_val;
  double			cooldown;
  char				*cmd;
  char				*cmd_proto;
  int				(*action_cmd)(t_server_data * const data,
					      const int fd,
					      const char * const cmd);
  int				(*check_cmd)(t_server_data * const data,
					     const int fd,
					     const char * const cmd);
}				t_action;

typedef struct			s_egg
{
  int				x;
  int				y;
  double			cooldown;
}				t_egg;

typedef struct			s_client_data
{
  const char			*team;
  int				fd;
  t_ring_buff			buff_reader;
  t_ring_buff			buff_writer;
  t_egg				*eggs;
  int				nb_eggs;
  bool				is_egg;
  t_direction			dir;
  unsigned int			pos_x;
  unsigned int			pos_y;
  unsigned int			lvl;
  t_ressources			inventory;
  t_action			action[DEFAULT_ACTION];
  struct s_client_data		*tail;
}				t_client_data;

typedef struct			s_select_data
{
  fd_set			fd_read;
  fd_set			fd_write;
  struct timeval		tv;
}				t_select_data;

typedef struct			s_server_data
{
  t_args			args_data;
  struct timeval		unow;
  t_ressources			*map;
  t_data_con			dc;
  t_select_data			select_data;
  t_client_data			*c_data;
  long long			graphic_cooldown;
}				t_server_data;

/*
** ------------ Init server from init_server_tools.c --------
*/
int				init_accept(t_data_con *dc);
int				init_server_connexion(t_server_data *
						      const data);
/*
** ------------ Server execution from server_execution.c ---
*/
void				init_action(t_client_data * const c_data,
					    const int freq);
int				update_data(t_server_data * const data);
int				server_execution(t_server_data *
						 const data);
int				close_connexion(t_server_data * const data,
						const int fd);
/*
** ------------ Data tools for client from client_data_tools.c --
*/
t_client_data			*find_player_pos(t_client_data * const c_data,
						 const unsigned int x,
						 const unsigned int y);
t_client_data			*find_client_fd(t_client_data *c_data,
						const int fd);
t_client_data			*add_client(t_server_data * const data,
					   const int fd);

t_client_data			*remove_client(t_client_data *data,
					      const int fd);

void				erase_clients(t_client_data * data);
/*
** ------------ Reading data from client_reader.c | handle_clients_cmd.c -
*/
int				cmd_compare(const char * const line,
					    const char * const cmd);

int				handle_clients_cmd(t_server_data *
						   const data);
int				write_data_to_client(t_client_data *
						     const data,
						     const int fd);
int				read_data_from_client(t_server_data *
						      const data,
						      const int fd);

/* ------------ client_writter.c - */
int				write_data_to_client(t_client_data *
						     const c_data,
						     const int fd);
/*
** ------------ team assignation ---------------------------
*/
int				nb_players_in_team(t_server_data * const data,
						   const int fd);
int				update_team_nb(t_server_data * const data,
					       const int fd);
int				try_team_assignation(t_server_data *
						     const data,
						     const int fd,
						     const char *
						     const cmd);

/* ------------ Command prototypes ----------------------- */
/*
** Command Forward
*/
int				cmd_forward(t_server_data *
					    const data,
					    const int fd,
					    const char * const cmd);
int				cmd_check_forward(t_server_data *
						 const data,
						 const int fd,
						 const char * const cmd);

/*
** Command Right
*/
int				cmd_right(t_server_data *
					  const data,
					  const int fd,
					  const char * const cmd);
int				cmd_check_right(t_server_data *
					       const data,
					       const int fd,
					       const char * const cmd);

/*
** Command Left
*/
int				cmd_left(t_server_data *
					 const data,
					 const int fd,
					 const char * const cmd);
int				cmd_check_left(t_server_data *
					      const data,
					      const int fd,
					      const char * const cmd);

/*
** Command Inventory
*/
int				cmd_inventory(t_server_data *
					      const data,
					      const int fd,
					      const char * const cmd);
int				cmd_check_inventory(t_server_data *
						   const data,
						   const int fd,
						   const char * const cmd);

/*
** Command Broadcast
*/
int				cmd_broadcast(t_server_data *
					      const data,
					      const int fd,
					      const char * const cmd);
int				cmd_check_broadcast(t_server_data *
						    const data,
						    const int fd,
						    const char * const cmd);
int				write_broadcast_buffer(t_ring_buff *
						       const buff,
						       const int way,
						       const char * const str);

/*
** Command Connect nbr
*/

int				find_abs_x(t_server_data * const data,
					   t_client_data * const broadcaster,
					   t_client_data * const current);
int				find_abs_y(t_server_data * const data,
					   t_client_data * const broadcaster,
					   t_client_data * const current);
double				calc_affine_coef(const int x1, const int y1,
						 const int x2, const int y2);
int				cmd_connect_nbr(t_server_data *
						const data,
						const int fd,
						const char * const cmd);
int				cmd_check_connect_nbr(t_server_data *
						     const data,
						     const int fd,
						     const char * const cmd);

/*
** Command Fork
*/
int				delete_idx_egg(t_egg * const egg,
					       const int nb_eggs,
					       const int idx);
int				hatch_egg(t_server_data * const data,
					  t_client_data * const client,
					  const int t_idx);
int				cmd_fork(t_server_data *
					 const data,
					 const int fd,
					 const char * const cmd);
int				cmd_check_fork(t_server_data *
					      const data,
					      const int fd,
					      const char * const cmd);

/*
** Command Eject
*/
int				cmd_eject(t_server_data *
					  const data,
					  const int fd,
					  const char * const cmd);
int				cmd_check_eject(t_server_data *
					       const data,
					       const int fd,
					       const char * const cmd);

/*
** Command Take object
*/
int				cmd_take_object(t_server_data *
						const data,
						const int fd,
						const char * const cmd);
int				cmd_check_take_object(t_server_data *
						     const data,
						     const int fd,
						     const char * const cmd);

/*
** Command Set object
*/
int				cmd_set_object(t_server_data *
					       const data,
					       const int fd,
					       const char * const cmd);
int				cmd_check_set_object(t_server_data *
						    const data,
						    const int fd,
						    const char * const cmd);

/*
** Command Incantation
*/
int				print_win(t_ring_buff * const buff,
					  const char * const str);
int				print_current_level(t_ring_buff * const buff,
						    const int level);
int				cmd_incantation(t_server_data *
						const data,
						const int fd,
						const char * const cmd);
int				cmd_check_incantation(t_server_data *
						     const data,
						     const int fd,
						     const char * const cmd);

/*
** Command Look
*/
int				cmd_look(t_server_data *
					 const data,
					 const int fd,
					 const char * const cmd);
int				cmd_check_look(t_server_data *
					       const data,
					       const int fd,
					       const char * const cmd);
int				get_tiles_up(const t_server_data *
					     const data,
					     const t_client_data *
					     const tmp,
					     const t_ctrl *
					     const data_ctrl);
int				get_tiles_down(const t_server_data *
					       const data,
					       const t_client_data *
					       const tmp,
					       const t_ctrl *
					       const data_ctrl);
int				get_tiles_left(const t_server_data *
					       const data,
					       const t_client_data *
					       const tmp,
					       const t_ctrl *
					       const data_ctrl);
int				get_tiles_right(const t_server_data *
						const data,
						const t_client_data *
						const tmp,
						const t_ctrl *
						const data_ctrl);
int				print_result_look(const t_server_data *
						  const data,
						  const t_client_data *
						  const tmp,
						  const int x, const int y);

/*
** Command Take Object
*/
typedef struct			s_t_and_d_object
{
  char				*object;
  int				(*check_object)(t_server_data * const data,
						t_client_data * const tmp);
}				t_t_and_d_object;

int				take_food(t_server_data * const data,
					  t_client_data * const tmp);
int				take_linemate(t_server_data * const data,
					      t_client_data * const tmp);
int				take_deraumere(t_server_data * const data,
					       t_client_data * const tmp);
int				take_sibur(t_server_data * const data,
					   t_client_data * const tmp);
int				take_mendiane(t_server_data * const data,
					      t_client_data * const tmp);

/*
** Command Set Object
*/
int				drop_food(t_server_data * const data,
					  t_client_data * const tmp);
int				drop_linemate(t_server_data * const data,
					      t_client_data * const tmp);
int				drop_deraumere(t_server_data * const data,
					       t_client_data * const tmp);
int				drop_sibur(t_server_data * const data,
					   t_client_data * const tmp);
int				drop_mendiane(t_server_data * const data,
					      t_client_data * const tmp);

/*
** Command eject
*/
int				sent_eject_and_set_pos(t_client_data *
						       const tmp,
						       const unsigned int x,
						       const unsigned int y,
						       const t_direction dir);

/*
** Command Incantation
*/
typedef struct			s_elevation
{
  unsigned int			lvl;
  unsigned int			nb_player;
  unsigned int			linemate;
  unsigned int			deraumere;
  unsigned int			sibur;
  unsigned int			mendiane;
  unsigned int			phiras;
  unsigned int			thystame;
}				t_elevation;

int				check_end_game(const t_server_data *
					       const data,
					       const char * const team);

/*
** Communication with Graphic Client
*/
typedef struct			s_info_graphic
{
  char				*x;
  char				*y;
  char				*type;
  char				*name;
}				t_info_graphic;

int				send_end_begin_msg(t_server_data *
						   const data);
int				send_graphical_msg(t_server_data * const data,
						   const char * const str);
int				send_map_size(t_server_data * const data,
					      t_client_data * const graphic);
int				first_co_graphic(t_server_data * const data,
						 t_client_data *
						 const graphic);
int				add_few_stones(t_client_data *
					       const graphic,
					       const unsigned int nb,
					       t_info_graphic *
					       const info);

int				add_fl(const t_ressources *tile,
				       t_client_data * const graphic,
				       char * const x,
				       char * const y);
int				add_ds(const t_ressources *tile,
				       t_client_data * const graphic,
				       char * const x,
				       char * const y);
int				add_mp(const t_ressources *tile,
				       t_client_data * const graphic,
				       char * const x,
				       char * const y);
int				add_t(const t_ressources *tile,
				       t_client_data * const graphic,
				       char * const x,
				       char * const y);
void				free_data_graphic(t_info_graphic * const
						  graphic);
t_client_data			*get_graphic_client(const t_server_data *
						    const data);
int				add_something(t_client_data * const graphic,
					      const t_info_graphic * const
					      data);
int				delete_stone(t_client_data * const graphic,
					     const t_info_graphic * const
					     data);
int				send_death_to_graphic(t_client_data * const
						      graphic,
						      const int fd);

#endif /* !SERVER_H_ */
