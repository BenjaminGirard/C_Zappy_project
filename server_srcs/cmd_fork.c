/*
** cmd_forward.c for  in /home/tetard/eptechY2/PSU/PSU_2016_zappy/server_srcs
**
** Made by girard
** Login   <benjamin.girard@epitech.eu>
**
** Started on  Sat Jun 24 14:09:49 2017 girard
** Last update Sun Jul  2 17:34:51 2017 sebastien vidal
*/

#include <string.h>
#include <stdio.h>
#include "server.h"

int				cmd_fork(t_server_data * const data,
					 const int fd,
					 const char * const cmd)
{
  t_client_data			*tmp;

  (void)cmd;
  if ((tmp = find_client_fd(data->c_data, fd)) == NULL)
    return (CRITERR);
  ++tmp->nb_eggs;
  if ((tmp->eggs = realloc(tmp->eggs, sizeof(t_egg) * tmp->nb_eggs))
      == NULL)
    return (CRITERR);
  tmp->eggs[tmp->nb_eggs - 1].cooldown = 600000000.0 / data->args_data.freq;
  tmp->eggs[tmp->nb_eggs - 1].x = tmp->pos_x;
  tmp->eggs[tmp->nb_eggs - 1].y = tmp->pos_y;
  return (feed_tmp_str(&tmp->buff_writer, OK));
}

int				cmd_check_fork(t_server_data * const data,
					       const int fd,
					       const char * const cmd)
{
  t_client_data			*tmp;

  if ((tmp = find_client_fd(data->c_data, fd)) == NULL)
    return (CRITERR);
  if (strlen(cmd) > strlen("Fork"))
    return (CRITERR);
  if (nb_players_in_team(data, fd) > LIMIT_FORK)
    return (CRITERR);
  return (EXIT_SUCCESS);
}
