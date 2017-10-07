/*
** args.h for  in /home/tetard/eptechY2/PSU/PSU_2016_zappy/server_srcs
**
** Made by girard
** Login   <benjamin.girard@epitech.eu>
**
** Started on  Tue Jun 27 17:13:56 2017 girard
** Last update Sun Jul  2 09:45:05 2017 girard
*/

#ifndef ARGS_H_
# define ARGS_H_

# include <stdbool.h>

static const int		DEFAULT_NB_PLAYERS = 4;
static const char		* const DEF_TEAM_NAME [] =
  {
    "Team1",
    "Team2",
    "Team3",
    "Team4"
  };

static const int		ARGS_ERR = -1;

typedef struct			s_team
{
  const char			*name;
  unsigned int			nb_members;
}				t_team;

typedef struct			s_args
{
  int				port;
  int				width;
  int				height;
  t_team			*teams;
  unsigned int			nb_teams;
  int				nb_clients;
  int				freq;
}				t_args;

typedef struct			s_arg_action
{
  char				*option;
  int				(*arg_action)(const char * const av[],
					      t_args * const args_data);
}				t_arg_action;

bool				is_an_option(const char * const arg);

int				handle_args(const char * const av[],
					    t_args * const data_args);

int				get_arg_port(const char * const av[],
					     t_args * const data_args);
int				get_arg_width(const char * const av[],
					     t_args * const data_args);
int				get_arg_height(const char * const av[],
					     t_args * const data_args);
int				init_default_teams(t_args * const data_args);
int				get_arg_names(const char * const av[],
					     t_args * const data_args);
int				get_arg_clientnb(const char * const av[],
					     t_args * const data_args);
int				get_arg_freq(const char * const av[],
					     t_args * const data_args);

int				write_usage(const int ret);

#endif /* !ARGS_H_ */
