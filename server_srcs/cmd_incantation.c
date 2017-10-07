/*
** cmd_forward.c for  in /home/tetard/eptechY2/PSU/PSU_2016_zappy/server_srcs
**
** Made by girard
** Login   <benjamin.girard@epitech.eu>
**
** Started on  Sat Jun 24 14:09:49 2017 girard
** Last update Sun Jul  2 17:35:22 2017 sebastien vidal
*/

#include <string.h>
#include <stdio.h>
#include "server.h"

static const t_elevation	DATA_COND[] =
  {
    {0, 0, 0, 0, 0, 0, 0, 0},
    {1, 1, 0, 0, 0, 0, 0, 0},
    {2, 2, 1, 1, 1, 0, 0, 0},
    {3, 2, 2, 0, 1, 0, 2, 0},
    {4, 4, 1, 1, 2, 0, 1, 0},
    {5, 4, 1, 2, 1, 3, 0, 0},
    {6, 6, 1, 2, 3, 0, 1, 0},
    {7, 6, 2, 2, 2, 2, 2, 1},
    {8, 100000, 0, 0, 0, 0, 0, 0},
  };

static int			check_nb_player(const t_server_data *
						const data,
						const t_client_data *
						const cur)
{
  unsigned int			cur_nb_player;
  t_client_data			*tmp;

  cur_nb_player = 1;
  tmp = data->c_data;
  while (tmp)
    {
      if (tmp->lvl == cur->lvl && tmp->pos_x == cur->pos_x &&
	  tmp->pos_y == cur->pos_y && tmp != cur)
	++cur_nb_player;
      tmp = tmp->tail;
    }
  if (DATA_COND[cur->lvl].nb_player > cur_nb_player)
    return (EXIT_FAILURE);
  return (EXIT_SUCCESS);
}

static int			check_stones(const t_server_data *
					     const data,
					     const t_client_data *
					     const tmp)
{
  int				idx;

  idx = data->args_data.width * tmp->pos_y + tmp->pos_x;
  if (data->map[idx].linemate >= DATA_COND[tmp->lvl].linemate &&
      data->map[idx].deraumere >= DATA_COND[tmp->lvl].deraumere &&
      data->map[idx].sibur >= DATA_COND[tmp->lvl].sibur &&
      data->map[idx].mendiane >= DATA_COND[tmp->lvl].mendiane &&
      data->map[idx].phiras >= DATA_COND[tmp->lvl].phiras &&
      data->map[idx].thystame >= DATA_COND[tmp->lvl].thystame)
    return (EXIT_SUCCESS);
  return (EXIT_FAILURE);
}

static int			check_cond_for_elevate(const t_server_data *
						       const data,
						       t_client_data *
						       const tmp)
{
  if (check_nb_player(data, tmp) == EXIT_FAILURE ||
      check_stones(data, tmp) == EXIT_FAILURE)
    return (EXIT_FAILURE);
  return (EXIT_SUCCESS);
}

int				cmd_incantation(t_server_data * const data,
					      const int fd,
					      const char * const cmd)
{
  t_client_data			*tmp;

  (void)cmd;
  if ((tmp = find_client_fd(data->c_data, fd)) == NULL)
    return (CRITERR);
  if (tmp->lvl < 8)
    ++tmp->lvl;
  if (check_end_game(data, tmp->team) == EXIT_SUCCESS)
    return (print_win(&tmp->buff_writer, tmp->team));
  return (print_current_level(&tmp->buff_writer, tmp->lvl));
}

int				cmd_check_incantation(t_server_data *
						      const data,
						      const int fd,
						      const char * const cmd)
{
  t_client_data			*tmp;

  if ((tmp = find_client_fd(data->c_data, fd)) == NULL)
    return (CRITERR);
  if (strlen(cmd) > strlen("Incantation"))
    return (CRITERR);
  if (check_cond_for_elevate(data, tmp) == EXIT_FAILURE)
    return (CRITERR);
  return (feed_tmp_str(&tmp->buff_writer, "Elevation underway\n"));
}
